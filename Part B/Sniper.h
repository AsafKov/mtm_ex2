#ifndef SNIPER
#define SNIPER

#include "Character.h"

namespace mtm {

    class Sniper : public Character {
    private:
        units_t RELOAD_RATE{2};
        units_t MOVE_DISTANCE{4};
    public:
        Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power);
    };
}

#endif  //  #ifndef SNIPER