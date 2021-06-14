#include "Soldier.h"
namespace mtm {


    Soldier::Soldier(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type)
            : Character(team, health, ammo, attack_range, power, type) {}

    Character *Soldier::clone() const{
        return new Soldier(*this);
    }

    void Soldier::reload() {
        this->ammo += mtm::Soldier::RELOAD_CREDIT;
    }

    void Soldier::attack(Character* target, const GridPoint& destination) {
        if (target == nullptr) {
            return;
        }
        this->ammo -= getAmmoCost();
    }

    bool Soldier::isDestinationInRange(GridPoint dst_coordinates) const{
        return distanceFromCurrentLocation(dst_coordinates) <= mtm::Soldier::MOVE_RANGE;
    }

    bool Soldier::isInAttackRange(GridPoint dst_coordinates) const {
        if(dst_coordinates.row != location.row && dst_coordinates.col != location.col){
            return false;
        }
        return distanceFromCurrentLocation(dst_coordinates) <= attack_range;
    }

}

