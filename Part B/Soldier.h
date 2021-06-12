#ifndef SOLDIER
#define SOLDIER

#include "Character.h"

namespace mtm {

    class Soldier : public Character {
    private:
        static const units_t reload_credit = 3;
        static const units_t move_range = 3;
        units_t min_attack_area_range = 1;
        units_t max_attack_area_range = (attack_range+2)/3; //how to create upper rounding
        units_t attack_area_damage = (power+1)/2;

    public:
        Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power,
                const GridPoint &location = GridPoint(0, 0));

        bool isInMoveRange(const GridPoint &point) const;
        void reload();
    };
}
#endif  //  #ifndef SOLDIER