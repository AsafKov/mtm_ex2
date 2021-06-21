#ifndef MEDIC

#include "Character.h"

namespace mtm {

    class Medic : public Character {
    private:
        static const units_t RELOAD_CREDIT{5};
        static const units_t MOVE_RANGE{5};

    public:
        Medic(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type);
        Character *clone() const override;
        void reload() override;
        /**
         * Checks if destination coordinates is in set move range
         * @param coordinates
         * @return true if in range, false otherwise
         */
        bool isDestinationInRange(GridPoint coordinates) const override;
        /**
         * Checks if destination coordinates is in set attack range
         * @param coordinates
         * @throws OutOfRange
         */
        void isInAttackRange(GridPoint coordinates) const override;
        /**
         * Operate attack on player from the same team/type, but not null player
         * while target destination in attack range
         * causing target damage equals to attacker power, only if target is not ally, only then updating attacker ammo
         * if target is ally, adding to target's health units equals to attacker power
         * @param characters
         * @param boardWidth
         * @param boardHeight
         * @param coordinates
         * @throws IllegalTarget while destination in not on the same column OR row
         * @throws OutOfAmmo if ammunition left is smaller than ammunition cost
         */
        void attack(const unordered_map<int, SharedPtr> &characters, int boardWidth, int boardHeight,
                            GridPoint coordinates) override;
    };
}

#endif  //  #ifndef MEDIC