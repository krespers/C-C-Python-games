
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <functional>
#include "game.hpp"
#include "spreadCs.hpp"

using namespace std;

Game::Game() {
    // Implement Here!
    players.push_back(Player(1));
    players.push_back(Player(2));
    turn = 0;

}

void Game::run() {
    system("clear");

    // Parse the input files
    parsePokemonPool();
    parseMovePool();
    parseHeldItemPool();
    matchMove2Pokemon();


    //// 파싱이 잘 되었는지 확인용도!! ////
    //checkPools();
    ////////


    // Select Pokemons and held items (Draft Phase)
    pokemonSelect();

    //// 선택이 잘 되었는지 확인용도!! ////
    //pokemonSelectChecker();


    heldItemSelect();

    pokemonSelectChecker();

    // Start the battle


    battle();
}


void Game::pokemonSelect() {
    // Implement Here!
    vector<bool> selected(pokemonPool.size(), false);
    
    // 1. Player 1 selects one pokemon
    selectPokemons(players[0], 1, selected);
    system("clear");
    // 2. Player 2 selects two pokemons
    selectPokemons(players[1], 2, selected);
    system("clear");
    // 3. Player 1 selects two pokemons
    selectPokemons(players[0], 2, selected);
    system("clear");
    // 4. Player 2 selects one pokemon
    selectPokemons(players[1], 1, selected);
    system("clear");

    // Each player selects 3 pokemons from the pool with following rules:
    // 1. Player 1 selects one pokemon
    // 2. Player 2 selects two pokemons
    // 3. Player 1 selects two pokemons
    // 4. Player 2 selects one pokemon
    // End of selection
    // If invalid choice, ask the player to choose again
}

void Game::selectPokemons(Player& player, int num_selection, vector<bool>& selected) {
    // Implement Here!
    string num_selection_char = "";
    if (num_selection == 1) {
        num_selection_char = "One Pokemon";
    } else if (num_selection == 2) {
        num_selection_char = "Two Pokemons";
    }
    cout << "Player " << player.getId() << ", Select " << num_selection_char << endl;
    showAvailablePokemons(selected); //if player selects pokemons, clear the screens
    for (int i = 0; i < num_selection ; ++i) {
        while (true) {
            int choice;
            cout << "Enter the number of the Pokemon: ";
            cin >> choice;


            if (choice < 0 || choice >= pokemonPool.size()) {
                cout << "Invalid choice, please try again." << endl;
            } else if (selected[choice]) {
                cout << "This Pokemon has already been selected. Choose another." << endl;
            } else {
                player.addPokemon(pokemonPool[choice]);
                selected[choice] = true;
                break;
            }
            
        }
    }
    // This function is used to select pokemons for the player
    // It displays the available pokemons and asks the player to choose a pokemon
    // If the player chooses an invalid pokemon, it will ask the player to choose again
    // If the player chooses a valid pokemon, it will assign the pokemon to the player
    // If the player chooses a pokemon that has already been selected, it will ask the player to choose again
    // If the player selects all pokemons, it will clear the screen
}

void Game::showAvailablePokemons(vector<bool>& selected) {
    // Show available Pokemons
    cout << "Available Pokemons" << endl;
    cout << "==================" << endl;
    for (int i = 0; i < pokemonPool.size(); i++) {
        if (!selected[i]) {
            cout << i << ". " << pokemonPool[i].getName() << endl;
        }
        else {
            cout << i << ". " << pokemonPool[i].getName() << " (Selected)" << endl;
        }
    }
    cout << endl;
}

void Game::assignHeldItems(Player& player, vector<HeldItem>& heldItems) {
    // Implement Here!
    cout << "Player " << player.getId() << ", You have selected the following pokemons:" << endl;
    vector<Pokemon> pokemons = player.getPokemons();

    for (int i = 0; i < pokemons.size(); ++i) {
        cout << "Pokemon " << i << ":" << endl;
        pokemons[i].displayInfo();
        cout << endl;
    }
    
    cout << "Player " << player.getId() << ", You have selected the following helditems:" << endl;
    for (int i = 0; i < heldItems.size(); ++i) {
        cout << "HeldItem " << i << ":" << endl;
        heldItems[i].displayInfo();
        cout << endl;
    }


    for (auto& item : heldItems) {
        while (true) {
            cout << "Assigning the following held item..." << endl;
            item.displayInfo();
            cout << "Enter the number of the Pokemon: (0, 1, or 2) :" << endl;
            
            int choice;
            cin >> choice;

            auto checking_for_pokemons = player.getPokemons();

            if (choice < 0 || choice >= player.getPokemons().size()) {
                cout << "Invalid choice" << endl;
            } else if (checking_for_pokemons[choice].getHeldItem().getName() != "") {
                cout << "The Pokemon already has a held item, please try again."<< endl;
            } else {
            player.setHeldItem(choice, item);
            cout << "Assigned " << item.getName() << " to " << player.getPokemons()[choice].getName() << endl;
            cout << endl;
            break;
            }
        }
    }
    // This function assigns held items to the player's pokemons
    // It displays the player's pokemons and held items
    // It asks the player to choose a pokemon to assign a held item
    // If the player chooses an invalid pokemon, it will ask the player to choose again
    // If the player chooses a valid pokemon, it will assign the held item to the chosen pokemon
    // If the player chooses a pokemon that already has a held item, it will ask the player to choose again
    // If the player assigns all held items, it will clear the screen
    system("clear");
}

