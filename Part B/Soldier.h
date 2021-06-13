#ifndef SOLDIER
#define SOLDIER

#include "Character.h"

namespace mtm {

    class Soldier : public Character {
    private:
        static const units_t reload_credit = 3;
        static const units_t move_range = 3;
        units_t min_attacked_area_range = 1;
        units_t max_attacked_area_range = ceil((double)attack_range/3);
        units_t attacked_area_damage = ceil((double)power/2);

    public:
        Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power,
                const GridPoint &location = GridPoint(0, 0));

        bool isInMoveRange(const GridPoint &point) const;
        void reload();
        void attack(Character *target, const GridPoint &destination);
        void doAttackedAreaDamage(const GridPoint& attack_location, Character* character);
    };
}
#endif  //  #ifndef SOLDIER