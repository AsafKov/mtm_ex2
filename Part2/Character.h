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
        static const units_t AMMO_COST = 1;
        Character(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, CharacterType type)
            : location(-1,-1), team(team), type(type), health(health), ammo(ammo), attack_range(attack_range),
                power(power){}
        Character(const Character &character) = default;

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
        virtual bool isInAttackRange(GridPoint dst_coordinates) const = 0;
        virtual void attack(const unordered_map<int, SharedPtr> &characters, int boardWidth, int boardHeight,
                            GridPoint dst) = 0;
        Team getTeam() const;
        bool isTeamMember(Character* character) const;
        CharacterType getType() const;
        units_t getPower() const;
        units_t getAmmoCost() const;
        units_t getAmmoCount() const;
        units_t getAttackRange() const;
        void applyDamage(units_t damage);
        bool isDead() const;
        GridPoint getLocation() const;
        void setLocation(const GridPoint& location);
        units_t distanceFromCurrentLocation(const GridPoint& point) const;
    };

}

#endif // #ifndef CHARACTER