void Game::heldItemSelect() {
    // Implement Here!
    vector<bool> Itemselected(heldItemPool.size(), false);
    vector<HeldItem> player1Items;
    vector<HeldItem> player2Items;
    
    // 1. Player 1 selects one held-item
    selectHeldItems(player1Items, 1, 1, Itemselected);
    system("clear");

    selectHeldItems(player2Items, 2, 2, Itemselected);
    system("clear");

    selectHeldItems(player1Items, 2, 1, Itemselected);
    system("clear");

    selectHeldItems(player2Items, 1, 2, Itemselected);
    system("clear");

    // Each player selects 3 held-items from the pool with following rules:
    // 1. Player 1 selects one held-item
    // 2. Player 2 selects two held-items
    // 3. Player 1 selects two held-items
    // 4. Player 2 selects one held-item
    // End of selection

    // If invalid choice, ask the player to choose again

    // Then call assignHeldItems for each player
    assignHeldItems(players[0], player1Items);
    assignHeldItems(players[1], player2Items);
}


// this function : new-made...
// this function : new-made...
void Game::selectHeldItems(vector<HeldItem>& playerItem, int num, int playernum, vector<bool>& selected) {

    string num_selection_char = "";
    if (num == 1) {
        num_selection_char = "One helditem";
    } else if (num == 2) {
        num_selection_char = "Two helditems";
    }

    cout << "Player " << playernum << ", Select " << num_selection_char << endl;
    showAvailableHeldItems(selected);

    for (int i = 0; i < num; ++i) {
        while (true) {
            int choice;
            cout << "Enter the number of the Helditem: ";
            cin >> choice;

            if (choice < 0 || choice >= heldItemPool.size() || selected[choice]) {
                cout << "Invalid choice, please try again." << endl;
            } else {
                selected[choice] = true;
                playerItem.push_back(heldItemPool[choice]);
                break;
            }
        }
    }
}


void Game::showAvailableHeldItems(vector<bool>& selected) {
    // Show available helditems
    cout << "Available helditems" << endl;
    cout << "==================" << endl;
    for (int i = 0; i < heldItemPool.size(); i++) {
        if (!selected[i]) {
            cout << i << ". " << heldItemPool[i].getName() << endl;
        }
        else {
            cout << i << ". " << heldItemPool[i].getName() << " (Selected)" << endl;
        }
    }
    cout << endl;
}

void Game::parsePokemonPool() {
    // Implement Here!
    ifstream file("pokemon.txt"); // Open the file
    string line;
    string name, value;
    Type type;
    int hp, attack, defense, specialAttack, specialDefense, speed;
    vector<string> moveNames;

    while (getline(file, line)) {
        if (line.empty()) {
            Pokemon pokemon;
            pokemon.setName(name);
            pokemon.setType(type);
            pokemon.setMaxHp(hp);
            pokemon.setHp(hp);
            pokemon.setAttack(attack);
            pokemon.setDefense(defense);
            pokemon.setSpecialAttack(specialAttack);
            pokemon.setSpecialDefense(specialDefense);
            pokemon.setSpeed(speed);
            pokemon.setMoves(moveNames);
            pokemonPool.push_back(pokemon);
            name = "";
            type = Type::NORMAL;

            hp = attack = defense = specialAttack = specialDefense = speed = 0;
            moveNames.clear();
        } else {
            stringstream ss(line);
            string key, value;
            getline(ss, key, ':');

            ss >> ws;
            // :(콜론) 뒤에 한 칸 띄우고 데이터가 나오므로 이것을 적어주었다.

            getline(ss, value);
            if (key == "name") name = value;
            else if (key == "type") {
                if (value == "normal") {
                    type = Type::NORMAL;
                } else if (value == "fire") {
                    type = Type::FIRE;
                } else if (value == "water") {
                    type = Type::WATER;
                } else if (value == "grass") {
                    type = Type::GRASS;
                }    
            }
            else if (key == "hp") hp = stoi(value);
            else if (key == "attack") attack = stoi(value);
            else if (key == "defense") defense = stoi(value);
            else if (key == "special attack") specialAttack = stoi(value);
            else if (key == "special defense") specialDefense = stoi(value);
            else if (key == "speed") speed = stoi(value);
            else if (key == "moves") {
                stringstream ss2(value);
                string moveName;
                while (getline(ss2, moveName, ',')) {
                    ss2 >> ws;
                    //

                    moveNames.push_back(moveName);
                }
            }
        }
    }
    if (!name.empty() || hp != 0 || attack != 0 || defense != 0 || specialAttack != 0 || specialDefense != 0 || speed != 0 || !moveNames.empty()) {
        Pokemon pokemon;
        pokemon.setName(name);
        pokemon.setType(type);
        pokemon.setMaxHp(hp);
        pokemon.setHp(hp);
        pokemon.setAttack(attack);
        pokemon.setDefense(defense);
        pokemon.setSpecialAttack(specialAttack);
        pokemon.setSpecialDefense(specialDefense);
        pokemon.setSpeed(speed);
        pokemon.setMoves(moveNames);
        pokemonPool.push_back(pokemon);
    }

    file.close();
    // Read pokemon.txt and parse the information
    // Read pokemon.txt and parse the information
}

void Game::parseMovePool() {
    // implement here!

    ifstream file("moves.txt");
    string line;
    string name, category;
    Type type;
    int power, pp;

    while (getline(file, line)) {
        if (line.empty()) {
            Move move;
            move.setName(name);
            move.setType(type);
            move.setCategory(category);
            move.setPower(power);
            move.setPP(pp);
            movePool.push_back(move);

            name = "";
            type = Type::NORMAL;
            category = "";
            power = pp = 0;
        } else {
            stringstream ss(line);
            string key, value;
            getline(ss, key, ':');

            ss >> ws;
            getline(ss, value);

            if (key == "name") {
                name = value;
            } else if (key == "type") {
                if (value == "normal") {
                    type = Type::NORMAL;
                } else if (value == "fire") {
                    type = Type::FIRE;
                } else if (value == "water") {
                    type = Type::WATER;
                } else if (value == "grass") {
                    type = Type::GRASS;
                } 
            } else if (key == "category") {
                category = value;
            } else if (key == "power") {
                power = stoi(value);
            } else if (key == "pp") {
                pp = stoi(value);
            }
        }
    }

    if (!name.empty()) {
        Move move;
        move.setName(name);
        move.setType(type);
        move.setCategory(category);
        move.setPower(power);
        move.setPP(pp);
        movePool.push_back(move);
    }

    file.close();
}

