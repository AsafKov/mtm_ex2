#include "Game.h"

namespace mtm {
    Game::Game(int height, int width) : width(width), height(height) {}

    Game::Game(const Game &game) : width(game.width), height(game.height) {
        copyCharacterMap(game.charactersMap);
    }

    Game &Game::operator=(const Game &game) {
        if (this == &game) {
            return *this;
        }
        copyCharacterMap(game.charactersMap);
        height = game.height;
        width = game.width;
        return *this;
    }

    Game::~Game() {
        charactersMap.clear();
    }

    shared_ptr<Character> Game::getCharacterMap(const GridPoint& coordinates, units_t width) {
        return charactersMap.find((int)Character::calculateKey(coordinates, width))->second;
    }

    void Game::eraseCharacterMap(const GridPoint& coordinates, units_t width) {
        charactersMap.erase((int)Character::calculateKey(coordinates, width));
    }

    void Game::addCharacterMap(const GridPoint& coordinates, units_t width, const SharedPtr &character) {
        charactersMap[(int)Character::calculateKey(coordinates, width)] = character;
    }

    bool Game::foundCharactersMap(const GridPoint& coordinates, units_t width) {
        return charactersMap.find((int)Character::calculateKey(coordinates, width)) != charactersMap.end();
    }

    void Game::addCharacter(const Game::GridPoint &coordinates, const SharedPtr &character) {
        if (!isValidLocation(coordinates)) {
            throw IllegalCell();
        }
        if (foundCharactersMap(coordinates, width)) {
            throw CellOccupied();
        }
        character->setLocation(coordinates);
        addCharacterMap(coordinates,width,character);
    }

    bool Game::isValidLocation(const Game::GridPoint point) const {
        return (point.row >= 0 && point.row < height) && (point.col >= 0 && point.col < width);
    }

    Game::SharedPtr Game::makeCharacter(CharacterType type, Team team, Game::unit_t health, Game::unit_t ammo,
                                        Game::unit_t range, Game::unit_t power) {
        if (health == 0 || range < 0 || ammo < 0 || power < 0) {
            throw IllegalArgument();
        }
        switch (type) {
            case SOLDIER: {
                SharedPtr character(new Soldier(team, health, ammo, range, power, SOLDIER));
                return character;
            }
            case MEDIC: {
                SharedPtr character(new Medic(team, health, ammo, range, power, MEDIC));
                return character;
            }
            default: {
                SharedPtr character(new Sniper(team, health, ammo, range, power, SNIPER));
                return character;
            }
        }
    }

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
        if (!isValidLocation(src_coordinates) || !isValidLocation(dst_coordinates)) {
            throw IllegalCell();
        }
        if (!foundCharactersMap(src_coordinates, width)) {
            throw CellEmpty();
        }
        SharedPtr character = getCharacterMap(src_coordinates, width);
        if (foundCharactersMap(dst_coordinates, width)) {
            throw CellOccupied();
        }
        if (!character->isDestinationInRange(dst_coordinates)) {
            throw MoveTooFar();
        }
        eraseCharacterMap(src_coordinates,width);
        addCharacterMap(dst_coordinates,width,character);
        character->setLocation(dst_coordinates);
    }

    void Game::attack(const GridPoint &attacker_coordinates, const GridPoint &dst_coordinates) {
        if (!isValidLocation(attacker_coordinates) || !isValidLocation(dst_coordinates)) {
            throw IllegalCell();
        }
        if (!foundCharactersMap(attacker_coordinates, width)) {
            throw CellEmpty();
        }
        SharedPtr attacker = getCharacterMap(attacker_coordinates, width);

        if (!attacker->isInAttackRange(dst_coordinates)) {
            throw OutOfRange();
        }
        if(attacker->isOutOfAmmo() && attacker->getType()!=MEDIC){
            throw OutOfAmmo();
        }
        attacker->attack(charactersMap, width, height, dst_coordinates);
        removeDeadCharacters();
    }

    void Game::reload(const GridPoint &coordinates) {
        if (!isValidLocation(coordinates)) {
            throw IllegalCell();
        }
        if (!foundCharactersMap(coordinates, width)) {
            throw CellEmpty();
        }
        SharedPtr character = getCharacterMap(coordinates, width);
        character->reload();
    }

    void Game::removeDeadCharacters() {
        using std::vector;
        vector<int> toRemove = vector<int>();
        SharedPtr character;
        for (const auto &item : charactersMap) {
            character = item.second;
            if (character->isDead()) {
                toRemove.push_back(item.first);
            }
        }
        for (auto iterator = toRemove.begin(); iterator != toRemove.end(); iterator++) {
            charactersMap.erase(*iterator);
        }
    }

    void Game::cellInOutput(string output, Team team, char CELL_PL , char CELL_CF) {
        if (team == POWERLIFTERS) {
            output += CELL_PL;
        } else {
            output += CELL_CF;
        }
    }

    std::ostream &operator<<(std::ostream &os, const Game &game) {
        string output = string();
        Game::SharedPtr character;
        for (int row = 0; row < game.height; row++) {
            for (int col = 0; col < game.width; col++) {
                int key = character->calculateKey(GridPoint(row, col), game.width);
                if (game.charactersMap.find(key) == game.charactersMap.end()) {
                    output += EMPTY_CELL;
                } else {
                    character = game.charactersMap.find(key)->second;
                    if (character->getType() == SOLDIER) {
                        Game::cellInOutput(output, character->getTeam(),SOLDIER_CELL_PL,SOLDIER_CELL_CF);
                    }
                    if (character->getType() == MEDIC) {
                        Game::cellInOutput(output, character->getTeam(),MEDIC_CELL_PL,MEDIC_CELL_CF);
                    }
                    if (character->getType() == SNIPER) {
                        Game::cellInOutput(output, character->getTeam(),SNIPER_CELL_PL,SNIPER_CELL_CF);
                    }
                }
            }
        }
        return printGameBoard(os, output.c_str(), output.c_str() + sizeof(char) * game.width * game.height, game.width);
    }

    bool Game::isOver(Team *winningTeam) {
        bool is_powerlifters_winners = false;
        bool is_crossfitters_winners = false;
        SharedPtr current_character;
        for (const auto &item : charactersMap) {
            current_character = item.second;
            if (current_character->getTeam() == POWERLIFTERS) {
                is_powerlifters_winners = true;
            } else {
                is_crossfitters_winners = true;
            }
        }
        if (winningTeam == nullptr) {
            return !is_crossfitters_winners || !is_powerlifters_winners;
        }
        if (is_powerlifters_winners && is_crossfitters_winners) {
            return false;
        }
        if (is_powerlifters_winners && !is_crossfitters_winners) {
            *winningTeam = POWERLIFTERS;
            return true;
        }
        if (!is_powerlifters_winners && is_crossfitters_winners) {
            *winningTeam = CROSSFITTERS;
            return true;
        }
        return false;
    }

    void Game::copyCharacterMap(const unordered_map<int, Game::SharedPtr> &characters) {
        unordered_map<int, SharedPtr> temp_map;
        for (const auto &item : characters) {
            temp_map[item.first] = SharedPtr(item.second->clone());
        }
        charactersMap.clear();
        charactersMap = unordered_map<int, SharedPtr>(temp_map);
    }
}
