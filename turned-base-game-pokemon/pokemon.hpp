#pragma once
#ifndef POKEMON_HPP
#define POKEMON_HPP

#include <string>
#include "move.hpp"
#include "held_item.hpp"
using namespace std;

class Pokemon {
public:
    Pokemon();
    string getName() const;
    Type getType() const;
    int getMaxHp() const;
    int getHp() const;
    int getAttack() const;
    int getDefense() const;
    int getSpecialAttack() const;
    int getSpecialDefense() const;
    int getSpeed() const;
    vector<string>& getMoveNames();
    vector<Move>& getMoves();
    HeldItem& getHeldItem();

    void setName(string);
    void setType(string);
    void setType(Type);
    void setMaxHp(int);
    void setHp(int);
    void setAttack(int);
    void setDefense(int);
    void setSpecialAttack(int);
    void setSpecialDefense(int);
    void setSpeed(int);
    void setMoves(vector<string>&);
    void setMoves(vector<Move>&);
    void setHeldItem(HeldItem);
    
    void reduceHp(int damage);
    void displayInfo() const;



    // 추가로 작성한 멤버 함수 
    void plusHp(int heal);

    void set_GRIT();
    void set_MINDCONTROL();
    bool get_GRIT();
    bool get_MINDCONTROL();
    void used_GRIT();
    void used_MINDCONTROL();


private:
    string name;
    Type type;
    int maxHp;
    int hp;
    int attack;
    int defense;
    int specialAttack;
    int specialDefense;
    int speed;
    vector<string> moveNames;
    vector<Move> moves;
    HeldItem heldItem;


    // 추가로 작성한 멤버 변수, 특수 스킬 구현용
    bool have_GRIT = false;
    bool got_MINDCONTROL = false;

};

#endif