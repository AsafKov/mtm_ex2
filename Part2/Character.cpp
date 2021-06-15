#include "Character.h"

namespace mtm {

    Team Character::getTeam() const {
        return team;
    }

    bool Character::isTeamMember(Character* character) const{
        return character->team == this->team;
    }

    CharacterType Character::getType() const{
        return type;
    }

    units_t Character::getPower() const{
        return power;
    }

    units_t Character::getAmmoCost() const {
        return AMMO_COST;
    }

    units_t Character::getAmmoCount() const{
        return ammo;
    }

    units_t Character::getAttackRange() const{
        return attack_range;
    }

    void Character::applyDamage(units_t damage){
        this->health-=damage;
    }

    bool Character::isDead() const {
        return health <= 0;
    }

    GridPoint Character::getLocation() const {
        return location;
    }

    void Character::setLocation(const GridPoint& location) {
        this->location = location;
    }

    units_t Character::distanceFromCurrentLocation(const GridPoint& point) const {
        return GridPoint::distance(this->location, point);
    }

    int Character::calculateKey(int row, int col, int width, int height) {
        int i = 1;
        if(row < col){
            i *= -1;
        }
        return (row * width + col) * i;
    }
}
