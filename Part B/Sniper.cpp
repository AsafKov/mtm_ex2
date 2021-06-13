#include "Sniper.h"
namespace mtm {

    Sniper::Sniper(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, const GridPoint& location)
            : Character(team, health, ammo, attack_range, power, location) {

    }

    bool Sniper::isInMoveRange(const GridPoint& point) const {
        return distanceFromCurrentLocation(point) <= this->move_range;
    }

    void Sniper::reload() {
        this->ammo += this->reload_credit;
    }

    bool Sniper::isDoubleDamage() {
        return (this->attacks_counter++)%3 == 0);
    }

    void Sniper::attack(Character* target,const GridPoint& destination) {
        if (target == NULL || isTeamMember(target)){
            throw //todo: invalid target
        }
        if(!this->isInAttackRange(destination)){
            throw //todo: invalid location
        }
        if(this->ammo){
            throw //todo: no ammo
        }
        this->ammo -= getAmmoCost();
        if(isDoubleDamage()){
            target->doDamage(this->power*2);
        }
        target->doDamage(this->power);
        doAttackedAreaDamage();
    }

    void Sniper::doAttackedAreaDamage(Character* potential_effected_target, const GridPoint& potential_effected_destination) {
        units_t distance = this->distanceFromCurrentLocation(potential_effected_destination);
        if(distance<min_attacked_area_range || distance>max_attacked_area_range){
            potential_effected_target->doDamage(this->attacked_area_damage);
        }
    }
}

