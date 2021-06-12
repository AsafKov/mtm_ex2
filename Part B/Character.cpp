#include "Character.h"

namespace mtm {

    Character::Character(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, const GridPoint& location) {
        this->team = team;
        this->health = health;
        this->ammo = ammo;
        this->attack_range = attack_range;
        this->power = power;
        this->location = location;
    }

    Team Character::getTeam() const {
        return team;
    }

    bool Character::isTeamMember(const Character* character) const {
        return character->team == this->team;
    }

    void Character::setDamage(units_t damage){
        this->health-=damage;
    }

    bool Character::isDead() const {
        return health <= 0;
    }

    units_t Character::getAmmoCount() const{
        return ammo;
    }

    units_t Character::getAmmoCost() const {
        return this->AMMO_COST;
    }

    units_t Character::getTargetAmmoCost(const Character* target) const {
        return target->AMMO_COST;
    }

    units_t Character::distance(const GridPoint& point) const {
        return GridPoint::distance(location, point);
    }

    bool Character::isInAttackRange(const GridPoint& point) const {
        return distance(point) <= this->attack_range;
    }

    void Character::setLocation(const GridPoint& location) {
        this->location = location;
    }

    GridPoint Character::getLocation() const {
        return location;
    }

}