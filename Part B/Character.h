
#ifndef CHARACTER
#define CHARACTER
#include "Auxiliaries.h"

namespace mtm {

    class Character {
    private:
        const static units_t AMMO_COST = 1;

    protected:
        Character(Team team, units_t health, units_t ammo, units_t attack_range, units_t power, const GridPoint& location = GridPoint(0, 0));

        Team team;
        units_t health;
        units_t ammo;
        units_t attack_range;
        units_t power;
        GridPoint location;

    public:
        Team getTeam() const;
        bool  isTeamMember(const Character* character) const;
        void setDamage(units_t damage);
        bool isDead() const;
        units_t getAmmoCount() const;
        units_t getAmmoCost() const;
        units_t getTargetAmmoCost(const Character* target) const;
        units_t distance(const GridPoint& point) const;
        bool isInAttackRange(const GridPoint& point) const;
        void setLocation(const GridPoint& location);
        GridPoint getLocation() const;
    };

}

#endif // #ifndef CHARACTER
