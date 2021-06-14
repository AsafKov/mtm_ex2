#ifndef MTM_EX2_GAME_H
#define MTM_EX2_GAME_H
#include "Medic.h"
#include "Sniper.h"
#include "Soldier.h"
#include "Auxiliaries.h"
#include <memory>
#include <vector>
#include <unordered_map>
using std::unordered_map;
using std::vector;
using std::shared_ptr;

namespace mtm{
    class Game {
        typedef int unit_t;
        typedef mtm::Character Character;
        typedef mtm::GridPoint GridPoint;
        typedef std::shared_ptr<Character> SharedPtr;

        unit_t height;
        unit_t width;
        vector<SharedPtr> characters;

        bool isValidLocation(GridPoint point) const;
    public:
        Game(int height, int width);
        Game(const Game &game);
        Game &operator=(const Game &game);
        ~Game();

        void addCharacter(const GridPoint& coordinates, const SharedPtr &character);
        void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        void attack(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
        SharedPtr &characterInCell(const GridPoint &coordinates);
        static SharedPtr makeCharacter(CharacterType type, Team team, unit_t health, unit_t ammo, unit_t range,
                                       unit_t power);
    };
}

#endif //MTM_EX2_GAME_H
