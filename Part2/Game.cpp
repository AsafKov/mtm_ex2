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

    void Game::addCharacter(const Game::GridPoint &coordinates, const SharedPtr &character) {
        if (!isValidLocation(coordinates)) {
            throw IllegalCell();
        }
        int newKey = Character::calculateKey(coordinates.row, coordinates.col, width);;
        if (charactersMap.find(newKey) != charactersMap.end()) {
            throw CellOccupied();
        }
        character->setLocation(coordinates);
        charactersMap[Character::calculateKey(coordinates.row, coordinates.col, width)] = character;
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
        int src_key = Character::calculateKey(src_coordinates.row, src_coordinates.col, width);
        int dst_key = Character::calculateKey(dst_coordinates.row, dst_coordinates.col, width);
        if (charactersMap.find(src_key) == charactersMap.end()) {
            throw CellEmpty();
        }
        SharedPtr character = charactersMap[src_key];
        if (charactersMap.find(dst_key) != charactersMap.end()) {
            throw CellOccupied();
        }
        if (!character->isDestinationInRange(dst_coordinates)) {
            throw MoveTooFar();
        }
        charactersMap.erase(src_key);
        charactersMap[dst_key] = character;
        character->setLocation(dst_coordinates);
    }

    void Game::attack(const GridPoint &attacker_location, const GridPoint &destination) {
        if (!isValidLocation(attacker_location) || !isValidLocation(destination)) {
            throw IllegalCell();
        }
        int src_key = Character::calculateKey(attacker_location.row, attacker_location.col, width);
        if (charactersMap.find(src_key) == charactersMap.end()) {
            throw CellEmpty();
        }
        SharedPtr attacker = charactersMap.find(src_key)->second;

        if (!attacker->isInAttackRange(destination)) {
            throw OutOfRange();
        }
        attacker->attack(charactersMap, width, height, destination);
        removeDeadCharacters();
    }

    void Game::reload(const GridPoint &coordinates) {
        if (!isValidLocation(coordinates)) {
            throw IllegalCell();
        }
        int key = Character::calculateKey(coordinates.row, coordinates.col, width);
        if (charactersMap.find(key) == charactersMap.end()) {
            throw CellEmpty();
        }
        SharedPtr character = charactersMap.find(key)->second;
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

    std::ostream &operator<<(std::ostream &os, const Game &game) {
        string output = string();
        int key;
        Game::SharedPtr character;
        int i;
        for (int row = 0; row < game.height; row++) {
            for (int col = 0; col < game.width; col++) {
                i = 1;
                if (row < col) {
                    i *= -1;
                }
                key = (row * game.width + col) * i;
                if (game.charactersMap.find(key) == game.charactersMap.end()) {
                    output += EMPTY_CELL;
                } else {
                    character = game.charactersMap.find(key)->second;
                    if (character->getType() == SOLDIER) {
                        if (character->getTeam() == POWERLIFTERS) {
                            output += SOLDIER_CELL_PL;
                        } else {
                            output += SOLDIER_CELL_CF;
                        }
                    }
                    if (character->getType() == MEDIC) {
                        if (character->getTeam() == POWERLIFTERS) {
                            output += MEDIC_CELL_PL;
                        } else {
                            output += MEDIC_CELL_CF;
                        }
                    }
                    if (character->getType() == SNIPER) {
                        if (character->getTeam() == POWERLIFTERS) {
                            output += SNIPER_CELL_PL;
                        } else {
                            output += SNIPER_CELL_CF;
                        }
                    }
                }
            }
        }
        return printGameBoard(os, output.c_str(), output.c_str() + sizeof(char) * game.width * game.height, game.width);
    }

    bool Game::isOver(Team *winningTeam) {
        bool powerlifters_present = false;
        bool crossfitters_present = false;
        SharedPtr current_character;
        for (const auto &item : charactersMap) {
            current_character = item.second;
            if (current_character->getTeam() == POWERLIFTERS) {
                powerlifters_present = true;
            } else {
                crossfitters_present = true;
            }
        }
        if (winningTeam == nullptr) {
            return !crossfitters_present || !powerlifters_present;
        }
        if (powerlifters_present && crossfitters_present) {
            return false;
        }
        if (powerlifters_present && !crossfitters_present) {
            *winningTeam = POWERLIFTERS;
            return true;
        }
        if (!powerlifters_present && crossfitters_present) {
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