void Game::matchMove2Pokemon() {
    // Implement Here!
    // Assign moves to each pokemon
    for (Pokemon& pokemon : pokemonPool) {
        vector<Move> matchedMoves; // Define the matchedMoves vector
        for (string& moveName : pokemon.getMoveNames()) {
            for (Move& move : movePool) {
                if (move.getName() == moveName) {
                    matchedMoves.push_back(move); // Add move to matchedMoves vector
                    break;
                }
            }
       }
       pokemon.setMoves(matchedMoves);
    }
    
}

void Game::parseHeldItemPool() {

    ifstream file("held_items.txt");
    string line;
    string name = "", effectType = "", conditionType = "", condition = "";
    bool isConsumable = false;
    double effect = 0.0;

    while (getline(file, line)) {
        if (line.empty()) {
            if (!name.empty() || isConsumable || !effectType.empty() || effect != 0.0 || !conditionType.empty() || !condition.empty()) {
                HeldItem item;
                item.setName(name);
                item.setConsumable(isConsumable);
                item.setEffectType(effectType);
                item.setEffect(effect);
                item.setConditionType(conditionType);
                item.setCondition(condition);
                heldItemPool.push_back(item);
                
                //cout << "Item: " << name << ", isConsumable: " << (isConsumable ? "True" : "False") << endl; // Log output

                name = effectType = conditionType = condition = "";
                isConsumable = false;
                effect = 0.0;
            }
        } else {
            stringstream ss(line);
            string key, value;
            getline(ss, key, ':');
            ss >> ws;
            getline(ss, value);
            if (key == "name") name = value;
            else if (key == "is consumable") isConsumable = (value == "True");
            else if (key == "effect type") effectType = value;
            else if (key == "effect") effect = stod(value);
            else if (key == "condition type") conditionType = value;
            else if (key == "condition") condition = value;
        }
    }

    // If the last line is not empty, create the last item
    if (!name.empty() || isConsumable || !effectType.empty() || effect != 0.0 || !conditionType.empty() || !condition.empty()) {
        HeldItem item;
        item.setName(name);
        item.setConsumable(isConsumable);
        item.setEffectType(effectType);
        item.setEffect(effect);
        item.setConditionType(conditionType);
        item.setCondition(condition);
        heldItemPool.push_back(item);

    }

    file.close();
}

