#ifndef MEDIC
#define MEDIC

#include "Character.h"

namespace mtm {

    class Medic : public Character {
    private:
        units_t reload_credit{5};
        units_t move_range{5};
        units_t min_attack_area_range = 1;
        units_t max_attack_area_range = attack_range;
        units_t attack_area_damage = power;

    public:
        Medic(Team team, units_t health, units_t ammo, units_t range, units_t power,const GridPoint &location = GridPoint(0, 0));
        bool isInMoveRange(const GridPoint& point) const;
        void reload();
    };
}

#endif  //  #ifndef MEDIC