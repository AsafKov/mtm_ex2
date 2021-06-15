
#include "Game.h"
#include "Character.h"
#include <iostream>
#include <cassert>

#define assertExcept(func, exception) try{func;} catch(exception e){}

using namespace mtm;
using std::cout;
using std::endl;


bool constructor()
{
    cout<<"startttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt"<<endl;
    Game G = Game(1, 1);
    cout<<"past 0.1 test"<<endl;
    assertExcept(Game G2 = Game(-1, 1), IllegalArgument);
    cout<<"past 0.2 test"<<endl;
    assertExcept(Game G2 = Game(0, 1), IllegalArgument);
    cout<<"past 0.3 test"<<endl;
    assertExcept(Game G2 = Game(1, -1), IllegalArgument);
    cout<<"past 0.4 test"<<endl;
    assertExcept(Game G2 = Game(1, 0), IllegalArgument);
    cout<<"past 1 test"<<endl;
    return true;
}

bool createChars()
{
    Game G = Game(10, 10);

    auto C1 = G.makeCharacter(mtm::SOLDIER, mtm::CROSSFITTERS, 4, 2, 12, 2);
    auto C2 = G.makeCharacter(mtm::MEDIC, mtm::CROSSFITTERS, 4, 2, 12, 2);
    auto C3 = G.makeCharacter(mtm::SNIPER, mtm::CROSSFITTERS, 4, 2, 12, 2);
    auto C4 = G.makeCharacter(mtm::SNIPER, mtm::POWERLIFTERS, 4, 2, 12, 2);
    cout<<"past 2 test"<<endl;
    assert(dynamic_cast<const Soldier*>(C1.get()) != nullptr);
    assert(dynamic_cast<const Medic*>(C2.get()) != nullptr);
    assert(dynamic_cast<const Sniper*>(C3.get()) != nullptr);
    cout<<"past 3 test"<<endl;
    assert(C1->getTeam() == CROSSFITTERS);
    assert(C2->getTeam() == CROSSFITTERS);
    assert(C3->getTeam() == CROSSFITTERS);
    assert(C4->getTeam() == POWERLIFTERS);

    cout<<"past 4 test"<<endl;
    assertExcept(G.makeCharacter(mtm::SOLDIER, mtm::CROSSFITTERS, 0, 1, 1, 1), IllegalArgument);
    assertExcept(G.makeCharacter(mtm::SOLDIER, mtm::CROSSFITTERS, 1, -1, 1, 1), IllegalArgument);
    assertExcept(G.makeCharacter(mtm::SOLDIER, mtm::CROSSFITTERS, 1, 1, -1, 1), IllegalArgument);
    assertExcept(G.makeCharacter(mtm::SOLDIER, mtm::CROSSFITTERS, 1, 1, 1, -1), IllegalArgument);
    cout<<"past 5 test"<<endl;
    G.makeCharacter(mtm::SOLDIER, mtm::CROSSFITTERS, 1, 0, 0, 0);

    return true;
}

