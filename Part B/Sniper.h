#ifndef SNIPER
#define SNIPER

#include "Character.h"

namespace mtm {

    class Sniper : public Character {
    private:
        static const units_t reload_credit = 2;
        static const units_t move_range = 4;
        units_t min_attack_area_range = (attack_range+1)/2;
        units_t max_attack_area_range = attack_range; //see if ring should affect the range from the higher radius.
        units_t attack_area_damage = (power+1)/2;

    public:
        Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power, const GridPoint& location = GridPoint(0, 0));
        bool isInMoveRange(const GridPoint& point) const;
        void reload();
        };
}

#endif  //  #ifndef SNIPER