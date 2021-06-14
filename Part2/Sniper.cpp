#include "Sniper.h"

namespace mtm {

    Sniper::Sniper(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type)
            : Character(team, health, ammo, attack_range, power, type) {}

    Character *Sniper::clone() const{
        return new Sniper(*this);
    }

    void Sniper::reload() {
        this->ammo += mtm::Sniper::RELOAD_CREDIT;
    }

    bool Sniper::isDoubleDamage() {
        return (this->attacks_counter++) % 3 == 0;
    }

    void Sniper::attack(Character *target, const GridPoint &destination) {
        if (target == nullptr || isTeamMember(target)) {
            //todo: invalid target
        }
        if (!this->isInAttackRange(destination)) {
            //todo: invalid location
        }
        if (this->ammo) {
            //todo: no ammo
        }
        this->ammo -= getAmmoCost();
        if (isDoubleDamage()) {
            target->doDamage(this->power * 2);
        }
        target->doDamage(this->power);
//        doAttackedAreaDamage();
    }

    void Sniper::doAttackedAreaDamage(Character *potential_effected_target,
                                      const GridPoint &potential_effected_destination) {
        units_t distance = this->distanceFromCurrentLocation(potential_effected_destination);
        if (distance < min_attacked_area_range || distance > max_attacked_area_range) {
            potential_effected_target->doDamage(this->attacked_area_damage);
        }
    }

    bool Sniper::isDestinationInRange(GridPoint dst_coordinates) const {
        return distanceFromCurrentLocation(dst_coordinates) <= mtm::Sniper::MOVED_RANGE;
    }

    bool Sniper::isInAttackRange(GridPoint dst_coordinates) const {
        return distanceFromCurrentLocation(dst_coordinates) <= attack_range
               && distanceFromCurrentLocation(dst_coordinates) >= attack_range / 2;
    }
}

