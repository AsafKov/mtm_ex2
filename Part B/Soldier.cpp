#include "Soldier.h"
namespace mtm {

    Soldier::Soldier(Team team, units_t health, units_t ammo, units_t range, units_t power)
            : Character(team, health, ammo, range, power) {

    }
}

