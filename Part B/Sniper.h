#ifndef SNIPER
#define SNIPER

#include "Character.h"

namespace mtm {

    class Sniper : public Character {
    private:
        units_t reload_credit = 2;
        units_t move_range = 4;
    public:
        Sniper(Team team, units_t health, units_t ammo, units_t range, units_t power, const GridPoint& location = GridPoint(0, 0));
        bool isInMoveRange(const GridPoint& point) const;
        void reload();
        };
}

#endif  //  #ifndef SNIPER