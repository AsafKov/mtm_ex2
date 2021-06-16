#include "Soldier.h"
namespace mtm {
    Soldier::Soldier(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type)
            : Character(team, health, ammo, attack_range, power, type) {}

    Character *Soldier::clone() const{
        return new Soldier(*this);
    }

    void Soldier::reload() {
        this->ammo += mtm::Soldier::RELOAD_CREDIT;
    }

    bool Soldier::isDestinationInRange(GridPoint dst_coordinates) const{
        return distanceFromCurrentLocation(dst_coordinates) <= mtm::Soldier::MOVE_RANGE;
    }

    bool Soldier::isInAttackRange(GridPoint dst_coordinates) const {
        if(dst_coordinates.row != location.row && dst_coordinates.col != location.col){
            throw IllegalTarget();
        }
        return distanceFromCurrentLocation(dst_coordinates) <= attack_range;
    }

    void Soldier::attack(const unordered_map<int, Character::SharedPtr> &characters, int width, int height,
                         GridPoint dst_coordinates){
        int target_key = calculateKey(dst_coordinates, width);
        updateAmmo();
        if(characters.find(target_key) != characters.end()){
            SharedPtr target = characters.find(target_key)->second;
            if(team != target->getTeam()){
                target->dealDamage(power);
            }
        }
        dealSplashDamage(characters, width, height, dst_coordinates);
    }

    void Soldier::dealSplashDamage(const unordered_map<int, Character::SharedPtr> &characters, int width, int height,
                                    const GridPoint &dst) {
        const units_t area_radius = ceil((double) attack_range / 3);
        const units_t splash_damage = ceil((double) power / 2);
        int currentKey;
        for (auto i = (units_t)fmax(dst.row - area_radius, 0); i <= fmin(dst.row + area_radius, height); i++){
            for (auto j = (units_t)fmax(dst.col - area_radius, 0); j <= fmin(dst.col + area_radius, width); j++){
                GridPoint current_cell = GridPoint(i, j);
                currentKey = calculateKey(current_cell, width);
                if (GridPoint::distance(current_cell, dst) > area_radius) {
                    continue;
                }
                if(characters.find(currentKey) == characters.end()){
                    continue;
                }
                SharedPtr affected_target = characters.find(currentKey)->second;
                if (team != affected_target.get()->getTeam()) {
                    affected_target->dealDamage(splash_damage);
                }
            }
        }
    }
}

