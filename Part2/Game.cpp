#include "Game.h"

namespace mtm {
    Game::Game(int height, int width) : width(width), height(height) {
        characters = vector<SharedPtr>();
    }

    Game::Game(const Game &game) : width(game.width), height(game.height) {
        characters = vector<SharedPtr>();
        auto iterator = game.characters.begin();
        while (iterator != game.characters.end()) {
            characters.push_back(SharedPtr((*iterator)->clone()));
        }
    }

    Game &Game::operator=(const Game &game) {
        if (this == &game) {
            return *this;
        }
        height = game.height;
        width = game.width;

        return *this;
    }

    Game::~Game() {
        auto iterator = characters.begin();
        while (iterator != characters.end()) {
            delete (*iterator).get();
        }
    }

    void Game::addCharacter(const Game::GridPoint &coordinates, const SharedPtr &character) {
        if (!isValidLocation(coordinates)) {
            throw IllegalCell();
        }

        if (characterInCell(coordinates) != nullptr) {
            throw CellOccupied();
        }
        character->setLocation(coordinates);
        characters.push_back(character);
    }

    bool Game::isValidLocation(const Game::GridPoint point) const {
        return (point.row >= 0 && point.row <= height) && (point.col >= 0 && point.col <= width);
    }

    Game::SharedPtr Game::makeCharacter(CharacterType type, Team team, Game::unit_t health, Game::unit_t ammo,
                                        Game::unit_t range, Game::unit_t power) {
        if (health == 0 || range == 0 || ammo < 0 || power < 0) {
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
        SharedPtr character = characterInCell(src_coordinates);
        if (character == nullptr) {
            throw CellEmpty();
        }
        //TODO: can move 0 steps?
        if (characterInCell(dst_coordinates) != nullptr) {
            throw CellOccupied();
        }
        if (!character->isDestinationInRange(dst_coordinates)) {
            throw OutOfRange();
        }
        character->setLocation(dst_coordinates);
    }

    Game::SharedPtr &Game::characterInCell(const GridPoint &coordinates) {
        auto it = characters.begin();
        while (it != characters.end()) {
            if ((*it)->getLocation() == coordinates) {
                return *it;
            }
            it++;
        }
        //TODO: Is valid return value null?
        return *it;
    }

    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
        if (!isValidLocation(src_coordinates) || !isValidLocation(dst_coordinates)) {
            throw IllegalCell();
        }
        SharedPtr character = characterInCell(src_coordinates);
        if (character == nullptr) {
            throw CellEmpty();
        }

        if (!character->isInAttackRange(dst_coordinates)) {
            throw OutOfRange();
        }

        if (character->getAmmoCount() < character->getAmmoCost()) {
            throw OutOfAmmo();
        }

        if (characterInCell(dst_coordinates) == nullptr &&
            (character->getType() == MEDIC || character->getType() == SNIPER)) {
            throw IllegalTarget();
        }
    }

    void Game::reload(const GridPoint &coordinates) {
        if (!isValidLocation(coordinates)) {
            throw IllegalCell();
        }
        SharedPtr character = characterInCell(coordinates);
        if (character == nullptr) {
            throw CellEmpty();
        }
        character->reload();
    }
}
