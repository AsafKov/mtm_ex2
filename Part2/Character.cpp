#include "Character.h"

namespace mtm {

    Team Character::getTeam() const {
        return team;
    }

    bool Character::isTeamMember(Character* character) const{
        return character->team == this->team;
    }

    void Character::doDamage(units_t damage){
        this->health-=damage;
    }

    bool Character::isDead() const {
        return health <= 0;
    }

    units_t Character::getAmmoCount() const{
        return ammo;
    }

    units_t Character::getAttackRange() const{
        return attack_range;
    }

    units_t Character::getPower() const{
        return power;
    }

    units_t Character::getAmmoCost() const {
        return mtm::Character::AMMO_COST;
    }

    units_t Character::getTargetAmmoCost(const Character* target) const {
        return target->AMMO_COST;
    }

    units_t Character::distanceFromCurrentLocation(const GridPoint& point) const {
        return GridPoint::distance(this->location, point);
    }

    void Character::setLocation(const GridPoint& location) {
        this->location = location;
    }

    GridPoint Character::getLocation() const {
        return location;
    }

    CharacterType Character::getType() const{
        return type;
    }
}