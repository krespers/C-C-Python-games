#pragma once
#include <iostream>
#include <vector>
#include "pokemon.hpp"
#include "player.hpp"
#include "held_item.hpp"

using namespace std;

class Game {
public:
    Game();
    void run();
    vector<Player> players;
    vector<Pokemon> pokemonPool;
    vector<Move> movePool;
    vector<HeldItem> heldItemPool;

    int turn;

    void pokemonSelect();
    void showAvailablePokemons(vector<bool>&);
    void heldItemSelect();
    void showAvailableHeldItems(vector<bool>&);
    void assignHeldItems(Player&, vector<HeldItem>&);
    void parsePokemonPool();
    void parseMovePool();
    void parseHeldItemPool();
    void matchMove2Pokemon();
    void battle();
    Move& attackSelect(Pokemon&);
    void attackExecute(Pokemon&, Pokemon&, Move&);


    // parsing checking
    void checkPools();

    // for pokemonSelect() => clear screen, more convinient for selection
    void selectPokemons(Player&, int, vector<bool>&);

    // seleciton checking
    void pokemonSelectChecker();

    // Item selection () => clear screen, more convinient for selection
    void selectHeldItems(vector<HeldItem>&, int, int, vector<bool>&);


};