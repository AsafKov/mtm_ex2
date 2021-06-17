#ifndef CHARACTER
#define CHARACTER
#include "Auxiliaries.h"
#include <unordered_map>
#include "Exceptions.h"
#include "memory"
using std::unordered_map;
using std::shared_ptr;

namespace mtm {

    class Character {
    protected:
        Character(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type)
                : team(team), type(type), health(health), ammo(ammo), attack_range(attack_range),
                  power(power), location(-1,-1){}
        Character(const Character &character) = default;

        static const units_t AMMO_COST = 1;
        Team team;
        CharacterType type;
        units_t health;
        units_t ammo;
        units_t attack_range;
        units_t power;
        GridPoint location;

        typedef shared_ptr<Character> SharedPtr;
    public:
        virtual ~Character() = default;
        virtual Character *clone() const = 0;
        virtual void reload() = 0;
        virtual bool isDestinationInRange(GridPoint dst_coordinates) const = 0;
        virtual void isInAttackRange(GridPoint dst_coordinates) const = 0;
        virtual void attack(const unordered_map<int, SharedPtr> &characters, int boardWidth, int boardHeight,
                            GridPoint dst) = 0;
        static int calculateKey(const GridPoint& coordinates, int width);
        Team getTeam() const;
        CharacterType getType() const;
        void dealDamage(units_t damage);
        bool isDead() const;
        bool isOutOfAmmo() const;
        void updateAmmo();
        void setLocation(const GridPoint& coordinates);
        units_t distanceFromCurrentLocation(const GridPoint& point) const;
    };

}

#endif // #ifndef CHARACTER
