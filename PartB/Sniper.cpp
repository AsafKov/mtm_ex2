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

    bool Sniper::isDestinationInRange(GridPoint coordinates) const {
        return distanceFromCurrentLocation(coordinates) <= MOVED_RANGE;
    }

    void Sniper::isInAttackRange(GridPoint coordinates) const {
        if(distanceFromCurrentLocation(coordinates) > attack_range
               || distanceFromCurrentLocation(coordinates) < ceil((double)attack_range/2)){
            throw OutOfRange();
        }
    }

    void Sniper::attack(const unordered_map<int, Character::SharedPtr> &characters, int width, int height,
                        GridPoint coordinates) {

        int target_key = calculateKey(coordinates, width);
        if(characters.find(target_key) == characters.end()){
            throw IllegalTarget();
        }
        SharedPtr target = characters.find(target_key)->second;
        if(team == target->getTeam()){
            throw IllegalTarget();
        }
        if(++attacks_counter % 3 == 0){
            target->dealDamage(power*2);
        } else {
            target->dealDamage(power);
        }
        updateAmmo();
    }
}

