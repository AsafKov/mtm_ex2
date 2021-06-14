#ifndef SOLDIER

#include "Character.h"

namespace mtm {

    class Soldier : public Character {
    private:
        static const units_t RELOAD_CREDIT = 3;
        static const units_t MOVE_RANGE = 3;

    public:
        Soldier(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type);
        //TODO: virtual
        Character *clone() const override;
        void reload() override;
        bool isInAttackRange(GridPoint dst_coordinates) const override;
        bool isDestinationInRange(GridPoint dst_coordinates) const override;
        void attack(Character *target, const GridPoint &destination);
    };
}
#endif  //  #ifndef SOLDIER