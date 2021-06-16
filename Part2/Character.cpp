#include "Character.h"

namespace mtm {

    int Character::calculateKey(const GridPoint& coordinates, int width) {
        int row = coordinates.row;
        int col = coordinates.col;
        int i = 1;
        if(row < col){
            i *= -1;
        }
        return (row * width + col) * i;
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

    units_t Character::distanceFromCurrentLocation(const GridPoint& point) const {
        return GridPoint::distance(this->location, point);
    }

}