bool addChars()
{
    cout<<"past 6 test"<<endl;
    Game G = Game(10, 10);
    cout<<"past 7 test"<<endl;
    auto C1 = G.makeCharacter(mtm::SOLDIER, mtm::CROSSFITTERS, 4, 2, 12, 2);
    auto C2 = G.makeCharacter(mtm::MEDIC, mtm::CROSSFITTERS, 4, 2, 12, 2);
    auto C3 = G.makeCharacter(mtm::SNIPER, mtm::CROSSFITTERS, 4, 2, 12, 2);
    cout<<"past 8 test"<<endl;
    G.addCharacter(mtm::GridPoint(0, 0), C1);
    G.addCharacter(mtm::GridPoint(0, 1), C2);
    G.addCharacter(mtm::GridPoint(0, 2), C3);
    cout<<"past 9 test"<<endl;
    auto C4 = G.makeCharacter(mtm::SOLDIER, mtm::POWERLIFTERS, 4, 2, 12, 2);
    auto C5 = G.makeCharacter(mtm::MEDIC, mtm::POWERLIFTERS, 4, 2, 12, 2);
    auto C6 = G.makeCharacter(mtm::SNIPER, mtm::POWERLIFTERS, 4, 2, 12, 2);
    cout<<"past 10 test"<<endl;
    G.addCharacter(mtm::GridPoint(1, 0), C4);
    G.addCharacter(mtm::GridPoint(1, 1), C5);
    G.addCharacter(mtm::GridPoint(1, 2), C6);
    cout<<"past 11 test"<<endl;
    assertExcept(G.addCharacter(mtm::GridPoint(1, 0), C1), CellOccupied);
    cout<<"past 11.1 test"<<endl;
    assertExcept(G.addCharacter(mtm::GridPoint(-1, 0), C1), IllegalCell);
    cout<<"past 11.2 test"<<endl;
    assertExcept(G.addCharacter(mtm::GridPoint(0, -1), C1), IllegalCell);
    cout<<"past 11.3 test"<<endl;
    assertExcept(G.addCharacter(mtm::GridPoint(0, 10), C1), IllegalCell);
    cout<<"past 11.4 test"<<endl;
    assertExcept(G.addCharacter(mtm::GridPoint(10, 0), C1), IllegalCell);
    cout<<"past 12 test"<<endl;
    return true;
}

bool copyConst()
{
    Game G = Game(10, 10);
    cout<<"past 13 test"<<endl;
    auto C1 = G.makeCharacter(mtm::SOLDIER, mtm::CROSSFITTERS, 4, 2, 12, 2);
    auto C2 = G.makeCharacter(mtm::MEDIC, mtm::CROSSFITTERS, 4, 2, 12, 2);
    auto C3 = G.makeCharacter(mtm::SNIPER, mtm::CROSSFITTERS, 4, 2, 12, 2);
    cout<<"past 14 test"<<endl;
    G.addCharacter(mtm::GridPoint(0, 0), C1);
    G.addCharacter(mtm::GridPoint(0, 1), C2);
    G.addCharacter(mtm::GridPoint(0, 2), C3);
    cout<<"past 15 test"<<endl;
    auto G2(G);
    cout<<"past 15.1 test"<<endl;
//    G2.~Game();
    cout<<"past 15.2 test"<<endl;
    G.reload(GridPoint(0, 0));
    cout<<"past 15.3 test"<<endl;
    auto G3(G);
    cout<<"past 15.4 test"<<endl;
    //  G.~Game();

    G3.reload(GridPoint(0, 0));
    cout<<"reached after line 105 "<<endl;
    return true;

}

bool assignOper()
{
    cout<<"past 16.5 test"<<endl;
    Game G = Game(10, 10);
    cout<<"past 17 test"<<endl;
    auto C1 = G.makeCharacter(mtm::SOLDIER, mtm::CROSSFITTERS, 4, 2, 12, 2);
    cout<<"past 17.1 test"<<endl;
    auto C2 = G.makeCharacter(mtm::MEDIC, mtm::CROSSFITTERS, 4, 2, 12, 2);
    cout<<"past 17.2 test"<<endl;
    auto C3 = G.makeCharacter(mtm::SNIPER, mtm::CROSSFITTERS, 4, 2, 12, 2);
    cout<<"past 18 test"<<endl;
    G.addCharacter(mtm::GridPoint(0, 0), C1);
    G.addCharacter(mtm::GridPoint(0, 1), C2);
    G.addCharacter(mtm::GridPoint(0, 2), C3);
    cout<<"past 19 test"<<endl;
    auto G2 = G;

    // G2.~Game();

    G.reload(GridPoint(0, 0));
    cout<<"past 20 test"<<endl;
    return true;
}

