#ifndef SNIPER
#include "Character.h"

namespace mtm {

    class Sniper : public Character {
    private:
        static const units_t RELOAD_CREDIT = 2;
        static const units_t MOVED_RANGE = 4;
        units_t attacks_counter = 0;

    public:
        Sniper(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type);
        Character *clone() const override;
        void reload() override;
        /**
         * Checks if destination coordinates is in set move range
         * @param coordinates
         * @return true if in range, false otherwise
         */
        bool isDestinationInRange(GridPoint coordinates) const override;
        /**
         * Checks if destination coordinates is in set attack range, range is set as a ring
         * max radius is attack range, and min radius is (min range)/2
         * @param coordinates
         * @throws OutOfRange
         */
        void isInAttackRange(GridPoint coordinates) const override;
        /**
         * Operate attack on player only is it's not from the same team/type, and not null player
         * while target destination is in attack range
         * causing target damage equals to attacker power, then updating attacker ammo
         * in every 3rd strike - causing target damage equals to (attacker power)*2, then updating attacker ammo
         * @param characters
         * @param boardWidth
         * @param boardHeight
         * @param coordinates
         * @throws IllegalTarget while destination in not on the same column OR row
         */
        void attack(const unordered_map<int, Character::SharedPtr> &characters, int boardWidth, int boardHeight,
                    GridPoint coordinates) override;
    };
}

#endif  //  #ifndef SNIPER