#include <SGE/components/physics/Rigidbody.hpp>
#include <random>
#include "BreakHandler.hpp"
#include "BreakGenerator.hpp"
#include "Fragment.hpp"
#include "TriangleOverlap.hpp"
#include <SGE/components/physics/Collider.hpp>
#include <Fading.hpp>
#include <game-scene/breakable/trigger/BreakTrigger.hpp>
#include <game-scene/breakable/generator/FragmentedLayerGenerator.hpp>

#define LAYER_CONTAINER_ID "Fragmented Layer Container "

unsigned int BreakHandler::break_event_counter = 0;

std::string BreakHandler::get_logic_id() {
    return std::string("BreakHandler");
}

BreakHandler::BreakHandler(bool is_child_dependent, bool fade_on_break, const std::string& fragment_collision_layer) {
    m_child_dependent_flag = is_child_dependent;
    m_fade_on_break_flag = fade_on_break;
    this->fragment_collision_layer = fragment_collision_layer;
}

bool BreakHandler::is_child_dependent() const {
    return m_child_dependent_flag;
}

void BreakHandler::break_pulse(b2Vec2 linear_vel_at_break, float trigger_val) {
    this->linear_vel_at_break = linear_vel_at_break;
    this->trigger_val_at_break = trigger_val;
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

        // Count total fragments
        int total_fragment_infos = 0;
        for (int l1 = 0; l1 < collected_fragment_info.size(); ++l1) {
            total_fragment_infos += collected_fragment_info[l1].size();
        }
        int container_indexes[total_fragment_infos];
        for (int i1 = 0; i1 < total_fragment_infos; ++i1) {
            container_indexes[i1] = -1;
        }
        std::vector<GameObject_H> spawned_containers;

        int already_spawned_total = 0;
        for (int layer = 0; layer < collected_fragment_info.size(); ++layer) {
            // Scroll this layer's info, when pointing to a given info check if adjacent to previously spawned fragments
            // if it is spawn it as child of the previously created container, if not spawn it in a new container

            unsigned int prev_containers_count[spawned_containers.size()];      // keep tracks of how many fragments of this layer have been placed in the containers primarily created by the previous layers
            for (int k = 0; k < spawned_containers.size(); ++k) { prev_containers_count[k] = 0;};
            unsigned int already_spawned_this_layer = 0;

            std::shuffle(collected_fragment_info[layer].begin(), collected_fragment_info[layer].end(), std::default_random_engine(random()));

            for (int pointed = 0; pointed < collected_fragment_info[layer].size(); ++pointed) {
                auto target_info = collected_fragment_info[layer][pointed];
                unsigned int pointed_shallow_index = (already_spawned_total-already_spawned_this_layer) + pointed;


                // Check if this fragment would overlap with fragments from the previous layers
                bool found_overlap = false;
                for (int j = 0; j < spawned_fragments.size()-already_spawned_this_layer; ++j) {

                    // Check if the container of the fragment to check has enough space for this fragment, if not there's no point in checking overlaps
                    if (prev_containers_count[container_indexes[j]] < target_info.max_triangles && target_info.max_triangles > 1) {
                        auto my_triangle = target_info.world_positions;
                        if (TriTri2D(spawned_fragments[j]->get_info().world_positions, my_triangle, 0.000001, true, false)) {
                            container_indexes[pointed_shallow_index] = container_indexes[j];
                            prev_containers_count[container_indexes[j]]++;
                            found_overlap = true;
                            break;
                        }
                    }
                }
                // If so adds it to the corresponding container (if not already too big)
                // If not already placed in a container, check if adjacent with another already spawned fragment from the same layer
                // Adds it to the corresponding container if not already too big, else create a new container

                bool found_adjacency = false;
                if (!found_overlap && target_info.max_triangles > 1) {

                    for (int i = pointed-1; i >= 0; --i) {
                        unsigned int i_shallow_index = (already_spawned_total-already_spawned_this_layer) + i;
                        if (target_info.shares_border(collected_fragment_info[layer][i])) {
                            if (spawned_containers[container_indexes[i_shallow_index]]->transform()->get_children().size() >= target_info.max_triangles){
                                continue;
                            }  else {
                                found_adjacency = true;
                                container_indexes[pointed_shallow_index] = container_indexes[i_shallow_index];
                                break;
                            }
                        }
                    }
                }

                // No feasible container can accept this fragment, create a new one
                if (!found_adjacency && !found_overlap) {
                    GameObject_H recipient_container;
                    container_indexes[pointed_shallow_index] = spawned_containers.size();
                    recipient_container = scene()->spawn_gameobject("Fragment Container");
                    recipient_container->transform()->set_local_position(target_info.world_center);
                    auto container_rb = recipient_container->add_component<sge::cmp::Rigidbody>("Rigidbody");
                    spawned_containers.push_back(recipient_container);
                }


                // Now that we have a container ready to accept the new fragment we can spawn it
                auto fragment = scene()->spawn_gameobject("Fragment");
                auto recipient_container = spawned_containers[container_indexes[pointed_shallow_index]];

                auto recipient_layer_container_t = recipient_container->transform()->get_child(LAYER_CONTAINER_ID + std::to_string(layer));
                if (recipient_layer_container_t.is_null()) {
                    auto recipient_layer_container_obj = scene()->spawn_gameobject(LAYER_CONTAINER_ID + std::to_string(layer));
                    recipient_layer_container_obj->transform()->set_parent(recipient_container->transform());
                    recipient_layer_container_t = recipient_layer_container_obj->transform();
                }
                fragment->transform()->set_local_position(target_info.world_center - recipient_container->transform()->get_world_position());
                fragment->transform()->set_parent(recipient_layer_container_t);
                auto fragment_logic = new Fragment(target_info, break_event_id);
                fragment->logichub()->attach_logic(fragment_logic);
                spawned_fragments.push_back(fragment_logic);

                already_spawned_this_layer++;
                already_spawned_total++;
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

            // Make the fragments'velocity the same as the original object
            // TODO maybe the break could absorb some of the kinetic energy
            container_rb->get_b2_body()->SetLinearVelocity(linear_vel_at_break);


            // Add some Fading logic if the fade_on_break flag is on
            if (spawned_containers[l]->transform()->get_child_count(true) <= 2 || m_fade_on_break_flag) {
                spawned_containers[l]->logichub()->attach_logic(new Fading(0.3));
            } else {
                // Add breakable logic
                spawned_containers[l]->logichub()->attach_logic(new BreakHandler(true, m_fade_on_break_flag, fragment_collision_layer));
                for (auto layer : spawned_containers[l]->transform()->get_children()) {
                    layer->gameobject()->logichub()->attach_logic(new FragmentedLayerGenerator(collected_fragment_info[0][0].max_triangles-1));
                    for (auto fragment : layer->get_children()) {
                        fragment->gameobject()->logichub()->attach_logic(new BreakTrigger(trigger_val_at_break));
                    }
                }
            }
        }
        collected_fragment_info.clear();
    }
}

void BreakHandler::recursive_info_collection(std::vector<std::vector<FragmentInfo>> &container,
                                             GameObject_H target) {
    auto break_generator_logic = target->logichub()->get_logic<BreakGenerator>();
    if (break_generator_logic != nullptr) {
        container.emplace_back();
        break_generator_logic->collect_fragment_info(container.back());
    }

    for (auto child : target->transform()->get_children()) {
        recursive_info_collection(container, child->gameobject());
    }
}
