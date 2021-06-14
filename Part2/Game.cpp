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
        return GridPoint::GridPoint(x,y);
    }

    units_t Game::distance(const GridPoint& point1, const GridPoint& point2) const {
        return GridPoint::distance(point1, point2);
    }

    void Game::addCharacter(const Game::GridPoint &coordinates,  const SharedPtr& character) {
        if (!isValidLocation(coordinates)) {
            //TODO: throw InvalidCellException
        }

        if(characterInCell(coordinates) != nullptr){
            //TODO: throw exception CellOccupied
        }
        characters.push_back(character);
    }

    bool Game::isValidLocation(const Game::GridPoint point) const {
        return (point.row >= 0 && point.row < height) && (point.col >= 0 && point.col < width);
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

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
        if(!isValidLocation(src_coordinates) || !isValidLocation(dst_coordinates)){
            //TODO: throw invalid coordinates
        }
        SharedPtr character = characterInCell(src_coordinates);
        if(character == nullptr){
            //TODO: throw empty cell exception
        }
        //TODO: can move 0 steps?
        if(characterInCell(dst_coordinates) != nullptr){
            //TODO: cell occupied exception
        }
        if(!character->isDestinationInRange(dst_coordinates)){
            //TODO: out of range exception
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

    void Game::soldierAreaAttack(Character* attacker, const GridPoint &dst_coordinates) {
        if(attacker->getType() == SOLDIER){
            units_t attack_radius = ceil((double)attacker->getAttackRange()/3);
            units_t attack_radius_damage = ceil((double)attacker->getPower()/2);
            for(units_t i=0 ; i < height ; i++){
                for(units_t j=0 ; j < width ; j++){
                    GridPoint damaged_area = getGrid(i,j);
                    if(distance(damaged_area, dst_coordinates)<=attack_radius){
                        SharedPtr effected_target = characterInCell(damaged_area);
                        if (effected_target != nullptr && attacker->isTeamMember(effected_target.get())) {
                            effected_target->doDamage(attack_radius_damage);
                        }
                    }
                }
            }
        }
    }

    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
        if(!isValidLocation(src_coordinates) || !isValidLocation(dst_coordinates)){
            //TODO: throw invalid coordinates
        }
        SharedPtr attacker = characterInCell(src_coordinates);
        SharedPtr target = characterInCell(dst_coordinates);
        if(!attacker->isInAttackRange(dst_coordinates)){
            //TODO: throw attack out of range exception
        }
        if(attacker->getAmmoCount() < attacker->getAmmoCost()){
            // TODO: throw OutOfAmmo exception
        }
        if(attacker->isTeamMember(target.get()) && attacker->getType()!= MEDIC){
            // TODO: throw Illegal attack exception
        }
        attacker->attack(target.get(), dst_coordinates);
        target->doDamage(attacker->getPower());
        soldierAreaAttack(attacker.get(), dst_coordinates);
    }




}