void Game::battle() {
    // Select first Pok?mon for each player
    
    players[0].switchPokemon();
    players[1].switchPokemon();
    system("clear");

    

    

    while (true) {
        cout << "----------" << endl;
        cout << "| Turn " << turn + 1 << " |"<< endl;
        cout << "----------" << endl;

        // Implement Here!
        Move move0, move1;
        //move0.displayInfo();
        //move1.displayInfo();

        // 1. select the turn, same speed pokemon case is ignored
        if (players[0].getCurrentPokemon().getSpeed() > players[1].getCurrentPokemon().getSpeed()) {
            
            bool player0Switched = false;
            bool player1Switched = false;

            Pokemon currentPokemon0 = players[0].getCurrentPokemon();
            Pokemon currentPokemon1 = players[1].getCurrentPokemon();            

            // Player 0's turn
            Action player0Action = players[0].actionSelect();
            if (player0Action == Action::attack) {
                // Perform attack with player 0's pokemon
                move0 = attackSelect(players[0].getCurrentPokemon());
                //attackSelect(players[0].getCurrentPokemon()).displayInfo();
            } else if (player0Action == Action::switchPokemon) {
                // Switch player 0's pokemon
                players[0].switchPokemon();
                player0Switched = true;
            } else if (player0Action == Action::stopGame) {
                cout << "Player 1 stopped the game." << endl;
                exit(1);
            }

            cout << move0.getName() << endl;

            // Player 1's turn
            Action player1Action = players[1].actionSelect();

            if (player1Action == Action::attack) {
                // Perform attack with player 1's pokemon
                move1 = attackSelect(players[1].getCurrentPokemon());
                //attackSelect(players[0].getCurrentPokemon()).displayInfo();
            } else if (player1Action == Action::switchPokemon) {
                // Switch player 1's pokemon
                players[1].switchPokemon();
                player1Switched = true;
            } else if (player1Action == Action::stopGame) {
                cout << "Player 2 stopped the game." << endl;
                exit(1);
            }
            cout << move1.getName() << endl;
            
/*
    player0 => player1 순서로 턴이 돕니다.
    1. player0 : 공격 player1 : 공격
        (1) player0의 공격으로 player1이 살아남았을 경우
            player1 : 공격
            1) player1의 공격으로 player0이 죽었을 경우
                player0 : 교체, 공격없음
        (2) player0의 공격으로 player1이 죽었을 경우
            player1 : 교체, 공격없음

    2. player0 : 교체 player1 : 공격
        player0 : 교체 선택
        player1 : 공격 선택, 데미지는 교체된 포켓몬에 대해 들어감
        (1) player1의 공격으로 player0이 죽었을 경우
            player0 : 교체, 공격없음
    3. player0 : 공격 player1 : 교체

        player0 : 공격 선택, 데미지는 교체된 포켓몬에 대해 들어감
        player1 : 교체 선택
        (교체된 포켓몬을 공격, 데미지는 교체된 포켓몬에 한해 적용)
        (1) player0의 공격으로 player1이 죽었을 경우
            player1 : 교체, 공격없음

    4. player0 : 교체 player1 : 교체
        player0 : 교체처리
        player1 : 교체처리

    M.IN.D control에 대해서) 시전 후 다음에 받는 공격에 대해서 적용되어야 한다 (턴이 돌아도 counter가 되어야)
    GRIT 특수기술에 대해서) 시전 후 다음에 받는 fatal한 공격에 대해서 적용되어야 한다 (턴이 돌아도 counter가 되어야)
*/
            // 2. execute the attack
            // 바꾸면 바뀌고 나서 들아온 것이 공격을 맞는거, 둘 다 바꾸면 공격을 서로 안함
            // 2. execute the attack
            
            if (!player0Switched) {
                attackExecute(players[0].getCurrentPokemon(), players[1].getCurrentPokemon(), move0);
                if (players[1].getCurrentPokemon().getHp() <= 0) {
                    cout << "Player 2's " << players[1].getCurrentPokemon().getName() << " fainted!" << endl;
                    players[1].reducePokemon();
                    if (players[1].getNumPokemon() == 0) {
                        cout << "Player 1 wins!" << endl;
                        exit(1);
                    }
                    players[1].switchPokemon();
                    player1Switched = true;
                }
                if (players[0].getCurrentPokemon().getHp() <= 0) {
                    cout << "Player 1's " << players[0].getCurrentPokemon().getName() << " fainted!" << endl;
                    players[0].reducePokemon();
                    if (players[0].getNumPokemon() == 0) {
                        cout << "Player 2 wins!" << endl;
                        exit(1);
                    }
                    players[0].switchPokemon();
                    
                }
            }
            if (!player1Switched) {
                attackExecute(players[1].getCurrentPokemon(), players[0].getCurrentPokemon(), move1);
                if (players[0].getCurrentPokemon().getHp() <= 0) {
                    cout << "Player 1's " << players[0].getCurrentPokemon().getName() << " fainted!" << endl;
                    players[0].reducePokemon();
                    if (players[0].getNumPokemon() == 0) {
                        cout << "Player 2 wins!" << endl;
                        exit(1);
                    }
                    players[0].switchPokemon();
                    
                }
                if (players[1].getCurrentPokemon().getHp() <= 0) {
                    cout << "Player 2's " << players[1].getCurrentPokemon().getName() << " fainted!" << endl;
                    players[1].reducePokemon();
                    if (players[1].getNumPokemon() == 0) {
                        cout << "Player 1 wins!" << endl;
                        exit(1);
                    }
                    players[1].switchPokemon();
                    
                }
            }
        }
        else {
            bool player0Switched = false;
            bool player1Switched = false;


            Pokemon currentPokemon0 = players[0].getCurrentPokemon();
            Pokemon currentPokemon1 = players[1].getCurrentPokemon();        

            // Player 1's turn
            Action player1Action = players[1].actionSelect();

            if (player1Action == Action::attack) {
                // Perform attack with player 1's pokemon
                move1 = attackSelect(players[1].getCurrentPokemon());
                //attackSelect(players[1].getCurrentPokemon()).displayInfo();
            } else if (player1Action == Action::switchPokemon) {
                // Switch player 1's pokemon
                players[1].switchPokemon();
                player1Switched = true;
            } else if (player1Action == Action::stopGame) {
                cout << "Player 2 stopped the game." << endl;
                exit(1);
            }

            Action player0Action = players[0].actionSelect();
            if (player0Action == Action::attack) {
                // Perform attack with player 0's pokemon
                move0 = attackSelect(players[0].getCurrentPokemon());
                //attackSelect(players[0].getCurrentPokemon()).displayInfo();
            } else if (player0Action == Action::switchPokemon) {
                // Switch player 0's pokemon
                players[0].switchPokemon();
                player0Switched = true;
            } else if (player0Action == Action::stopGame) {
                cout << "Player 1 stopped the game." << endl;
                exit(1);
            }
            
            // 2. execute the attack
            if (!player1Switched) {
                attackExecute(players[1].getCurrentPokemon(), players[0].getCurrentPokemon(), move1);
                if (players[0].getCurrentPokemon().getHp() <= 0) {
                    players[0].reducePokemon();
                    if (players[0].getNumPokemon() == 0) {
                        cout << "Player 2 wins!" << endl;
                        exit(1);
                    }
                    players[0].switchPokemon();
                    player0Switched = true;
                }
                if (players[1].getCurrentPokemon().getHp() <= 0) {
                    players[1].reducePokemon();
                    if (players[1].getNumPokemon() == 0) {
                        cout << "Player 1 wins!" << endl;
                        exit(1);
                    }
                    players[1].switchPokemon();
                    player1Switched = true;
                }
            }
            if (!player0Switched) {
                attackExecute(players[0].getCurrentPokemon(), players[1].getCurrentPokemon(), move0);
                if (players[1].getCurrentPokemon().getHp() <= 0) {
                    players[1].reducePokemon();
                    if (players[1].getNumPokemon() == 0) {
                        cout << "Player 1 wins!" << endl;
                        exit(1);
                    }
                    players[1].switchPokemon();
                    player1Switched = true;
                }
                if (players[0].getCurrentPokemon().getHp() <= 0) {
                    players[0].reducePokemon();
                    if (players[0].getNumPokemon() == 0) {
                        cout << "Player 2 wins!" << endl;
                        exit(1);
                    }
                    players[0].switchPokemon();
                    player0Switched = true;
                }
            }
        }

        // at the end of the turn 조건에서의 아이템 관련 (if the alive, current Pokemon has a held item,
        // it will be triggered) at the end of the turn!
        for (int i = 0; i < 2; i++) {
            Pokemon& currentPokemon = players[i].getCurrentPokemon();
            HeldItem& item = players[i].getCurrentPokemon().getHeldItem();
            if (currentPokemon.getHp() != 0 && item.getConditionType() == "end_of_turn" && currentPokemon.getHp() != currentPokemon.getMaxHp())
            {
                cout << "using" << item.getName() << "..." << endl;
                int heal = 0;
                if (item.getEffectType() == "heal_relative") {
                    heal = int(currentPokemon.getMaxHp() * item.getEffect());
                }
                if (item.getEffectType() == "heal_absolute") {
                    heal = int(item.getEffect());
                }

                if (currentPokemon.getHp() + heal > currentPokemon.getMaxHp())
                {
                    heal = currentPokemon.getMaxHp() - currentPokemon.getHp();
                    currentPokemon.plusHp(heal);
                }
                else
                {
                    currentPokemon.plusHp(heal);
                }
                cout << currentPokemon.getName() << " healed " << heal << " HP!" << endl;
            }
        }
            // Heal below threshold에 대해서 absolute 값도 적용되도록 구현을 해야한다. 


        turn++;

        // Display Pok?mon information
        cout << "Player 1 Pokemon" << endl;
        players[0].getCurrentPokemon().displayInfo();
        cout << "Player 2 Pokemon" << endl;
        players[1].getCurrentPokemon().displayInfo();
    }
}


