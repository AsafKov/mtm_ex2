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
        /**
         * Character constructor, setting default location to an off-board location
         * @param team
         * @param health
         * @param ammo
         * @param attack_range
         * @param power
         * @param type
         */
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
        /**
         * copys character
         * @return new character, same as copied character
         */
        virtual Character *clone() const = 0;
        /**
         * Claims ammunition, as set in each characters type's reload credit
         */
        virtual void reload() = 0;
        virtual bool isDestinationInRange(GridPoint dst_coordinates) const = 0;
        virtual void isInAttackRange(GridPoint dst_coordinates) const = 0;
        virtual void attack(const unordered_map<int, SharedPtr> &characters, int boardWidth, int boardHeight,
                            GridPoint dst) = 0;
        /**
         * Generates unique ID for each character, depending on it's current coordinates and game board width
         * @param coordinates
         * @param width
         * @return Key: character ID
         */
        static int calculateKey(const GridPoint& coordinates, int width);
        /**
         * @return character team - POWERLIFTERS/ CROSSFITTERS
         */
        inline Team getTeam() const {
            return team;}
            ;
        /**
         * @return character type SOLDIER/MEDIC/SNIPER
         */
        inline CharacterType getType() const {
            return type;
        };
        /**
         * causing damage to health units
         * @param damage
         */
        inline void dealDamage(units_t damage) {
            health-=damage;
        };
        /**
         *
         * @return True if character is dead and has no more health units, false otherwise
         */
        inline bool isDead() const {
            return health <= 0;
        };
        /**
         *
         * @return True if ammunition left is smaller than ammunition cost
         */
        inline bool isOutOfAmmo() const{
            return (ammo < AMMO_COST);
        };
        /**
         * removing ammunition cost from ammunition left
         */
        inline void updateAmmo() {
            ammo -= AMMO_COST;
        };
        /**
         * updating coordinates for character
         * @param coordinates
         */
        inline void setLocation(const GridPoint& coordinates) {
            location = coordinates;
        };
        /**
         *
         * @param coordinates
         * @return the distance units between character's current location and sent coordinates point
         */
        units_t distanceFromCurrentLocation(const GridPoint& coordinates) const;
    };

}

#endif // #ifndef CHARACTER