void example1() {
    std::cout << "------example 1------" << std::endl;
    Game g1(8, 8);
    cout<<"past 21 test"<<endl;
    g1.addCharacter(GridPoint(1, 1), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 10, 2, 4, 5));
    cout<<"past 21.1 test"<<endl;
    g1.addCharacter(GridPoint(1, 4), Game::makeCharacter(CharacterType::SNIPER, Team::POWERLIFTERS, 10, 2, 4, 5));
    cout<<"past 21.2 test"<<endl;
    g1.addCharacter(GridPoint(6, 1), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 10, 2, 4, 5));
    cout<<"past 21.3 test"<<endl;
    g1.addCharacter(GridPoint(6, 4), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 10, 2, 4, 5));
    cout<<"past 21.4 test"<<endl;
    std::cout << g1 << std::endl;
    cout<<"past 21.5 test"<<endl;
    g1.move(GridPoint(1, 1), GridPoint(1, 2));
    cout<<"past 21.6 test"<<endl;
    std::cout << g1 << std::endl;
    cout<<"past 21 test"<<endl;

    try {
        g1.attack(GridPoint(1, 4), GridPoint(1, 2)); // can't attak ally
    }
    catch (mtm::IllegalTarget& e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 22 test"<<endl;
    try {
        g1.attack(GridPoint(1, 4), GridPoint(6, 1)); // should not work - not in range
    }
    catch (mtm::OutOfRange& e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 23 test"<<endl;
    std::cout << g1 << std::endl;

    g1.move(GridPoint(1, 4), GridPoint(3, 2));

    std::cout << g1 << std::endl;
    try {
        g1.attack(GridPoint(1, 4), GridPoint(6, 4)); // character moved away
    }
    catch (mtm::CellEmpty& e) {
        std::cout << e.what() << std::endl;
    }

    g1.attack(GridPoint(3, 2), GridPoint(6, 1)); // now it can hit

    std::cout << g1 << std::endl;

    g1.move(GridPoint(6, 1), GridPoint(4, 2));
    std::cout << g1 << std::endl;

    try {
        g1.attack(GridPoint(3, 2), GridPoint(4, 2)); // sniper can't attack close targets
    }
    catch (mtm::OutOfRange& e) {
        std::cout << e.what() << std::endl;
    }

    g1.move(GridPoint(4, 2), GridPoint(6, 2));
    std::cout << g1 << std::endl;

    g1.attack(GridPoint(3, 2), GridPoint(6, 2)); // now it can hit
    std::cout << g1 << std::endl;

    try {
        g1.move(GridPoint(6, 2), GridPoint(6, 1)); // soldier was killed and removed
    }
    catch (mtm::CellEmpty& e) {
        std::cout << e.what() << std::endl;
    }

    g1.move(GridPoint(3, 2), GridPoint(3, 4));

    try {
        g1.attack(GridPoint(3, 4), GridPoint(6, 4)); // sniper out of ammo
    }
    catch (mtm::OutOfAmmo& e) {
        std::cout << e.what() << std::endl;
    }


    try {
        g1.attack(GridPoint(6, 4), GridPoint(6, 4)); // medic can't heal itself
    }
    catch (mtm::IllegalTarget& e) {
        std::cout << e.what() << std::endl;
    }

    mtm::Team winning_team = mtm::Team::CROSSFITTERS;
    assert(g1.isOver(&winning_team) == false);
    std::cout << "isOver: " << g1.isOver(&winning_team) << std::endl;
    std::cout << "is powerlifters the winning team?: " << (winning_team == mtm::Team::POWERLIFTERS) << std::endl;

    g1.reload(GridPoint(3, 4));
    g1.attack(GridPoint(3, 4), GridPoint(6, 4)); // now can shoot

    std::cout << g1 << std::endl;

    try {
        g1.move(GridPoint(6, 4), GridPoint(6, 1)); // medic was killed and removed
        // the kill was possible because of the sniper double power third attack
    }
    catch (mtm::CellEmpty& e) {
        std::cout << e.what() << std::endl;
    }

    assert(g1.isOver(&winning_team) == true);
    assert(winning_team == mtm::Team::POWERLIFTERS);
    std::cout << "isOver: " << g1.isOver(&winning_team) << std::endl;
    std::cout << "is powerlifters the winning team?: " << (winning_team == mtm::Team::POWERLIFTERS) << std::endl;
}

void example2() {
    std::cout << "------example 2------" << std::endl;
    Game g1(5, 10);
    g1.addCharacter(GridPoint(3, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 20, 0, 3, 5));
    g1.addCharacter(GridPoint(2, 6), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(3, 8), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(3, 6), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(4, 6), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 10, 2, 4, 5));
    std::cout << g1 << std::endl;

    try {
        g1.attack(GridPoint(3, 0), GridPoint(3, 6));
    }
    catch (mtm::OutOfRange& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        g1.move(GridPoint(3, 0), GridPoint(3, 4)); // soldier only moves 3 at a time
    }
    catch (mtm::MoveTooFar& e) {
        std::cout << e.what() << std::endl;
    }

    std::cout << g1 << std::endl; // has not changed

    Game g2 = g1; // copy constructor - games should be independent

    g1.move(GridPoint(3, 0), GridPoint(3, 3));

    std::cout << g1 << std::endl; // changed
    std::cout << g2 << std::endl; // has not changed

    try {
        g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // soldier has 0 ammo
    }
    catch (mtm::OutOfAmmo& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        g1.reload(GridPoint(3, 2));
    }
    catch (mtm::CellEmpty& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        g1.reload(GridPoint(3, -3));
    }
    catch (mtm::IllegalCell& e) {
        std::cout << e.what() << std::endl;
    }
    try {
        g1.reload(GridPoint(3, 13));
    }
    catch (mtm::IllegalCell& e) {
        std::cout << e.what() << std::endl;
    }

    g1.reload(GridPoint(3, 3)); // now soldier has ammo

    g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // damages 2 medics and 1 sniper in range
    std::cout << g1 << std::endl; // everyone still alive

    g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // one medic dies (took 5+5 damage instead of 3+3 like the others)
    std::cout << g1 << std::endl;

    g1.attack(GridPoint(3, 3), GridPoint(3, 6));
    std::cout << g1 << std::endl;

    g1.attack(GridPoint(4, 6), GridPoint(2, 6)); // medic heals sniper
    try {
        g1.attack(GridPoint(4, 6), GridPoint(4, 6)); // medic can't heal self
    }
    catch (mtm::IllegalTarget& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // soldier out of ammo
    }
    catch (mtm::OutOfAmmo& e) {
        std::cout << e.what() << std::endl;
    }

    g1.reload(GridPoint(3, 3)); // now soldier has ammo
    g1.reload(GridPoint(3, 3)); // can reload twice - no problem (more ammo)

    g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // medic dead, sniper not dead
    std::cout << g1 << std::endl;
}

