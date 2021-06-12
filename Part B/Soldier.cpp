#include "Soldier.h"
namespace mtm {

    Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power, const GridPoint& location)
            : Character(team, health, ammo, range, power, location) {
    }

    bool Soldier::isInMoveRange(const GridPoint& point) const {
        return distance(point) <= this->move_range;
    }

    void Soldier::reload() {
        this->ammo += this->reload_credit;
    }

}

