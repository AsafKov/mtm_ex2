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

    units_t Character::distanceFromCurrentLocation(const GridPoint& coordinates) const {
        return GridPoint::distance(this->location, coordinates);
    }
}