void example3Hemi() {
    std::cout << "------example 3------" << std::endl;
    Game g1(5, 5);
    g1.addCharacter(GridPoint(0, 1), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 20, 20, 3, 5));
    g1.addCharacter(GridPoint(0, 2), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 20, 20, 3, 5));
    g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::SNIPER, Team::POWERLIFTERS, 10, 20, 4, 5));
    g1.addCharacter(GridPoint(0, 3), Game::makeCharacter(CharacterType::SNIPER, Team::POWERLIFTERS, 10, 20, 4, 5));
    g1.addCharacter(GridPoint(0, 4), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 20, 30, 5, 8));

    g1.addCharacter(GridPoint(4, 2), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 20, 20, 3, 5));
    g1.addCharacter(GridPoint(4, 3), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 20, 20, 3, 5));
    g1.addCharacter(GridPoint(4, 4), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 10, 20, 4, 5));
    g1.addCharacter(GridPoint(4, 1), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 10, 20, 4, 5));
    g1.addCharacter(GridPoint(4, 0), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 20, 30, 5, 8));

    std::cout << g1 << std::endl;

    try {
        g1.move(GridPoint(0, 1), GridPoint(3, 6));
    }
    catch (mtm::IllegalCell& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        g1.attack(GridPoint(0, 1), GridPoint(4, 1)); // soldier only moves 3 at a time
    }
    catch (mtm::OutOfRange& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        g1.attack(GridPoint(0, 0), GridPoint(0, 2)); // cell occupied
    }
    catch (mtm::IllegalTarget& e) {
        std::cout << e.what() << std::endl;
    }

    g1.move(GridPoint(0, 1), GridPoint(2, 1));
    g1.move(GridPoint(4, 3), GridPoint(3, 3));
    std::cout << g1 << std::endl;
    try {
        g1.attack(GridPoint(0, 3), GridPoint(1, 3));
    }
    catch (mtm::OutOfRange& e) {
        std::cout << e.what() << std::endl;
    }
    g1.attack(GridPoint(0, 3), GridPoint(3, 3));
    for (int i = 0; i < 20; i++)
    {
        g1.attack(GridPoint(3, 3), GridPoint(3, 4)); //Wasting ammo for no reason on empty cell
    }
    try {
        g1.attack(GridPoint(3, 3), GridPoint(3, 4));
    }
    catch (mtm::OutOfAmmo& e) {
        std::cout << e.what() << std::endl;
    }
    g1.reload(GridPoint(3, 3));
    g1.attack(GridPoint(0, 4), GridPoint(3, 3));
    g1.attack(GridPoint(0, 4), GridPoint(3, 3));

    g1.move(GridPoint(4, 0), GridPoint(3, 2));
    g1.attack(GridPoint(0, 2), GridPoint(3, 2));
    g1.attack(GridPoint(3, 2), GridPoint(4, 1));
    g1.attack(GridPoint(0, 4), GridPoint(4, 4));
    g1.attack(GridPoint(0, 4), GridPoint(4, 4));
    g1.move(GridPoint(4, 1), GridPoint(4, 0));
    g1.attack(GridPoint(0, 0), GridPoint(4, 0));
    g1.attack(GridPoint(4, 0), GridPoint(0, 0));
    g1.attack(GridPoint(0, 0), GridPoint(4, 0));
    g1.move(GridPoint(2, 1), GridPoint(2, 0));
    g1.attack(GridPoint(2, 0), GridPoint(4, 0));
    g1.attack(GridPoint(2, 0), GridPoint(4, 0));
    try {
        g1.reload(GridPoint(4, 0));
    }
    catch (mtm::CellEmpty& e) {
        std::cout << e.what() << std::endl;
    }

    g1.move(GridPoint(0, 4), GridPoint(2, 2));
    for (int i = 0; i < 2; i++)
    {
        g1.attack(GridPoint(2, 2), GridPoint(3, 2));
    }
    std::cout << g1 << std::endl;
    g1.move(GridPoint(4, 2), GridPoint(4, 0));
    std::cout << g1 << std::endl;
    g1.attack(GridPoint(0, 0), GridPoint(4, 0));
    g1.attack(GridPoint(4, 0), GridPoint(2, 0));
    g1.attack(GridPoint(2, 2), GridPoint(4, 0));
    Team team1 = CROSSFITTERS;
    Team* team = &team1;
    bool t = g1.isOver(team);
    std::cout << g1 << std::endl;
    std::cout << "winning team is: " << team1 << std::endl;

}

