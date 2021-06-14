#include "Medic.h"
namespace mtm {

    Medic::Medic(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type)
            : Character(team, health, ammo, attack_range, power, type) {}

    Character *Medic::clone() const{
        return new Medic(*this);
    }

    void Medic::reload() {
        this->ammo += mtm::Medic::RELOAD_CREDIT;
    }

    void Medic::attack(Character* target,const GridPoint& destination) {
        if (target == nullptr || this->location == target->getLocation()){
            throw IllegalTarget();
        }
        this->ammo -= getAmmoCost();
    }

    bool Medic::isDestinationInRange(GridPoint dst_coordinates) const {
        return distanceFromCurrentLocation(dst_coordinates) <= MOVE_RANGE;
    }

    bool Medic::isInAttackRange(GridPoint dst_coordinates) const {
        return distanceFromCurrentLocation(dst_coordinates) <= attack_range;
    }
}



