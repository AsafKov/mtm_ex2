#include "Character.h"

namespace mtm {

    int Character::calculateKey(int row, int col, int width) {
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

    void Character::setLocation(const GridPoint& coordinates) {
        this->location = coordinates;
    }

    units_t Character::distanceFromCurrentLocation(const GridPoint& point) const {
        return GridPoint::distance(this->location, point);
    }

}
