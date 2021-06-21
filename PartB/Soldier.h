#ifndef SOLDIER

#include "Character.h"

namespace mtm {

    class Soldier : public Character {
    private:
        static const units_t RELOAD_CREDIT = 3;
        static const units_t MOVE_RANGE = 3;

    public:
        Soldier(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type);
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
         * Operate attack on ANY player - null player or player from the same team/type
         * while target destination in attack range, and is on the same column OR row,
         * updating attacker ammo,
         * causing target damage equals to attacker power, only if target is not ally, then updating attacker ammo
         * @param characters
         * @param boardWidth
         * @param boardHeight
         * @param coordinates
         * @throws IllegalTarget while destination in not on the same column OR row
         */
        void attack(const unordered_map<int, SharedPtr> &characters, int boardWidth, int boardHeight,
                    GridPoint coordinates) override;
        /**
         * Operate splash damage on players that are in 1-(attack range)/3 radius from attacked coordinates
         * causing affected targets in radius damage equals to (attacker power)/2,
         * only if target is and not ally, cannot cause self damage
         * @param characters
         * @param boardWidth
         * @param boardHeight
         * @param dst
         */
        void dealSplashDamage(const unordered_map<int, Character::SharedPtr> &characters,
                               int boardWidth, int boardHeight, const GridPoint &dst);
        };
}
#endif