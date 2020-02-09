#ifndef NON_GRAVITAR_PLAYERPERSISTENTDATA_HPP
#define NON_GRAVITAR_PLAYERPERSISTENTDATA_HPP

#include "COLORS.hpp"
#include <utility-classes/ColorPalette.hpp>
#include <SGE/utils/events/Events.hpp>


#define NG_PLAYER_STARTING_LIVES 3
#define NG_PLAYER_STARTING_MAX_STAMINA 100
#define NG_PLAYER_STARTING_MAX_FUEL 100.0


template <class T>
class WatchedVal {
public:
    explicit WatchedVal(const T& initial_val) { val = initial_val; }
    void subscribe(const utils::event::EventHandler& event_handler) { val_changed_event.addHandler(event_handler); }
    void unsubscribe(const utils::event::EventHandler& event_handler) { val_changed_event.removeHandler(event_handler); }
    void unsubscribe(int ev_handler_id) { val_changed_event.removeHandler(ev_handler_id); }
    void set(const T& new_val) { val = new_val; val_changed_event(); }
    T value() const { return val; }
    void clear_subscribers() { val_changed_event.clearSubscribers(); }
private:
    utils::event::Event val_changed_event;
    T val;
};

class Player;

struct PlayerPersistentData {
    friend class Player;

    WatchedVal<float> fuel_amount = WatchedVal<float>(NG_PLAYER_STARTING_MAX_FUEL);
    WatchedVal<float> fuel_max = WatchedVal<float>(NG_PLAYER_STARTING_MAX_FUEL);
    WatchedVal<float> stamina_max = WatchedVal<float>(NG_PLAYER_STARTING_MAX_STAMINA);
    WatchedVal<float> stamina_amount = WatchedVal<float>(NG_PLAYER_STARTING_MAX_STAMINA);
    WatchedVal<int> lives = WatchedVal<int>(NG_PLAYER_STARTING_LIVES);
    WatchedVal<int> score = WatchedVal<int>(0);
    WatchedVal<int> bonus_score = WatchedVal<int>(0);

    bool is_player_alive() const {
        return is_alive;
    }

private:
    bool is_alive = true;
};





#endif //NON_GRAVITAR_PLAYERPERSISTENTDATA_HPP
