#ifndef SOLDIER
#define SOLDIER

#include "Character.h"

namespace mtm {

    class Soldier : public Character {
    private:
        units_t RELOAD_RATE{3};
        units_t MOVE_DISTANCE{3};

    public:
        Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power);
    };

}
#endif  //  #ifndef SOLDIER