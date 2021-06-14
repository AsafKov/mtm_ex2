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

    units_t Game::distance(const GridPoint& point1, const GridPoint& point2) {
        return GridPoint::distance(point1, point2);
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
        Character* character = characterInCell(src_coordinates);
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

    Character* Game::characterInCell(const GridPoint &coordinates) {
        int size = characters.size();
        auto it = characters.begin();
        while (it != characters.end()) {
            GridPoint point = (*it)->getLocation();
            if (point == coordinates) {
                return (*it).get();
            }
            it++;
        }
        return nullptr;
    }

    void Game::soldierAreaAttack(Character* attacker, const GridPoint &destination) {
        if(attacker->getType() == SOLDIER){
            units_t area_radius = ceil((double)attacker->getAttackRange()/3);
            units_t area_damage = ceil((double)attacker->getPower()/2);
            for(units_t i=destination.row-2 ; i <= destination.row+2 ; i++){
                for(units_t j=destination.col-2 ; j <= destination.col+2 ; j++){
                    GridPoint damaged_area = GridPoint(i,j);
                    if(distance(damaged_area, destination)<=area_radius){
                        Character *effected_target = characterInCell(damaged_area);
                        if (effected_target != nullptr || attacker->isTeamMember(effected_target)) {
                            effected_target->doDamage(area_damage);
                        }
                    }
                }
            }
        }
    }


    void Game::attack(const GridPoint &attacker_location, const GridPoint &destination) {
        Character * attacker = characterInCell(attacker_location);
        int size = characters.size();
        if(attacker == nullptr){
            throw CellEmpty();
        }
        Character * target = characterInCell(destination);
        if(!isValidLocation(attacker_location) || !isValidLocation(destination)){
            throw IllegalCell();
        }
        if(!attacker->isInAttackRange(destination)){
            throw OutOfRange();
        }
        if(attacker->isTeamMember(target)){
            if(attacker->getType() == MEDIC) {
                target->doDamage(-attacker->getPower());
                return;
            }
            throw IllegalTarget();
        }
        if(attacker->getAmmoCount() < attacker->getAmmoCost()){
            throw OutOfAmmo();
        }
        attacker->attack(target, destination);
        target->doDamage(attacker->getPower());
        soldierAreaAttack(attacker, destination);
    }

    void Game::reload(const GridPoint &coordinates) {
        if (!isValidLocation(coordinates)) {
            throw IllegalCell();
        }
        Character * character = characterInCell(coordinates);
        if (character == nullptr) {
            throw CellEmpty();
        }
        character->reload();
    }
}
