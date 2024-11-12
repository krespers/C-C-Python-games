#include "yut.hpp"
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__
using namespace std;

#define BACK_DO 0
#define DO 1
#define GAE 2
#define GEOL 3
#define YUT 4
#define MO 5

class Player {
    /////////Feel free to add or subtract functions or variables. //////////

  public:
    Player() {}

    Player(int num_pieces) : pieces(num_pieces, 0) {}
    int movePlayer(int pos, string yut);
    void throwYut(Yut &yut);


    // pieces 벡터와 관련된 함수



    const vector<int>& getPieces() const { return pieces; } 
    int getArrivedPieceNum() const { return arrived_piece_num; }
    
    // pieces 벡터를 순회하면서 pos와 같은 값을 가진 원소가 있는지 확인
    bool hasPieceAt(int pos) const;
    
    // 내가 남의 말을 잡아버리면, pos 위치에 해당하는 남의 모든 말을 position 0으로 만듦
    void sendPieceToStart(int pos);

    // 이것은 말을 움직이는 함수
    // 현재 위치와 다음 위치를 받아서 현재 위치에 해당하는 말을 다음 위치로 옮김
    // 대신, current_pos가 0, 0, 0, 0인 경우에 movePiece(0,1)을 받으면 1,1,1,1 이 되는게 아니고 0,0,0,1이 됨
    // 그리고 current_pos가 1~29 사이에 있으며 동일한 위치에 두 개 이상의 말이 있는 경우에는 그 말들을 한꺼번에 옮김
    void movePiece(int current_pos, int next_pos);

    // pieces 벡터를 sort하는 함수
    void sortPieces() { sort(pieces.begin(), pieces.end()); }

    void updateArrivedPieceNum() { arrived_piece_num = std::count(pieces.begin(), pieces.end(), 100); }

    // yut_list와 관련된 함수
    multiset<YutName> getYutList() { return yut_list; }
    void removeYut(string yut) { auto it = yut_list.find(YutName{yut}); if (it != yut_list.end()) { yut_list.erase(it); } }
    bool isYutListEmpty() { return yut_list.empty(); }

    void resetPlayer();

  protected:
    vector<int> pieces;
    // 각 piece의 위치를 저장하는 vector로 확인됨. 처음 0으로 설정됨.
    // 처음에 게임 시작 하고 나서 pieces의 갯수를 설정함에 따라서 그 크기가 정해짐
    int arrived_piece_num = 0; 
    // 도착한 piece의 수를 저장하는 변수로 확인됨. 처음 0으로 설정됨. piece의 크기가 100이 되면 1씩 늘어남.
    // 어느 한 user의 arrived_piece_num이 처음 pieces의 크기와 같아지면 게임이 종료됨
    multiset<YutName> yut_list; 
    // 현재 턴에서 윷을 던진 결과를 저장하는 multiset. YutName 클래스형을 저장하는 것으로 확인됨.
};



class AnimalPlayer : public Player {
    /////////Feel free to add or subtract functions or variables. //////////
    // 0:pig 1:dog 2:sheep 3:cow

    public:
      AnimalPlayer() {}
      AnimalPlayer(string name, int animal_type) : name(name), animal_type(animal_type) { pieces = vector<int>(4,0); };

      // pieces를 수정하는 함수
      void setPieces(vector<int> pieces) { this->pieces = pieces; }




      string getName() const { return name; }
      void setName(string name) { this->name = name; }
      int getAnimalType() const { return animal_type; }
      void setAnimalType(int type) { animal_type = type; }


    // pig
    // If someone else (player A) catches you, A ends his turn immediately. sheep 보다 pig가 더 셈.
    // 내가 pig의 말을 잡아버리면, pos 위치에 해당하는 pig를 잡은 남의 모든 말 또한 position 0으로 만듦
    // void sendPieceToStart(int pos) { for (int& piece : pieces) { if (piece == pos) { piece = 0; } } } 
    // 얘를 활용하면 되겠구만.
    void resetYutList() { yut_list.clear(); }


    // dog
    // Even if the stick result is geol (하나의 geol), you should throw again (다시 한 번 더 던짐!)
    void throwYutDog(Yut &yut);

    // sheep
    // If you catch someone else, you have two chances to throw again.
    //game_extension에서 구현


    // cow 기술 : You can only move along the specific path
    // cow는 0,1,2,3,4,5,20,21,22,23,24,15,16,17,18,19,29,100의 루트로만 이동함
    int movePlayerCow(int pos, string yut);

    void resetAnimalPlayer();


    protected:
      // 플레이어 이름을 저장하는 변수
      string name;
      // 동물의 종류를 저장하는 변수 0:pig 1:dog 2:sheep 3:cow로 설정됨.
      int animal_type;
      

};

#endif
