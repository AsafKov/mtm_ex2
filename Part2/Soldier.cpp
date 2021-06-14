#include "Soldier.h"
namespace mtm {


    Soldier::Soldier(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type)
            : Character(team, health, ammo, attack_range, power, type) {}

    Character *Soldier::clone() const{
        return new Soldier(*this);
    }

//    bool Soldier::isInEffectedEreaRange(Character* target,const GridPoint& destination) const {
//        return distanceFromCurrentLocation(point) <= this->MOVE_RANGE;
//    }

    void Soldier::reload() {
        this->ammo += mtm::Soldier::RELOAD_CREDIT;
    }

    void Soldier::attack(Character* target,const GridPoint& destination) {
        if (target == NULL) {
            return;
        }
        if(!this->isInAttackRange(destination)){
             //todo: invalid location
        }
        if ((destination.col != this->location.col) && (destination.row != this->location.col)) {
             //todo: invalid location
        }
        if(this->ammo){
            //todo: no ammo
        }
        this->ammo -= getAmmoCost();
        target->doDamage(this->power);
//        doAttackedAreaDamage();
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

//    void Soldier::doAttackedAreaDamage(Character* potential_effected_target, const GridPoint& potential_effected_destination) {
//        units_t distance = this->distanceFromCurrentLocation(potential_effected_destination);
//        if(distance<min_attacked_area_range || distance>max_attacked_area_range){
//            potential_effected_target->doDamage(this->attacked_area_damage);
//        }
//    }
}

