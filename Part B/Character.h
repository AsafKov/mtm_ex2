
#ifndef CHARACTER
#define CHARACTER
#include "Auxiliaries.h"

namespace mtm {

    class Character {
    protected:
        Character(Team team, units_t health, units_t ammo, units_t range, units_t power);

        Team team;
        units_t health;
        units_t ammo;
        units_t range;
        units_t power;
    };
}

#endif //CHARACTER
