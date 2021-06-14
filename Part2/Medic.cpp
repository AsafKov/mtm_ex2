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
            //todo: invalid target
        }
        if(!this->isInAttackRange(destination)){
            //todo: invalid location
        }
        if(this->ammo){
            //todo: no ammo
        }
        this->ammo -= getAmmoCost();
        target->doDamage(this->power);
    }

    bool Medic::isDestinationInRange(GridPoint dst_coordinates) const {
        return distanceFromCurrentLocation(dst_coordinates) <= mtm::Medic::MOVE_RANGE;
    }
}

bool mtm::Medic::isInAttackRange(mtm::GridPoint dst_coordinates) const {
    return distanceFromCurrentLocation(dst_coordinates) <= attack_range;
}

mtm::units_t mtm::Medic::getAmmoCost() const {
    return Medic::AMMO_COST;
}