// struggle skill => global class variable setting
Move struggle("Struggle", Type::NORMAL, MoveCategory::Physical, 30, 999);


Move& Game::attackSelect(Pokemon& attacker) {
    // Implement Here!
    // Implement Here!
    while (true) {
        cout << "Choose a move for " << attacker.getName() << ":" << endl;
        const vector<Move>& moves = attacker.getMoves();

        // struggle move => 전역 변수로!
        bool allMovesDepleted = true;
        for (const Move& move : moves) {
            if (move.getPP() > 0) {
                allMovesDepleted = false;
                break;
            }
        }
        if (allMovesDepleted) {
            cout << "No PP left for all moves! Using Struggle!" << endl;
            return struggle;
        }

        for (int i = 0; i < moves.size(); ++i) {
            cout << i << ": " << moves[i].getName() << " (" << moves[i].getPP() << " PP)" << endl;
        }

        int choice;
        cin >> choice;

        if (choice < 0 || choice >= moves.size()) {
            cout << "Invalid choice, please try again." << endl;
        } else if (moves[choice].getPP() == 0) {
            cout << "No PP left for this move! Choose another move:" << endl;
        } else {

            attacker.getMoves()[choice].reducePP();

            return attacker.getMoves()[choice];
            // attacker 의 move 를 리턴해야 오류가 없다. 지역 변수로 만들어놓은 moves를 리턴하면 큰일난다
        }
    }
    // 1. Get the choice from the user
    // 2. if the choice is invalid, ask the user to choose again
    // 3. return the selected move
}






// Empty item
HeldItem emptyItem;

