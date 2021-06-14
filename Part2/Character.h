#ifndef CHARACTER
#define CHARACTER
#include "Auxiliaries.h"
#include <vector>
#include "Exceptions.h"

namespace mtm {

    class Character {
    private:
        static const units_t AMMO_COST = 1;

    protected:
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

    public:
        virtual ~Character() = default;
        virtual Character *clone() const = 0;
        virtual void reload() = 0;
        virtual bool isDestinationInRange(GridPoint dst_coordinates) const = 0;
        virtual bool isInAttackRange(GridPoint dst_coordinates) const = 0;
        virtual void attack(Character* target, const GridPoint& destination) = 0;
        Team getTeam() const;
        bool isTeamMember(Character* character) const;
        CharacterType getType() const;
        units_t getPower() const;
        units_t getAmmoCost() const;
        units_t getAmmoCount() const;
        units_t getAttackRange() const;
        void doDamage(units_t damage);
        bool isDead() const;
        GridPoint getLocation() const;
        void setLocation(const GridPoint& location);
        units_t distanceFromCurrentLocation(const GridPoint& point) const;
    };

}

#endif // #ifndef CHARACTER
