#ifndef MEDIC
#define MEDIC

#include "Character.h"

namespace mtm {

    class Medic : public Character {
    private:
        units_t RELOAD_RATE{5};
        units_t MOVE_DISTANCE{5};

    public:
        Medic(Team team, units_t health, units_t ammo, units_t range, units_t power);
    };
}

#endif  //  #ifndef MEDIC