#ifndef MTM_EX2_GAME_H
#define MTM_EX2_GAME_H

#include "Medic.h"
#include "Sniper.h"
#include "Soldier.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
#include <memory>
#include <vector>
#include <unordered_map>

using std::unordered_map;
using std::shared_ptr;


namespace mtm {
    const static char EMPTY_CELL = ' ';
    const static char SOLDIER_CELL_PL = 'S';
    const static char SOLDIER_CELL_CF = 's';
    const static char MEDIC_CELL_PL = 'M';
    const static char MEDIC_CELL_CF = 'm';
    const static char SNIPER_CELL_PL = 'N';
    const static char SNIPER_CELL_CF = 'n';

    class Game {
        typedef mtm::Character Character;
        typedef mtm::GridPoint GridPoint;
        typedef std::shared_ptr<Character> SharedPtr;

        units_t width;
        units_t height;
        unordered_map<int, SharedPtr> charactersMap;

        bool isValidLocation(GridPoint point) const;
        void copyCharactersMap(const unordered_map<int, SharedPtr> &characters);
        static char getBoardCellChar(Team team, char CELL_PL , char CELL_CF);
        void removeDeadCharacters();
        shared_ptr<Character> getCharacterInCell(const GridPoint& dst_coordinates);
        bool isCellOccupied(const GridPoint& dst_coordinates);
        void addCharacterToMap(const GridPoint& coordinates, const SharedPtr &character);

    public:
        ~Game();
        Game(int height, int width);
        Game(const Game &game);
        Game &operator=(const Game &game);
        friend std::ostream &operator<<(std::ostream &os, const Game &game);
        static SharedPtr makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range,
                                       units_t power);
        void addCharacter(const GridPoint &coordinates, const SharedPtr &character);
        void move(const GridPoint &src_location, const GridPoint &dst_location);
        void attack(const GridPoint &attacker_location, const GridPoint &destination);
        void reload(const GridPoint &coordinates);
        bool isOver(Team *winningTeam = nullptr);
    };

    std::ostream &operator<<(std::ostream &os, const Game &game);
}

#endif //MTM_EX2_GAME_H