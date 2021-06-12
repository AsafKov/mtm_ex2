#ifndef SOLDIER
#define SOLDIER

#include "Character.h"

namespace mtm {

    class Soldier : public Character {
    private:
        units_t reload_credit = 3;
        units_t move_range = 3;

    public:
        Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power,
                const GridPoint &location = GridPoint(0, 0));

        bool isInMoveRange(const GridPoint &point) const;
        void reload();
    };
}
#endif  //  #ifndef SOLDIER