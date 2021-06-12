#include "Medic.h"
namespace mtm {

    Medic::Medic(Team team, units_t health, units_t ammo, units_t range, units_t power, const GridPoint& location)
            : Character(team, health, ammo, range, power, location) {

    }

    bool Medic::isInMoveRange(const GridPoint& point) const {
        return distance(point) <= this->move_range;
    }

    void Medic::reload() {
        this->ammo += this->reload_credit;
    }
}

