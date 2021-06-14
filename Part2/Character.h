#ifndef CHARACTER
#define CHARACTER
#include "Auxiliaries.h"
#include <vector>

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
        ~Character() = default;
        virtual void reload();
        virtual bool isDestinationInRange(GridPoint dst_coordinates) const;
        virtual bool isInAttackRange(GridPoint dst_coordinates) const;
        virtual void attack();
        virtual units_t getAmmoCost() const;
        Team getTeam() const;
        bool  isTeamMember(Character* character) const;
        void doDamage(units_t damage);
        bool isDead() const;
        CharacterType getType() const;
        units_t getAmmoCount() const;
        units_t getTargetAmmoCost(const Character* target) const;
        units_t distanceFromCurrentLocation(const GridPoint& point) const;
        void setLocation(const GridPoint& location);
        GridPoint getLocation() const;
    };

}

#endif // #ifndef CHARACTER
