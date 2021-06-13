#ifndef SNIPER
#define SNIPER

#include "Character.h"

namespace mtm {

    class Sniper : public Character {
    private:
        static const units_t reload_credit = 2;
        static const units_t move_range = 4;
        units_t min_attacked_area_range = ceil((double)attack_range/2);
        units_t max_attacked_area_range = attack_range;
        units_t attacked_area_damage = ceil((double)power/2);
        units_t attacks_counter = 0;

    public:
        Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power, const GridPoint& location = GridPoint(0, 0));
        bool isInMoveRange(const GridPoint& point) const;
        void reload();
        void attack(Character* target,const GridPoint& destination);
        void doAttackedAreaDamage(Character* potential_effected_target, const GridPoint& potential_effected_destination);

    };
}

#endif  //  #ifndef SNIPER