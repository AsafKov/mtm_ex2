#include "Game.h"

namespace mtm{
    Game::Game(int height, int width) : width(width), height(height) {
        characters = vector<SharedPtr>();
    }

    Game::Game(const Game &game) {

    }

    Game &Game::operator=(const Game &game) {

    }

    Game::~Game() {

    }

    GridPoint Game::getGrid(int x, int y) const {
        return GridPoint(x,y);
    }

    units_t Game::distance(const GridPoint& point1, const GridPoint& point2) const {
        return GridPoint::distance(point1, point2);
    }

    bool Game::isValidLocation(const GridPoint location) const {
        return (location.row >= 0 && location.row < height) && (location.col >= 0 && location.col < width);
    }

    void Game::addCharacter(const GridPoint &coordinates,  const SharedPtr& character) {
        if (!isValidLocation(coordinates)) {
            //TODO: throw InvalidCellException
        }

        if(characterInCell(coordinates) != nullptr){
            //TODO: throw exception CellOccupied
        }
        characters.push_back(character);
    }

    Game::SharedPtr Game::makeCharacter(CharacterType type, Team team, Game::unit_t health, Game::unit_t ammo,
                                        Game::unit_t range, Game::unit_t power) {
        if(health == 0 || range == 0){
            //TODO: throw illegal argument exception
        }
        if(power <0 || ammo < 0){
            //TODO: throw illegal argument exception
        }
        switch (type) {
            case SOLDIER: {
                SharedPtr character(new Soldier(team, health, ammo, range, power, SOLDIER));
                return character;
            }
            case MEDIC:{
                SharedPtr character(new Medic(team, health, ammo, range, power, MEDIC));
                return character;
            }
            case SNIPER:{
                SharedPtr character(new Sniper(team, health, ammo, range, power, SNIPER));
                return character;
            }
        }
    }

    Game::SharedPtr &Game::characterInCell(const GridPoint &location) {
        auto it = characters.begin();
        while (it != characters.end()) {
            if ((*it)->getLocation() == location) {
                return *it;
            }
            it++;
        }
        //TODO: Is valid return value null?
        return *it;
    }

    void Game::move(const GridPoint &src_location, const GridPoint &dst_location) {
        SharedPtr character = characterInCell(src_location);
        if(!isValidLocation(src_location) || !isValidLocation(dst_location)){
            //TODO: throw invalid coordinates
        }
        if(character == nullptr){
            //TODO: throw empty cell exception
        }
        //TODO: can move 0 steps?
        if(characterInCell(dst_location) != nullptr){
            //TODO: cell occupied exception
        }
        if(!character->isDestinationInRange(dst_location)){
            //TODO: out of range exception
        }
        character->setLocation(dst_location);
    }

    void Game::soldierAreaAttack(Character* attacker, const GridPoint &destination) {
        if(attacker->getType() == SOLDIER){
            units_t area_radius = ceil((double)attacker->getAttackRange()/3);
            units_t area_damage = ceil((double)attacker->getPower()/2);
            for(units_t i=destination.row-2 ; i <= destination.row+2 ; i++){
                for(units_t j=destination.col-2 ; j <= destination.col+2 ; j++){
                    GridPoint damaged_area = getGrid(i,j);
                    if(distance(damaged_area, destination)<=area_radius){
                        SharedPtr effected_target = characterInCell(damaged_area);
                        if (effected_target != nullptr || attacker->isTeamMember(effected_target.get())) {
                            effected_target->doDamage(area_damage);
                        }
                    }
                }
            }
        }
    }

    void Game::attack(const GridPoint &attacker_location, const GridPoint &destination) {
        SharedPtr attacker = characterInCell(attacker_location);
        SharedPtr target = characterInCell(destination);
        if(!isValidLocation(attacker_location) || !isValidLocation(destination)){
            //TODO: throw invalid coordinates
        }
        if(!attacker->isInAttackRange(destination)){
            //TODO: throw attack out of range exception
        }
        if(attacker->isTeamMember(target.get())){
            if(attacker->getType() == MEDIC) {
                target->doDamage(-attacker->getPower());
                return;
            }
            // TODO: throw Illegal attack exception
        }
        if(attacker->getAmmoCount() < attacker->getAmmoCost()){
            // TODO: throw OutOfAmmo exception
        }
        attacker->attack(target.get(), destination);
        target->doDamage(attacker->getPower());
        soldierAreaAttack(attacker.get(), destination);
    }

}



