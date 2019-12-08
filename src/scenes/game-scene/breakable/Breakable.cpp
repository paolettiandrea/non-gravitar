#include "Breakable.hpp"
#include "SGE/components/physics/Collider.hpp"
#include "Fragment.hpp"
#include <random>

std::string Breakable::get_logic_id() {
    return std::string("Breakable");
}

Breakable::Breakable(float impact_velocity, bool child_dependent) {
    this->max_impact_velocity = impact_velocity;
    this->m_child_dependent = child_dependent;
}

void Breakable::pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const sge::CollisionInfo &info) {
    Logic::pre_solve(contact, oldManifold, info);

    if (info.get_impact_velocity().get_magnitude() > max_impact_velocity) {
        // This object is breaking!
        break_handler_event();
        if (break_handler_event.totalHandlers() == 0)
            break_pulse(collected_fragment_info);
        contact->SetEnabled(false);
    }
}

void Breakable::on_update() {
    if (!collected_fragment_info.empty()) {
        std::vector<Fragment*> spawned_fragments;
        // Vector where at a given index is stored the index of the container to which the corresponding spawned fragment
        // was assigned, -1 if not assigned yet
        std::vector<int> container_indexes;
        std::vector<utils::Handle<sge::GameObject>> spawned_containers;

        // Shuffle this layer of information (in order to avoid same models braking always the same way)
        std::shuffle(collected_fragment_info.begin(), collected_fragment_info.end(), std::default_random_engine(random()));
        for (auto info : collected_fragment_info) {
            container_indexes.push_back(-1);
        }

        int piece_number_target = 3;
        // Scroll this layer's info, when pointing to a given info check if adjacent to previously spawned fragments
        // if it is spawn it as child of the previously created container, if not spawn it in a new container
        for (int pointed = 0; pointed < collected_fragment_info.size(); ++pointed) {

            utils::Handle<sge::GameObject> target_container;
            bool found_adjacency = false;
            for (int i = pointed-1; i >= 0; --i) {
                if (collected_fragment_info[pointed].shares_border(collected_fragment_info[i])) {
                    target_container = spawned_containers[container_indexes[i]];
                    if (target_container->transform()->get_children().size()>piece_number_target){
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
                target_container->transform()->set_local_position(collected_fragment_info[pointed].position);
                target_container->add_component<sge::cmp::Rigidbody>("Rigidbody");
                spawned_containers.push_back(target_container);
            }

            // Now that we have a container ready to accept the new fragment we can spawn it
            auto fragment = scene()->spawn_gameobject("Fragment");
            fragment->transform()->set_parent(target_container->transform());
            auto fragment_logic = new Fragment(collected_fragment_info[pointed]);
            fragment->logichub()->attach_logic(fragment_logic);
            spawned_fragments.push_back(fragment_logic);
        }
    }

    collected_fragment_info.clear();
}

void Breakable::break_pulse(std::vector<FragmentInfo>& container) {
    collect_fragment_info(container);
    gameobject()->doom();
}

void Breakable::collect_fragment_info(std::vector<FragmentInfo>& container) {

}
