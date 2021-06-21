#include "Character.h"

namespace mtm {

    int Character::calculateKey(const GridPoint& coordinates, int width) {
        int row = coordinates.row;
        int col = coordinates.col;
        int key = (row * width + col);
        if(row < col){
            return -key;
        }
        return key;
    }

    Team Character::getTeam() const {
        return team;
    }

    CharacterType Character::getType() const{
        return type;
    }

    void Character::dealDamage(units_t damage){
        this->health-=damage;
    }

    bool Character::isDead() const {
        return health <= 0;
    }

    bool Character::isOutOfAmmo() const {
        return (ammo < AMMO_COST);
    }

    void Character::updateAmmo() {
        ammo -= AMMO_COST;
    }

    void Character::setLocation(const GridPoint& coordinates) {
        this->location = coordinates;
    }

    units_t Character::distanceFromCurrentLocation(const GridPoint& coordinates) const {
        return GridPoint::distance(this->location, coordinates);
    }
}