void Game::attackExecute(Pokemon& attacker, Pokemon& defender, Move& move) {
    // Implement Here!
    // 하나!. Calculate the damage
    // 하나!. Check if the attacker/defender's held item is triggered
    // 하나!. Apply the damage to the defender   

    string moveName = move.getName(); // 기술 이름을 얻습니다.
    cout << attacker.getName() << " used " << moveName << "!" << endl;


    if (move.getName() == "Struggle") {
        cout << attacker.getName() << " used Struggle!" << endl;   
    }


    if (move.getName() == "GRIT") {
        attacker.set_GRIT();
    }

    if (move.getName() == "M.IN.D Control") {
        defender.set_MINDCONTROL();
    }
    // initial damage calculation
    int damage;
 
    // initial damage 
    double init_damage_numerator = 0.00; // 분자
    double init_damage_denominator = 0.00; // 분모

    // 일반적인 경우
    if (attacker.get_MINDCONTROL() == false) {
        if (move.getCategory() == MoveCategory::Physical) { 
            init_damage_numerator = double(attacker.getAttack()) * double(move.getPower());
            init_damage_denominator = double(defender.getDefense());
        } else if (move.getCategory() == MoveCategory::Special) {
            init_damage_numerator = double(attacker.getSpecialAttack()) * double(move.getPower());
            init_damage_denominator = double(defender.getSpecialDefense());
            if (move.getName() == "SpreadCs") {
                SpreadCs spreadCs;
                bool iscorrect = spreadCs.run();
                if (iscorrect) {
                    init_damage_numerator = (double(move.getPower()) / 2) * double(attacker.getSpecialAttack());
                    init_damage_denominator = double(defender.getSpecialDefense());
                } else {
                    init_damage_numerator = double(move.getPower()) * double(attacker.getSpecialAttack());
                    init_damage_denominator = (defender.getSpecialDefense());
                }
            }
        }
    } else {
    // 자기 자신에게 공격을 하는 상태
        if (move.getCategory() == MoveCategory::Physical) { 
            init_damage_numerator = double(attacker.getAttack()) * double(move.getPower());
            init_damage_denominator = double(attacker.getDefense());
        } else if (move.getCategory() == MoveCategory::Special) {
            init_damage_numerator = double(attacker.getSpecialAttack()) * double(move.getPower());
            init_damage_denominator = (attacker.getSpecialDefense());
            if (move.getName() == "SpreadCs") {
                SpreadCs spreadCs;
                bool iscorrect = spreadCs.run();
                if (iscorrect) {
                    init_damage_numerator = (double(move.getPower()) / 2) * double(attacker.getSpecialAttack());
                    init_damage_denominator = double(attacker.getSpecialDefense());
                } else {
                    init_damage_numerator = double(move.getPower()) * double(attacker.getSpecialAttack());
                    init_damage_denominator = double(attacker.getSpecialDefense());
                }
            }
        }
    }


    if (init_damage_numerator == 0) {
        cout << "this move is GRIT or M.IN.D Control" << endl;
    }

    double type_effectiveness = 1.0;
    
    if ((move.getType() == Type::FIRE && defender.getType() == Type::GRASS)||\
    (move.getType() == Type::WATER && defender.getType() == Type::FIRE)||\
    (move.getType() == Type::GRASS && defender.getType() == Type::WATER)) {
        type_effectiveness = 2.0;
    }
    if ((move.getType() == Type::FIRE && defender.getType() == Type::FIRE)||\
    (move.getType() == Type::FIRE && defender.getType() == Type::WATER)||\
    (move.getType() == Type::WATER && defender.getType() == Type::WATER)||\
    (move.getType() == Type::WATER && defender.getType() == Type::GRASS)||\
    (move.getType() == Type::GRASS && defender.getType() == Type::FIRE)||\
    (move.getType() == Type::GRASS && defender.getType() == Type::GRASS)) {
        type_effectiveness = 0.5;
    }

    

    double STAB = 1.0;
    if (attacker.getType() == move.getType()) {
        STAB = 1.5;
    }

    double item_effect = 1.0;
    if (attacker.getHeldItem().getEffectType() == "boost_move_power") {
        // is consumable = true, move_type control
        if (attacker.getHeldItem().getConsumable() == true && attacker.getHeldItem().getConsumed() == false) {
            if (attacker.getHeldItem().getConditionType() == "move_type") {
                if (attacker.getHeldItem().getCondition() == "normal" && move.getType() == Type::NORMAL) {
                    item_effect = attacker.getHeldItem().getEffect();
                    cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
                    attacker.getHeldItem().consumeItem();
                    attacker.setHeldItem(emptyItem);
                }
                if (attacker.getHeldItem().getCondition() == "fire" && move.getType() == Type::FIRE) {
                    item_effect = attacker.getHeldItem().getEffect();
                    cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
                    attacker.getHeldItem().consumeItem();
                    attacker.setHeldItem(emptyItem);
                }
                if (attacker.getHeldItem().getCondition() == "water" && move.getType() == Type::WATER) {
                    item_effect = attacker.getHeldItem().getEffect();
                    cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
                    attacker.getHeldItem().consumeItem();
                    attacker.setHeldItem(emptyItem);
                }
                if (attacker.getHeldItem().getCondition() == "grass" && move.getType() == Type::GRASS) {
                    item_effect = attacker.getHeldItem().getEffect();
                    cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
                    attacker.getHeldItem().consumeItem();
                    attacker.setHeldItem(emptyItem);
                }
            }
            if (attacker.getHeldItem().getConditionType() == "move_category") {
                if (attacker.getHeldItem().getCondition() == "physical" && move.getCategory() == MoveCategory::Physical) {
                    item_effect = attacker.getHeldItem().getEffect();
                    cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
                    attacker.getHeldItem().consumeItem();
                    attacker.setHeldItem(emptyItem);
                }
                if (attacker.getHeldItem().getCondition() == "special" && move.getCategory() == MoveCategory::Special) {
                    item_effect = attacker.getHeldItem().getEffect();
                    cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
                    attacker.getHeldItem().consumeItem();
                    attacker.setHeldItem(emptyItem);
                }
            }

        }
        if (attacker.getHeldItem().getConsumable() == false)
        {
            if (attacker.getHeldItem().getConditionType() == "move_type") {
                if (attacker.getHeldItem().getCondition() == "normal" && move.getType() == Type::NORMAL) {
                    item_effect = attacker.getHeldItem().getEffect();
                    cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
                }
                if (attacker.getHeldItem().getCondition() == "fire" && move.getType() == Type::FIRE) {
                    item_effect = attacker.getHeldItem().getEffect();
                    cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
                }
                if (attacker.getHeldItem().getCondition() == "water" && move.getType() == Type::WATER) {
                    item_effect = attacker.getHeldItem().getEffect();
                    cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
                }
                if (attacker.getHeldItem().getCondition() == "grass" && move.getType() == Type::GRASS) {
                    item_effect = attacker.getHeldItem().getEffect();
                    cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
                }
            }
            if (attacker.getHeldItem().getConditionType() == "move_category") {
                if (attacker.getHeldItem().getCondition() == "physical" && move.getCategory() == MoveCategory::Physical) {
                    item_effect = attacker.getHeldItem().getEffect();
                    cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
                }
                if (attacker.getHeldItem().getCondition() == "special" && move.getCategory() == MoveCategory::Special) {
                    item_effect = attacker.getHeldItem().getEffect();
                    cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
                }
            }     
        }
    }
    
    // 공격 데미지가 지 체력보다 크면 최대 hp만큼 데미지를 입음.
    damage = int(init_damage_numerator * type_effectiveness * STAB * item_effect / init_damage_denominator);

    cout << endl;
    cout << "init_damage_numerator : " << init_damage_numerator << endl;
    cout << "init_damage_denominator : " << init_damage_denominator << endl;
    cout << "type_effectiveness : " << type_effectiveness << endl;
    cout << "STAB : " << STAB << endl;
    cout << "item_effect : " << item_effect << endl;
    cout << "damage : " << damage << endl;
    cout << endl;

    // FPE가 발생할 수 있는 문제는 분자와 분모를 따로 계산하여 한번에 처리했다.



    // M.IN.D control(attacker 기준) 갖고 있는 것 고려
    // 데미지 계산이 => 스스로한테 공격하는 거니까 스스로의 방어력 및 특수방어력을 고려하여야 하게 되는 것.
    // 즉 위의 과정에 대해서 또 수정해서 damage 연산 로직을 세워야 함...
    
    if (attacker.get_MINDCONTROL() == false) {
    // 일반적인 경우
        if (damage < defender.getHp()) {
            cout << defender.getName() << " received " << damage << " damage!" << endl;
            defender.reduceHp(damage);
        } else {
            damage = defender.getHp();
            cout << defender.getName() << " received " << damage << " damage!" << endl;
            defender.reduceHp(damage);
            if (defender.get_GRIT() == true) {
                cout << defender.getName() << " has GRIT!" << endl;
                defender.plusHp(1);
                defender.used_GRIT();
            }
        }
    }

    // GRIT 고려 // GRIT는 일단 얻고나서 유지, 치명상을 받고, 체력이 0이 되어도 1로 살아남음
    if (attacker.get_MINDCONTROL() == true) {
        cout << attacker.getName() << " is controlled and attacked itself!" << endl;
        if (damage < attacker.getHp()) {
            cout << attacker.getName() << " received " << damage << " damage!" << endl;
            attacker.reduceHp(damage);
        } else {
            damage = attacker.getHp();
            cout << attacker.getName() << " received " << damage << " damage!" << endl;
            attacker.reduceHp(damage);
            if (attacker.get_GRIT() == true) {
                cout << attacker.getName() << " has GRIT!" << endl;
                attacker.plusHp(1);
                attacker.used_GRIT();
            }
        }
        attacker.used_MINDCONTROL();
        // boolean 값을 다시 false로 바꾼다.
    }//false로 바꾼다.
    

    // GRIT 고려 // GRIT는 일단 얻고나서 유지, 치명상을 받고, 체력이 0이 되어도 1로 살아남음


    int lifesteal_heal;
    
    // 아래는 포켓몬의 체력 회복에 관한 것. 죽은 포켓몬에 대해서는 체력이 회복되지 않음. 
    // shell bell 등의 lifesteal 아이템 타입에 대하여

    // is consumable false
    if (attacker.getHeldItem().getConditionType() == "damage_done" && attacker.getHeldItem().getConsumable() == false && attacker.getHp() != 0) {
        cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
        lifesteal_heal = int(damage * double(attacker.getHeldItem().getEffect()));
        attacker.plusHp(lifesteal_heal);

        if (attacker.getHp() >= attacker.getMaxHp()) {
            lifesteal_heal -= (attacker.getHp() - attacker.getMaxHp());
            attacker.setHp(attacker.getMaxHp());
        }
        cout << attacker.getName() << " healed " << lifesteal_heal << " HP!" << endl;
    }




    // hp_below_threshold 아이템 타입에 대하여,
    // 공격자에 대하여
    // 1. is consumable && heal_absolute 
    // 2. is consumable && heal_relative
    // 3. is not consumable && heal_absolute
    // 4. is not consumable && heal_relative

    if (attacker.getHeldItem().getConditionType() == "hp_below_threshold" && attacker.getHp() != 0) {
    // 1. is consumable && heal_absolute 
        if (attacker.getHeldItem().getEffectType() == "heal_absolute" && attacker.getHeldItem().getConsumable() == true && attacker.getHeldItem().getConsumed() == false && (attacker.getHp() < (attacker.getMaxHp() * stod(attacker.getHeldItem().getCondition())))) {
            cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
            int heal = attacker.getHeldItem().getEffect();
            attacker.setHp(attacker.getHp() + heal);
            if (attacker.getHp() >= attacker.getMaxHp()) {
                heal -= (attacker.getHp() - attacker.getMaxHp());
                attacker.setHp(attacker.getMaxHp());
            }
            cout << attacker.getName() << " healed " << heal << " HP!" << endl;
            attacker.getHeldItem().consumeItem();
            attacker.setHeldItem(emptyItem);
        }
    // 2. is consumable && heal_relative
        if (attacker.getHeldItem().getEffectType() == "heal_relative" && attacker.getHeldItem().getConsumable() == true && attacker.getHeldItem().getConsumed() == false && (attacker.getHp() < (attacker.getMaxHp() *  stod(attacker.getHeldItem().getCondition())))) {
            cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
            int heal = int(attacker.getMaxHp() * attacker.getHeldItem().getEffect());
            attacker.setHp(attacker.getHp() + heal);
            if (attacker.getHp() >= attacker.getMaxHp()) {
                heal -= (attacker.getHp() - attacker.getMaxHp());
                attacker.setHp(attacker.getMaxHp());
            }
            cout << attacker.getName() << " healed " << heal << " HP!" << endl;
            attacker.getHeldItem().consumeItem();
            attacker.setHeldItem(emptyItem);
        }
    // 3. is not consumable && heal_absolute
        if (attacker.getHeldItem().getEffectType() == "heal_absolute" && attacker.getHeldItem().getConsumable() == false && (attacker.getHp() < (attacker.getMaxHp() *  stod(attacker.getHeldItem().getCondition())))) {
            cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
            int heal = attacker.getHeldItem().getEffect();
            attacker.setHp(attacker.getHp() + heal);
            if (attacker.getHp() >= attacker.getMaxHp()) {
                heal -= (attacker.getHp() - attacker.getMaxHp());
                attacker.setHp(attacker.getMaxHp());
            }
            cout << attacker.getName() << " healed " << heal << " HP!" << endl;
        }
    // 4. is not consumable && heal_relative
        if (attacker.getHeldItem().getEffectType() == "heal_relative" && attacker.getHeldItem().getConsumable() == false && (attacker.getHp() < (attacker.getMaxHp() *  stod(attacker.getHeldItem().getCondition())))) {
            cout << "Using " << attacker.getHeldItem().getName() << "..." << endl;
            int heal = int(attacker.getMaxHp() * attacker.getHeldItem().getEffect());
            attacker.setHp(attacker.getHp() + heal);
            if (attacker.getHp() >= attacker.getMaxHp()) {
                heal -= (attacker.getHp() - attacker.getMaxHp());
                attacker.setHp(attacker.getMaxHp());
            }
            cout << attacker.getName() << " healed " << heal << " HP!" << endl;
        }
    }

    // 방어자에 대하여
    // 1. is consumable && heal_absolute 
    // 2. is consumable && heal_relative
    // 3. is not consumable && heal_absolute
    // 4. is not consumable && heal_relative

    if (defender.getHeldItem().getConditionType() == "hp_below_threshold" && defender.getHp() != 0) {
    // 1. is consumable && heal_absolute 
        if (defender.getHeldItem().getEffectType() == "heal_absolute" && defender.getHeldItem().getConsumable() == true && defender.getHeldItem().getConsumed() == false && (defender.getHp() < (defender.getMaxHp() * stod(defender.getHeldItem().getCondition())))) {
            cout << "Using " << defender.getHeldItem().getName() << "..." << endl;
            int heal = defender.getHeldItem().getEffect();
            defender.setHp(defender.getHp() + heal);
            if (defender.getHp() >= defender.getMaxHp()) {
                heal -= (defender.getHp() - defender.getMaxHp());
                defender.setHp(defender.getMaxHp());
            }
            cout << defender.getName() << " healed " << heal << " HP!" << endl;
            defender.getHeldItem().consumeItem();
            defender.setHeldItem(emptyItem);
        }
    // 2. is consumable && heal_relative
        if (defender.getHeldItem().getEffectType() == "heal_relative" && defender.getHeldItem().getConsumable() == true && defender.getHeldItem().getConsumed() == false && (defender.getHp() < (defender.getMaxHp() * stod(defender.getHeldItem().getCondition())))) {
            cout << "Using " << defender.getHeldItem().getName() << "..." << endl;
            int heal = int(defender.getMaxHp() * defender.getHeldItem().getEffect());
            defender.setHp(defender.getHp() + heal);
            if (defender.getHp() >= defender.getMaxHp()) {
                heal -= (defender.getHp() - defender.getMaxHp());
                defender.setHp(defender.getMaxHp());
            }
            cout << defender.getName() << " healed " << heal << " HP!" << endl;
            defender.getHeldItem().consumeItem();
            defender.setHeldItem(emptyItem);
        }
    // 3. is not consumable && heal_absolute
        if (defender.getHeldItem().getEffectType() == "heal_absolute" && defender.getHeldItem().getConsumable() == false && (defender.getHp() < (defender.getHp() < (defender.getMaxHp() * stod(defender.getHeldItem().getCondition()))))) {
            cout << "Using " << defender.getHeldItem().getName() << "..." << endl;
            int heal = defender.getHeldItem().getEffect();
            defender.setHp(defender.getHp() + heal);
            if (defender.getHp() >= defender.getMaxHp()) {
                heal -= (defender.getHp() - defender.getMaxHp());
                defender.setHp(defender.getMaxHp());
            }
            cout << defender.getName() << " healed " << heal << " HP!" << endl;
        }
    // 4. is not consumable && heal_relative
        if (defender.getHeldItem().getEffectType() == "heal_relative" && defender.getHeldItem().getConsumable() == false && (defender.getHp() < (defender.getHp() < (defender.getMaxHp() * stod(defender.getHeldItem().getCondition()))))) {
            cout << "Using " << defender.getHeldItem().getName() << "..." << endl;
            int heal = int(defender.getMaxHp() * defender.getHeldItem().getEffect());
            defender.setHp(defender.getHp() + heal);
            if (defender.getHp() >= defender.getMaxHp()) {
                heal -= (defender.getHp() - defender.getMaxHp());
                defender.setHp(defender.getMaxHp());
            }
            cout << defender.getName() << " healed " << heal << " HP!" << endl;
        }
    }

    // 공격 시, fainted 된 pokemon에 대한 출력 처리
    if (attacker.getHp() == 0) {
        cout << attacker.getName() << " fainted!" << endl;
    } // 공격 반사 관련 처리
    if (defender.getHp() == 0) {
        cout << defender.getName() << " fainted!" << endl;
    } // 일반적 공격 처리
    

}


