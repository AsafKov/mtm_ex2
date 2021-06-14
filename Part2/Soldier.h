#ifndef SOLDIER

#include "Character.h"

namespace mtm {

    class Soldier : public Character {
    private:
        static const units_t RELOAD_CREDIT = 3;
        static const units_t MOVE_RANGE = 3;
        units_t min_attacked_area_range = 1;
        units_t max_attacked_area_range = ceil((double)attack_range/3);
        units_t attacked_area_damage = ceil((double)power/2);

    public:
        Soldier(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type);
        //TODO: virtual
        virtual Character *clone() const;
        void reload() override;
        bool isInAttackRange(GridPoint dst_coordinates) const override;
        bool isDestinationInRange(GridPoint dst_coordinates) const override;
        void attack(Character *target, const GridPoint &destination);
        void doAttackedAreaDamage(const GridPoint& attack_location, Character* character);
    };
}
#endif  //  #ifndef SOLDIER