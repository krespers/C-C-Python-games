#include <iostream>
#include "move.hpp"

using namespace std;

Move::Move() {
    // Implement Here!
    // 기본 생성자
    name = "";
    type = Type::NORMAL;
    category = MoveCategory::Physical;
    power = 0;
    pp = 0;
}

Move::Move(const string& name, Type type, MoveCategory category, int power, int pp)
    : name(name), type(type), category(category), power(power), pp(pp) {
}


void Move::displayInfo() {
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
    if (category == MoveCategory::Physical) {
        cout << "Category: Physical" << endl;
    }
    else {
        cout << "Category: Special" << endl;
    }
    cout << "Power: " << power << endl;
    cout << "PP: " << pp << endl;
}

string Move::getName() const {
    // Implement Here!
    return name;
}

Type Move::getType() const {
    // Implement Here!
    return type;
}

int Move::getPower() const {
    // Implement Here!
    return power;
}

int Move::getPP() const {
    // Implement Here!
    return pp;
}

void Move::setCategory(const string& moveCategory) {
    // Implement Here!
    if (moveCategory == "physical") {
        category = MoveCategory::Physical;
    }
    else if (moveCategory == "special") {
        category = MoveCategory::Special;
    }
}

MoveCategory Move::getCategory() const {
    // Implement Here!
    return category;

}

void Move::setName(string name) {
    // Implement Here!
    this->name = name;

}

void Move::setType(string type) {
    // Implement Here!
    if (type == "Normal") {
        this->type = Type::NORMAL;
    }
    else if (type == "Fire") {
        this->type = Type::FIRE;
    }
    else if (type == "Water") {
        this->type = Type::WATER;
    }
    else if (type == "Grass") {
        this->type = Type::GRASS;
    }
    
}

void Move::setType(Type type) {
    // Implement Here!
    this->type = type;
}

void Move::setPower(int power) {
    // Implement Here!
    this->power = power;
}

void Move::setPP(int pp) {
    // Implement Here!
    this->pp = pp;
}   

void Move::reducePP() {
    // Implement Here!
    if (pp>0){
        pp--;
    }

}