/////////////////////


// 파싱 잘 되었는지를 확인하는 용도로 작성된 코드입니다.

void Game::checkPools() {

    cout << "Pokemon Pool Size: " << pokemonPool.size() << "\n";
    if (!pokemonPool.empty()) {
        cout << "First Pokemon in Pool: " << pokemonPool[0].getName() << "\n";
    }

    for (int i = 0 ; i<pokemonPool.size() ;i++) {
        pokemonPool[i].displayInfo();
        vector<Move> moves = pokemonPool[i].getMoves();
        cout << "Moves for " << pokemonPool[i].getName() << ":\n";
        for (const auto& move : moves) {
            cout << "Name: " << move.getName() << "\n";
            cout << "Power: " << move.getPower() << "\n";
            cout << "PP: " << move.getPP() << "\n";
        }
        cout << endl;
    }

    // Check movePool
    cout << "Move Pool Size: " << movePool.size() << "\n";
    if (!movePool.empty()) {
        cout << "First Move in Pool: " << movePool[0].getName() << "\n";
    }

    for (int i = 0 ; i<movePool.size() ;i++) {
        movePool[i].displayInfo();
        cout << endl;
    }

    // Check heldItemPool
    cout << "Held Item Pool Size: " << heldItemPool.size() << "\n";
    if (!heldItemPool.empty()) {
        cout << "First Held Item in Pool: " << heldItemPool[0].getName() << "\n";
    }
    for (int i = 0 ; i<heldItemPool.size() ;i++) {
        heldItemPool[i].displayInfo();
        cout << endl;
    }
}


// checking for selection and checking the codes
void Game::pokemonSelectChecker() {
    vector<bool> selected(pokemonPool.size(), false);
    cout << "Player 1 Pokemons:\n";
    for (const auto& pokemon : players[0].getPokemons()) {
        pokemon.displayInfo();
    }
    cout << "Player 2 Pokemons:\n";
    for (const auto& pokemon : players[1].getPokemons()) {
        pokemon.displayInfo();
    }
}