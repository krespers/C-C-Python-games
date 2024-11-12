#include <iostream>
#include "player.hpp"

using namespace std;

const vector<Pokemon>& Player::getPokemons() {
    // Implement Here!
    return pokemons;

}

void Player::setPokemons(vector<Pokemon>& pokemons) {
    // Implement Here!
    this->pokemons = pokemons;
}

int Player::switchSelect() {
    // Implement Here!

    int choice;
    do {
        cout << "Player " << id << ", choose a Pokemon : " << endl;
        for (int i = 0; i < pokemons.size(); i++) {
            cout << i << ". " << pokemons[i].getName() << " (" << pokemons[i].getHp() << " HP)" << endl;
        }
        cin >> choice;
    if (choice < 0 || choice >= pokemons.size()) {
        cout << "Invalid choice" << endl;
    }
    else if (choice == currentPokemonIndex) {
        cout << "This Pokemon is already in battle." << endl;
    }

    else if (pokemons[choice].getHp() == 0) {
        cout << "This Pokemon has fainted. Choose another." << endl;
    }
    } while (choice < 0 || choice >= pokemons.size() || choice == currentPokemonIndex || pokemons[choice].getHp() == 0);
    
    return choice;
    // This function is used to switch the current pokemon in battle
    // It displays the player's pokemon and asks the player to choose a pokemon
    // If the player chooses an invalid pokemon, it will ask the player to choose again
    // If the player chooses a fainted pokemon, it will ask the player to choose again
    // If the player chooses the current pokemon, it will ask the player to choose again
    // If the player chooses a valid pokemon, it will return the index of the chosen pokemon

}

void Player::switchExecute(int choice) {
    // Implement Here!
    currentPokemonIndex = choice;
    cout << "Player " << id << " switched to " << pokemons[currentPokemonIndex].getName() << endl;


    // Update the `currentPokemonIndex` to the chosen pokemon index
}

void Player::switchPokemon() {
    int choice = switchSelect();
    switchExecute(choice);

}

Action Player::actionSelect() {
    // Implement Here!
    
    int choice;
    do {
        cout << "Player " << id << ", choose an action: " << endl;
        cout << "0. Attack" << endl;
        cout << "1. Switch Pokemon" << endl;
        cout << "2. Stop Game" << endl;
        cin >> choice;
    } while (choice < 0 || choice > 2);
    if (choice == 0) {
        return Action::attack;
    }
    else if (choice == 1) {
        return Action::switchPokemon;
    }
    else if (choice == 2) {
        return Action::stopGame;
    }
    
    
    // This function is used to ask the player to choose an action
    // If the player has only one pokemon, the player must attack
    // If the player chooses to attack, return Action::attack
    // If the player chooses to switch pokemon, return Action::switchPokemon
    // If the player chooses to stop game, return Action::stopGame
}

Pokemon& Player::getCurrentPokemon() {
    // Implement Here!
    return pokemons[currentPokemonIndex];
}

int Player::getNumPokemon() const {
    // Implement Here!
    return numPokemon;
}

void Player::reducePokemon() {
    // Implement Here!
    numPokemon--;
}

void Player::addPokemon(Pokemon& pokemon) {
    // Implement Here!
    pokemons.push_back(pokemon);
    numPokemon++;
}

void Player::setHeldItem(int pokemonIdx, HeldItem item) {
    // Implement Here!
    pokemons[pokemonIdx].setHeldItem(item);
}

Player::Player(int id) {
    // Implement Here!

    currentPokemonIndex = -1;
    numPokemon = 0;
    this->id = id;
}

Player::Player() {
    // Implement Here!
    currentPokemonIndex = -1;
    numPokemon = 0;
    id = 0;
}

int Player::getId() const {
    // Implement Here!
    return id;
}