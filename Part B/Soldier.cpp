#include "Soldier.h"
namespace mtm {

    Soldier::Soldier(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, const GridPoint& location)
            : Character(team, health, ammo, attack_range, power, location) {
    }

    bool Soldier::isInMoveRange(const GridPoint& point) const {
        return distanceFromCurrentLocation(point) <= this->move_range;
    }

//    bool Soldier::isInEffectedEreaRange(Character* target,const GridPoint& destination) const {
//        return distanceFromCurrentLocation(point) <= this->move_range;
//    }

    void Soldier::reload() {
        this->ammo += this->reload_credit;
    }

    void Soldier::attack(Character* target,const GridPoint& destination) {
        if (target == NULL) {
            return;
        }
        if(!this->isInAttackRange(destination)){
            throw //todo: invalid location
        }
        if ((destination.col != this->location.col) && (destination.row != this->location.col)) {
            throw //todo: invalid location
        }
        if(this->ammo){
            throw //todo: no ammo
        }
        this->ammo -= getAmmoCost();
        target->doDamage(this->power);
        doAttackedAreaDamage();
    }

    void Soldier::doAttackedAreaDamage(Character* potential_effected_target, const GridPoint& potential_effected_destination) {
        units_t distance = this->distanceFromCurrentLocation(potential_effected_destination);
        if(distance<min_attacked_area_range || distance>max_attacked_area_range){
            potential_effected_target->doDamage(this->attacked_area_damage);
        }
    }
}

