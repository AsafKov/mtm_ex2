#ifndef MEDIC

#include "Character.h"

namespace mtm {

    class Medic : public Character {
    private:
        static const units_t AMMO_COST{0};
        static const units_t RELOAD_CREDIT{5};
        static const units_t MOVE_RANGE{5};
//        units_t min_attacked_area_range = 1;
//        units_t max_attacked_area_range = attack_range;
//        units_t attacked_area_damage = power;

    public:
        Medic(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type);
        Character *clone() const override;
        void reload() override;
        bool isInAttackRange(GridPoint dst_coordinates) const override;
        units_t getAmmoCost() const override;
        bool isDestinationInRange(GridPoint dst_coordinates) const override;
        void attack(Character* target,const GridPoint& destination);
    };
}

#endif  //  #ifndef MEDIC