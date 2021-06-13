#ifndef MEDIC
#define MEDIC

#include "Character.h"

namespace mtm {

    class Medic : public Character {
    private:
        static const units_t reload_credit{5};
        static const units_t move_range{5};
//        units_t min_attacked_area_range = 1;
//        units_t max_attacked_area_range = attack_range;
//        units_t attacked_area_damage = power;

    public:
        Medic(Team team, units_t health, units_t ammo, units_t range, units_t power,const GridPoint &location = GridPoint(0, 0));
        bool isInMoveRange(const GridPoint& point) const;
        void reload();
        void attack(Character* target,const GridPoint& destination);

    };
}

#endif  //  #ifndef MEDIC