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

    bool Medic::isDestinationInRange(GridPoint dst_coordinates) const {
        return distanceFromCurrentLocation(dst_coordinates) <= MOVE_RANGE;
    }

    bool Medic::isInAttackRange(GridPoint dst_coordinates) const {
        return distanceFromCurrentLocation(dst_coordinates) <= attack_range;
    }

    void Medic::attack(const unordered_map<int, SharedPtr> &characters, int width, int height,
                       GridPoint dst_coordinates){
        int target_key = Character::calculateKey(dst_coordinates.row, dst_coordinates.col, width);
        if(dst_coordinates == location || characters.find(target_key) == characters.end()){
            throw IllegalTarget();
        }
        SharedPtr target = characters.find(target_key)->second;
        if(team == target->getTeam()){
            target->dealDamage(-power);
        } else {
            if(ammo < AMMO_COST){
                throw OutOfAmmo();
            }
            target->dealDamage(power);
            ammo -= AMMO_COST;
        }
    }
}



