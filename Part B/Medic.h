#ifndef MEDIC
#define MEDIC

#include "Character.h"

namespace mtm {

    class Medic : public Character {
    private:
        units_t reload_credit{5};
        units_t move_range{5};

    public:
        Medic(Team team, units_t health, units_t ammo, units_t range, units_t power,const GridPoint &location = GridPoint(0, 0));
        bool isInMoveRange(const GridPoint& point) const;
        void reload();
    };
}

#endif  //  #ifndef MEDIC