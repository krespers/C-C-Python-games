#include <iostream>
#include <vector>
#include <string>
#include "pokemon.hpp"

using namespace std;

Pokemon::Pokemon() {
    // Implement Here!
    name = "";
    type = Type::NORMAL;
    maxHp = 0;
    hp = 0;
    attack = 0;
    defense = 0;
    specialAttack = 0;
    specialDefense = 0;
    speed = 0;
}

string Pokemon::getName() const {
    // Implement Here!
    return name;
}

Type Pokemon::getType() const {
    // Implement Here!
    return type;
}

int Pokemon::getMaxHp() const {
    // Implement Here!
    return maxHp;
}

int Pokemon::getHp() const {
    // Implement Here!
    return hp;
}

int Pokemon::getAttack() const {
    // Implement Here!
    return attack;
}

int Pokemon::getDefense() const {
    // Implement Here!
    return defense;
}

int Pokemon::getSpecialAttack() const {
    // Implement Here!
    return specialAttack;
}

int Pokemon::getSpecialDefense() const {
    // Implement Here!
    return specialDefense;
}

int Pokemon::getSpeed() const {
    // Implement Here!
    return speed;
}

vector<string>& Pokemon::getMoveNames() {
    // Implement Here!
    return moveNames;

}

vector<Move>& Pokemon::getMoves() {
    // Implement Here!
    return moves;

}

HeldItem& Pokemon::getHeldItem() {
    // Implement Here!
    return heldItem;
}

void Pokemon::setName(string name) {
    // Implement Here!
    this->name = name;
}

void Pokemon::setType(string type) {
    // Implement Here!
    if (type == "NORMAL") {
        this->type = Type::NORMAL;
    }
    else if (type == "FIRE") {
        this->type = Type::FIRE;
    }
    else if (type == "WATER") {
        this->type = Type::WATER;
    }
    else if (type == "GRASS") {
        this->type = Type::GRASS;
    }
    
}

void Pokemon::setType(Type type) {
    // Implement Here!
    this->type = type;

}

void Pokemon::setMaxHp(int maxHp) {
    // Implement Here!
    this->maxHp = maxHp;
}

void Pokemon::setHp(int hp) {
    // Implement Here!
    this->hp = hp;
}

void Pokemon::setAttack(int attack) {
    // Implement Here!
    this->attack = attack;
}

void Pokemon::setDefense(int defense) {
    // Implement Here!
    this->defense = defense;
}

void Pokemon::setSpecialAttack(int specialAttack) {
    // Implement Here!
    this->specialAttack = specialAttack;
}

void Pokemon::setSpecialDefense(int specialDefense) {
    // Implement Here!
    this->specialDefense = specialDefense;
}

void Pokemon::setSpeed(int speed) {
    // Implement Here!
    this->speed = speed;
}

void Pokemon::setMoves(vector<string>& moves) {
    // Implement Here!
    moveNames = moves;
}

void Pokemon::setMoves(vector<Move>& moves) {
    // Implement Here!
    this->moves = moves;
}

void Pokemon::setHeldItem(HeldItem heldItem) {
    // Implement Here!
    this->heldItem = heldItem;
}

void Pokemon::reduceHp(int damage) {
    // Implement Here!
    hp -= damage;

}

void Pokemon::displayInfo() const {
    cout << "Name: " << name << endl;
    if (type == Type::NORMAL) {
        cout << "Type: Normal" << endl;
    }
    else if (type == Type::FIRE) {
        cout << "Type: Fire" << endl;
    }
    else if (type == Type::WATER) {
        cout << "Type: Water" << endl;
    }
    else if (type == Type::GRASS) {
        cout << "Type: Grass" << endl;
    }
    cout  << "Current HP: " << hp << endl;
    cout  << "Max HP: " << maxHp<< endl;
    cout  << "Attack: " << attack << endl;
    cout  << "Defense: " << defense << endl;
    cout  << "Special Attack: " << specialAttack << endl;
    cout  << "Special Defense: " << specialDefense << endl;
    cout  << "Speed: " << speed << endl;
    cout  << "Moves: ";
    for (size_t i = 0; i < moveNames.size(); ++i) {
        cout << moveNames[i];
        if (i < moveNames.size() - 1) {
            cout << ", ";
        }
    }
    if (heldItem.getName() != "") {
        cout << endl;
        cout  << "Held Item: " << heldItem.getName() << endl;
    } else {
        cout << endl;
        cout  << "Held Item: None" << endl;
    }
    cout << endl;


/// 특수 스킬 상태 확인용 코드.
    cout << "have GRIT : " << have_GRIT << endl;
    cout << "got_MINDCONTROL : "<< got_MINDCONTROL << endl;
///

    cout  << "==================" << endl;
}



//////////////// Additional Function ////////////////
void Pokemon::plusHp(int heal) {
    // Implement Here!
    hp += heal;
}

void Pokemon::set_GRIT() {
    this->have_GRIT = true;
}

void Pokemon::used_GRIT() {
    this->have_GRIT = false;
}

void Pokemon::set_MINDCONTROL() {
    this->got_MINDCONTROL = true;
}

void Pokemon::used_MINDCONTROL() {
    this->got_MINDCONTROL = false;
}

bool Pokemon::get_GRIT() {
    return have_GRIT;
}

bool Pokemon::get_MINDCONTROL() {
    return got_MINDCONTROL;
}