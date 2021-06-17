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
        void isInAttackRange(GridPoint coordinates) const override;
        bool isDestinationInRange(GridPoint coordinates) const override;
        void attack(const unordered_map<int, SharedPtr> &characters, int boardWidth, int boardHeight,
                            GridPoint coordinates) override;
    };
}

#endif  //  #ifndef MEDIC