void example4Hemi()
{
    Game g1(4, 4);
    g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 5, 3, 4, 10));
    g1.addCharacter(GridPoint(0, 3), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 5, 3, 4, 10));
    g1.addCharacter(GridPoint(0, 1), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 10, 5, 5, 8));
    g1.addCharacter(GridPoint(0, 2), Game::makeCharacter(CharacterType::SNIPER, Team::POWERLIFTERS, 10, 4, 5, 5));

    g1.addCharacter(GridPoint(3, 3), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 5, 3, 4, 10));
    g1.addCharacter(GridPoint(3, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 5, 3, 4, 10));
    g1.addCharacter(GridPoint(3, 2), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 10, 5, 5, 8));
    g1.addCharacter(GridPoint(3, 1), Game::makeCharacter(CharacterType::SNIPER, Team::POWERLIFTERS, 10, 4, 5, 5));
    Team* team = NULL;
    bool t = g1.isOver(team);
    assert(t == true);
    std::cout << g1;

}

void example5Hemi()
{
    Game g1(4, 4);
    g1.addCharacter(GridPoint(0, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 7, 3, 4, 10));
    g1.addCharacter(GridPoint(0, 3), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 7, 3, 4, 10));
    g1.addCharacter(GridPoint(0, 1), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 10, 5, 5, 8));
    g1.addCharacter(GridPoint(0, 2), Game::makeCharacter(CharacterType::SNIPER, Team::POWERLIFTERS, 10, 4, 4, 5));

    g1.addCharacter(GridPoint(3, 3), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 7, 3, 4, 10));
    g1.addCharacter(GridPoint(3, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 7, 3, 4, 10));
    g1.addCharacter(GridPoint(3, 2), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 10, 5, 5, 8));
    g1.addCharacter(GridPoint(3, 1), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 10, 4, 4, 5));
    Team* team = NULL;
    bool t = g1.isOver(team);
    assert(t == false);
    try {
        g1.move(GridPoint(5, 3), GridPoint(3, 4));
    }
    catch (mtm::IllegalCell& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        g1.move(GridPoint(3, 3), GridPoint(3, 4));
    }
    catch (mtm::IllegalCell& e) {
        std::cout << e.what() << std::endl;
    }
    g1.move(GridPoint(3, 3), GridPoint(1, 2));
    g1.move(GridPoint(1, 2), GridPoint(1, 1));
    g1.attack(GridPoint(0, 2), GridPoint(1, 1));
    g1.reload(GridPoint(0, 2));
    try {
        g1.attack(GridPoint(1, 1), GridPoint(0, 2));
    }
    catch (mtm::IllegalTarget& e) {
        std::cout << e.what() << std::endl;
    }
    g1.attack(GridPoint(1, 1), GridPoint(0, 1));
    g1.attack(GridPoint(0, 2), GridPoint(1, 1));
    try {
        g1.reload(GridPoint(1, 1));
    }
    catch (mtm::CellEmpty& e)
    {
        std::cout << e.what() << std::endl;
    }
    g1.move(GridPoint(0, 2), GridPoint(1, 1));
    g1.attack(GridPoint(1, 1), GridPoint(3, 2));
    g1.move(GridPoint(1, 1), GridPoint(0, 1));
    g1.attack(GridPoint(3, 1), GridPoint(0, 1));
    std::cout << g1;
    for (int i = 0; i < 3; i++)
    {
        g1.attack(GridPoint(3, 0), GridPoint(3, 0)); //s wasting ammo for no reason
    }
    std::cout << g1;
    try {
        g1.attack(GridPoint(3, 0), GridPoint(0, 0));
    }
    catch (mtm::OutOfAmmo& e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << g1;
    g1.attack(GridPoint(0, 0), GridPoint(3, 0));
    std::cout << g1;
    g1.attack(GridPoint(3, 1), GridPoint(0, 0));
    std::cout << g1;
    try
    {
        g1.attack(GridPoint(3, 1), GridPoint(0, 3));
    }
    catch (mtm::OutOfRange& e)
    {
        std::cout << e.what() << std::endl;
    }
    std::cout << g1;
    g1.move(GridPoint(0, 3), GridPoint(0, 1));
    std::cout << g1;
    g1.attack(GridPoint(3, 1), GridPoint(0, 1));
    std::cout << g1;
    Team team2 = POWERLIFTERS;
    Team* team3 = &team2;
    bool t1 = g1.isOver(team3);
    std::cout << "Winning team is: " << team2;
    //Should be 1 -croosfiters
}

