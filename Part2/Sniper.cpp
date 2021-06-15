#include "Sniper.h"

namespace mtm {

    Sniper::Sniper(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type)
            : Character(team, health, ammo, attack_range, power, type) {}

    Character *Sniper::clone() const{
        return new Sniper(*this);
    }

    void Sniper::reload() {
        this->ammo += RELOAD_CREDIT;
    }

    bool Sniper::isDestinationInRange(GridPoint dst_coordinates) const {
        return distanceFromCurrentLocation(dst_coordinates) <= MOVED_RANGE;
    }

    bool Sniper::isInAttackRange(GridPoint dst_coordinates) const {
        return distanceFromCurrentLocation(dst_coordinates) <= attack_range
               && distanceFromCurrentLocation(dst_coordinates) >= ceil((double)attack_range/2);
    }

    void Sniper::attack(const unordered_map<int, Character::SharedPtr> &characters, int boardWidth, int boardHeight,
                        GridPoint dst) {

        int target_key = calculateKey(dst.row, dst.col, boardWidth);
        if(characters.find(target_key) == characters.end()){
            throw IllegalTarget();
        }
        SharedPtr target = characters.find(target_key)->second;
        if(team == target->getTeam()){
            throw IllegalTarget();
        }
        if(ammo < AMMO_COST){
            throw OutOfAmmo();
        }
        if(++attacks_counter % 3 == 0){
            target->applyDamage(power*2);
        } else {
            target->applyDamage(power);
        }
        ammo -= AMMO_COST;
    }
}

