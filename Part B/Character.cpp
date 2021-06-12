#include "Character.h"

namespace mtm {

    Character::Character(Team team, units_t health, units_t ammo, units_t range, units_t power) {
        this->team = team;
        this->health = health;
        this->ammo = ammo;
        this->range = range;
        this->power = power;
    }
    
}