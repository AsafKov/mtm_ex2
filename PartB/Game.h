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

        /**
         * @param point
         * @return True - if the point is within the boundaries of the board, False otherwise
         */
        bool isValidLocation(GridPoint point) const;
        /**
         * Deep copy the contents of a given map of characters into the game's map
         * @param characters
         */
        void copyCharactersMap(const unordered_map<int, SharedPtr> &characters);
        /**
         * @param team - Team of the character in a cell
         * @param CELL_PL - Character of the role if team is Powerlifters
         * @param CELL_CF - Character of the role if the team is Crossfitters
         * @return - character to print according to the team
         */
        static char getBoardCellChar(Team team, char CELL_PL , char CELL_CF);
        /**
         * Removes dead characters from the game
         */
        void removeDeadCharacters();
        /**
         * @param cell_coordinates
         * @return - returns a pointer to a character in a given cell defined by coordinates
         */
        shared_ptr<Character> getCharacterInCell(const GridPoint& cell_coordinates);
        /**
         * @param cell_coordinates
         * @return True - if there is a character in the given cell, False otherwise
         */
        bool isCellOccupied(const GridPoint& cell_coordinates);
        /**
         * Adds a character to the game board
         * @param coordinates - Cell to add the character to
         * @param character - Character to add
         */
        void addCharacterToMap(const GridPoint& coordinates, const SharedPtr &character);

    public:
        /**
         * Deletes game by deleting the characters map
         */
        ~Game();
        Game(int height, int width);
        Game(const Game &game);
        Game &operator=(const Game &game);
        /**
         * @param os
         * @param game
         * @return An ostream containing the cell-by-cell characters representing the board game
         */
        friend std::ostream &operator<<(std::ostream &os, const Game &game);
        /**
         * Creates a character with the give parameters
         * @param type
         * @param team
         * @param health
         * @param ammo
         * @param range
         * @param power
         * @return A shared_ptr object to the new character
         * @throws IllegalArgument - if one of the parameter values are illegal
         */
        static SharedPtr makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range,
                                       units_t power);
        /**
         * Add character to the board
         * @param coordinates
         * @param character
         * @throws IllegalCell - If the cell isn't within the board boundaries
         * @throws CellOccupied - If the cell is occupied
         */
        void addCharacter(const GridPoint &coordinates, const SharedPtr &character);
        /**
         * Moves a character from a source cell to a destination
         * @param src_location
         * @param dst_location
         * @throws IllegalCell - If the destination cell isn't with the board boundaries
         * @throws CellEmpty - If there isn't a character in the source cell
         * @throws MoveTooFar - If the destination isn't within the character movement range
         * @throw CellOccupied - If the destination cell is occupied
         */
        void move(const GridPoint &src_location, const GridPoint &dst_location);
        /**
         * Attack the target coordinates with the characters in attacker_coordinates
         * @param attacker_coordinates
         * @param target_coordinates
         * @throws IllegalCell - If the destination cell isn't with the board boundaries
         * @throws CellEmpty - If there isn't a character in the source cell
         * @throws OutOfAmmo - If the character is out of ammo
         *                      (If medic - case handled within the character attack function)
         */
        void attack(const GridPoint &attacker_coordinates, const GridPoint &target_coordinates);
        /**
         * Do a reload for the character in a given coordinates
         * @param coordinates
         * @throws IllegalCell - If the destination cell isn't with the board boundaries
         * @throws CellEmpty - If there isn't a character in the source cell
         */
        void reload(const GridPoint &coordinates);
        /**
         * @param winningTeam - Set pointer value to the winning team
         * @return True - if game has ended (at least on of the team no longer has players on the board), False otherwise
         */
        bool isOver(Team *winningTeam = nullptr);
    };

    std::ostream &operator<<(std::ostream &os, const Game &game);
}

#endif //MTM_EX2_GAME_H
