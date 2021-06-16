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
        bool isDestinationInRange(GridPoint coordinates) const override;
        void reload() override;
        Character *clone() const override;
        bool isInAttackRange(GridPoint coordinates) const override;
        void attack(const unordered_map<int, Character::SharedPtr> &characters, int boardWidth, int boardHeight,
                    GridPoint coordinates) override;
    };
}

#endif  //  #ifndef SNIPER