int main()
{
    assert(constructor());
    assert(createChars());
    assert(addChars());
    assert(copyConst());
    assert(assignOper());

    example1();
    example2();
    example3Hemi();
    example4Hemi();
    example5Hemi();
    return 0;
}






/*
#include <iostream>

#include <cassert>

#include "Exceptions.h"
#include "Game.h"

using namespace mtm;

void example1();
void example2();

int main() {
    example1();
    example2();
}

void example1() {
    std::cout << "------example 1------" << std::endl;
    Game g1(8,8);
    g1.addCharacter(GridPoint(1,1), Game::makeCharacter(CharacterType::MEDIC, Team::POWERLIFTERS, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(1,4), Game::makeCharacter(CharacterType::SNIPER, Team::POWERLIFTERS, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(6,1), Game::makeCharacter(CharacterType::SOLDIER, Team::CROSSFITTERS, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(6,4), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 10, 2, 4, 5));
    std::cout << g1 << std::endl;
    g1.move(GridPoint(1,1), GridPoint(1,2));
    std::cout << g1 << std::endl;


    try {
        g1.attack(GridPoint(1,4), GridPoint(1,2)); // can't attak ally
    } catch (mtm::IllegalTarget& e) {
        std::cout << e.what() << std::endl;
    }
     cout<<"past 1 test"<<endl;
    try {
        g1.attack(GridPoint(1,4), GridPoint(6,1)); // should not work - not in range
    } catch (mtm::OutOfRange& e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 2 test"<<endl;
    g1.move(GridPoint(1,4), GridPoint(3,2));
    std::cout << g1 << std::endl;
    try {
        g1.attack(GridPoint(1,4), GridPoint(6,4)); // character moved away
    } catch (mtm::CellEmpty& e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 3 test"<<endl;
    g1.attack(GridPoint(3,2), GridPoint(6,1)); // now it can hit

    g1.move(GridPoint(6,1), GridPoint(4,2));
    std::cout << g1 << std::endl;
    cout<<"past 4 test"<<endl;
    try {
        g1.attack(GridPoint(3,2), GridPoint(4,2)); // sniper can't attack close targets
    } catch (mtm::OutOfRange& e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 5 test"<<endl;
    g1.move(GridPoint(4,2), GridPoint(6,2));
    std::cout << g1 << std::endl;
    cout<<"past 6 test"<<endl;
    g1.attack(GridPoint(3,2), GridPoint(6,2)); // now it can hit
    std::cout << g1 << std::endl;
    cout<<"past 7 test"<<endl;
    try {
        g1.move(GridPoint(6,2), GridPoint(6,1)); // soldier was killed and removed
    } catch (mtm::CellEmpty& e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 8 test"<<endl;
    g1.move(GridPoint(3,2), GridPoint(3,4));
    cout<<"past 9 test"<<endl;
    try {
        g1.attack(GridPoint(3,4), GridPoint(6,4)); // sniper out of ammo
    } catch (mtm::OutOfAmmo& e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 10 test"<<endl;

    try {
        g1.attack(GridPoint(6,4), GridPoint(6,4)); // medic can't heal itself
    } catch (mtm::IllegalTarget& e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 11 test"<<endl;
    mtm::Team winning_team = mtm::Team::CROSSFITTERS;

    assert(g1.isOver(&winning_team) == false);
    cout<<"past all tests until this point"<<endl;
    std::cout << "isOver: " <<  g1.isOver(&winning_team) << std::endl;
    std::cout << "is powerlifters the winning team?: " <<  (winning_team == mtm::Team::POWERLIFTERS) << std::endl;
    cout<<"past 12 test"<<endl;
    g1.reload(GridPoint(3,4));
    g1.attack(GridPoint(3,4), GridPoint(6,4)); // now can shoot
    cout<<"past 13 test"<<endl;
    std::cout << g1 << std::endl;

    try {
        g1.move(GridPoint(6,4), GridPoint(6,1)); // medic was killed and removed
        // the kill was possible because of the sniper double power third attack
    } catch (mtm::CellEmpty& e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 14 test"<<endl;
    assert(g1.isOver(&winning_team) == true);
    assert(winning_team == mtm::Team::POWERLIFTERS);
    std::cout << "isOver: " <<  g1.isOver(&winning_team) << std::endl;
    std::cout << "is powerlifters the winning team?: " <<  (winning_team == mtm::Team::POWERLIFTERS) << std::endl;
    cout<<"past 14.5 test"<<endl;
}

void example2() {
    std::cout << "------example 2------" << std::endl;
    Game g1(5, 10);
    g1.addCharacter(GridPoint(3, 0), Game::makeCharacter(CharacterType::SOLDIER, Team::POWERLIFTERS, 20, 0, 3, 5));
    g1.addCharacter(GridPoint(2, 6), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(3, 8), Game::makeCharacter(CharacterType::SNIPER, Team::CROSSFITTERS, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(3, 6), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 10, 2, 4, 5));
    g1.addCharacter(GridPoint(4, 6), Game::makeCharacter(CharacterType::MEDIC, Team::CROSSFITTERS, 10, 2, 4, 5));
    std::cout << g1 << std::endl;
    try {
        g1.attack(GridPoint(3, 0), GridPoint(3, 6));
    } catch (mtm::OutOfRange &e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 16 test"<<endl;
    try {
        g1.move(GridPoint(3, 0), GridPoint(3, 4)); // soldier only moves 3 at a time
    } catch (mtm::MoveTooFar &e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 17 test"<<endl;
    std::cout << g1 << std::endl; // has not changed
    cout<<"past 18 test"<<endl;
    Game g2 = g1; // copy constructor - games should be independent
    cout<<"past 19 test"<<endl;
    g1.move(GridPoint(3, 0), GridPoint(3, 3));
    cout<<"past 20 test"<<endl;
    std::cout << g1 << std::endl; // changed
    cout<<"past 21 test"<<endl;
    std::cout << g2 << std::endl; // has not changed

    try {
        g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // soldier has 0 ammo
    } catch (mtm::OutOfAmmo &e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 22 test"<<endl;
    try {
        g1.reload(GridPoint(3, 2));
    } catch (mtm::CellEmpty &e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 23 test"<<endl;
    try {
        g1.reload(GridPoint(3, -3));
    } catch (mtm::IllegalCell &e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 23.5 test"<<endl;
    try {
        g1.reload(GridPoint(3, 13));
    } catch (mtm::IllegalCell &e) {
        std::cout << e.what() << std::endl;
    }
    cout<<"past 24 test"<<endl;
    g1.reload(GridPoint(3, 3)); // now soldier has ammo
    cout<<"past 24.5 test"<<endl;
    g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // damages 2 medics and 1 sniper in range
    std::cout << g1 << std::endl; // everyone still alive
    cout<<"past 24.6 test"<<endl;
    g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // one medic dies (took 5+5 damage instead of 3+3 like the others)
    std::cout << g1 << std::endl;
    cout<<"past 24.7 test"<<endl;
    g1.attack(GridPoint(3, 3), GridPoint(3, 6));
    std::cout << g1 << std::endl;
    cout<<"past 25 test"<<endl;
    g1.attack(GridPoint(4, 6), GridPoint(2, 6)); // medic heals sniper
    try {
        g1.attack(GridPoint(4, 6), GridPoint(4, 6)); // medic can't heal self
    } catch (mtm::IllegalTarget &e) {
        std::cout << e.what() << std::endl;
    }

    try {
        g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // soldier out of ammo
    } catch (mtm::OutOfAmmo &e) {
        std::cout << e.what() << std::endl;
    }

    g1.reload(GridPoint(3, 3)); // now soldier has ammo
    g1.reload(GridPoint(3, 3)); // can reload twice - no problem (more ammo)

    g1.attack(GridPoint(3, 3), GridPoint(3, 6)); // medic dead, sniper not dead
    std::cout << g1 << std::endl;
}
*/