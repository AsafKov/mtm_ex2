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

    void Medic::attack(const unordered_map<int, SharedPtr> &characters, int boardWidth, int boardHeight,
                       GridPoint dst){
        int target_key = Character::calculateKey(dst.row, dst.col, boardWidth, boardHeight);
        if(dst == location || characters.find(target_key) == characters.end()){
            throw IllegalTarget();
        }
        SharedPtr target = characters.find(target_key)->second;
        if(team == target->getTeam()){
            target->applyDamage(-power);
        } else {
            if(ammo < AMMO_COST){
                throw OutOfAmmo();
            }
            target->applyDamage(power);
            ammo -= AMMO_COST;
        }
    }
}



