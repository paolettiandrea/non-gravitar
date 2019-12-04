#include <SGE/components/physics/Rigidbody.hpp>
#include <random>
#include "BreakHandler.hpp"
#include "BreakGenerator.hpp"
#include "Fragment.hpp"
#include "TriangleOverlap.hpp"
#include <SGE/components/physics/Collider.hpp>

unsigned int BreakHandler::break_event_counter = 0;

std::string BreakHandler::get_logic_id() {
    return std::string("BreakHandler");
}

BreakHandler::BreakHandler(bool is_child_dependent) {
    m_child_dependent_flag = is_child_dependent;
}

bool BreakHandler::is_child_dependent() const {
    return m_child_dependent_flag;
}

void BreakHandler::break_pulse() {
    if (collected_fragment_info.empty()) {
        recursive_info_collection(collected_fragment_info, gameobject());
        break_event_id = ++break_event_counter;

        if (!collected_fragment_info.empty()) {
            gameobject()->doom();
        } else {
            LOG_ERROR << "Something went wrong, after fragment info collection the info container is empty. It could be"
                         "a complete absence of BreakGenerators down the hierarchy.";
            exit(1);
        }
    }
}

void BreakHandler::on_update() {
    if (!collected_fragment_info.empty()) {
        std::vector<Fragment*> spawned_fragments;
        // Vector where at a given index is stored the index of the container to which the corresponding spawned fragment
        // was assigned, -1 if not assigned yet
        std::vector<int> container_indexes;
        std::vector<utils::Handle<sge::GameObject>> spawned_containers;

        // Shuffle this layer of information (in order to avoid same models braking always the same way)
        for (auto info : collected_fragment_info) {
            container_indexes.push_back(-1);
        }

        for (int layer = 0; layer < collected_fragment_info.size(); ++layer) {
            // Scroll this layer's info, when pointing to a given info check if adjacent to previously spawned fragments
            // if it is spawn it as child of the previously created container, if not spawn it in a new container

            unsigned int prev_containers_count[spawned_containers.size()];      // keep tracks of how many fragment of this layer have been placed in the containers primarily created by the previous layers
            for (int k = 0; k < spawned_containers.size(); ++k) { prev_containers_count[k] = 0;};
            unsigned int already_spawned_this_layer = 0;

            std::shuffle(collected_fragment_info[layer].begin(), collected_fragment_info[layer].end(), std::default_random_engine(random()));

            for (int pointed = 0; pointed < collected_fragment_info[layer].size(); ++pointed) {

                auto target_info = collected_fragment_info[layer][pointed];
                utils::Handle<sge::GameObject> target_container;

                // Check if this fragment would overlap with fragments from the previous layers
                bool found_overlap = false;
                for (int j = 0; j < spawned_fragments.size()-already_spawned_this_layer; ++j) {
                    auto fragment_to_check = spawned_fragments[j];

                    // Check if the container of the fragment to check has enough space for this fragment, if not there's no point in checking overlaps
                    if (prev_containers_count[container_indexes[j]] < target_info.max_triangles) {
                        TriPoint* its_triangle = fragment_to_check->get_info().world_positions;
                        auto my_triangle = target_info.world_positions;
                        if (TriTri2D(its_triangle, my_triangle, 0.01, true, false)) {
                            target_container = spawned_containers[container_indexes[j]];
                            prev_containers_count[container_indexes[j]]++;
                            found_overlap = true;
                            break;
                        }
                    }
                }
                // If so adds it to the corresponding container (if not already too big)
                // If not already placed in a container, check if adjacent with another already spawned fragment from the same layer
                // Adds it to the corresponding container if not already too big, alse create a new container

                if (!found_overlap) {
                    bool found_adjacency = false;
                    for (int i = pointed-1; i >= 0; --i) {
                        if (target_info.shares_border(collected_fragment_info[layer][i])) {
                            target_container = spawned_containers[container_indexes[i]];
                            if (target_container->transform()->get_children().size()>=target_info.max_triangles){
                                continue;
                            }  else {
                                found_adjacency = true;
                                container_indexes[pointed] = container_indexes[i];
                                break;
                            }
                        }
                    }
                    if (!found_adjacency) {
                        container_indexes[pointed] = spawned_containers.size();
                        target_container = scene()->spawn_gameobject("Fragment Container");
                        target_container->transform()->set_local_position(target_info.world_center);
                        auto container_rb = target_container->add_component<sge::cmp::Rigidbody>("Rigidbody");
                        spawned_containers.push_back(target_container);
                    }
                }


                // Now that we have a container ready to accept the new fragment we can spawn it
                auto fragment = scene()->spawn_gameobject("Fragment");
                fragment->transform()->set_local_position(target_info.world_center - target_container->transform()->get_world_position());
                fragment->transform()->set_parent(target_container->transform());
                auto fragment_logic = new Fragment(target_info, break_event_id);
                fragment->logichub()->attach_logic(fragment_logic);
                spawned_fragments.push_back(fragment_logic);

                already_spawned_this_layer++;
            }
        }

        for (int n = 0; n < spawned_fragments.size(); ++n) {
            auto col = spawned_fragments[n]->gameobject()->get_component<sge::cmp::Collider>("Collider");
            col->force_clean_pass();
        }

        sge::Vec2<float> explosion_origin_local_position;
        for (int l = 0; l < spawned_containers.size(); ++l) {
            auto container_rb = spawned_containers[l]->get_component<sge::cmp::Rigidbody>("Rigidbody");

            b2MassData m;
            container_rb->get_b2_body()->GetMassData(&m);

            auto center = container_rb->get_b2_body()->GetWorldPoint(m.center);
            auto this_container_center = sge::Vec2<float>(center.x, center.y);

            auto distance_vec = this_container_center - gameobject()->transform()->local_to_world_point(explosion_origin_local_position);

            auto impulse_vec = distance_vec;
            impulse_vec.set_magnitude(1/(1+distance_vec.get_magnitude()));
            container_rb->apply_linear_impulse(impulse_vec, this_container_center, true);
        }

        collected_fragment_info.clear();
    }
}

void BreakHandler::recursive_info_collection(std::vector<std::vector<FragmentInfo>> &container,
                                             utils::Handle<sge::GameObject> target) {
    auto break_generator_logic = target->logichub()->get_logic_by_id<BreakGenerator>("BreakGenerator");
    if (break_generator_logic != nullptr) {
        container.emplace_back();
        break_generator_logic->collect_fragment_info(container.back());
    }

    for (auto child : target->transform()->get_children()) {
        recursive_info_collection(container, child->gameobject());
    }
}
