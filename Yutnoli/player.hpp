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


    // pieces ���Ϳ� ���õ� �Լ�



    const vector<int>& getPieces() const { return pieces; } 
    int getArrivedPieceNum() const { return arrived_piece_num; }
    
    // pieces ���͸� ��ȸ�ϸ鼭 pos�� ���� ���� ���� ���Ұ� �ִ��� Ȯ��
    bool hasPieceAt(int pos) const;
    
    // ���� ���� ���� ��ƹ�����, pos ��ġ�� �ش��ϴ� ���� ��� ���� position 0���� ����
    void sendPieceToStart(int pos);

    // �̰��� ���� �����̴� �Լ�
    // ���� ��ġ�� ���� ��ġ�� �޾Ƽ� ���� ��ġ�� �ش��ϴ� ���� ���� ��ġ�� �ű�
    // ���, current_pos�� 0, 0, 0, 0�� ��쿡 movePiece(0,1)�� ������ 1,1,1,1 �� �Ǵ°� �ƴϰ� 0,0,0,1�� ��
    // �׸��� current_pos�� 1~29 ���̿� ������ ������ ��ġ�� �� �� �̻��� ���� �ִ� ��쿡�� �� ������ �Ѳ����� �ű�
    void movePiece(int current_pos, int next_pos);

    // pieces ���͸� sort�ϴ� �Լ�
    void sortPieces() { sort(pieces.begin(), pieces.end()); }

    void updateArrivedPieceNum() { arrived_piece_num = std::count(pieces.begin(), pieces.end(), 100); }

    // yut_list�� ���õ� �Լ�
    multiset<YutName> getYutList() { return yut_list; }
    void removeYut(string yut) { auto it = yut_list.find(YutName{yut}); if (it != yut_list.end()) { yut_list.erase(it); } }
    bool isYutListEmpty() { return yut_list.empty(); }

    void resetPlayer();

  protected:
    vector<int> pieces;
    // �� piece�� ��ġ�� �����ϴ� vector�� Ȯ�ε�. ó�� 0���� ������.
    // ó���� ���� ���� �ϰ� ���� pieces�� ������ �����Կ� ���� �� ũ�Ⱑ ������
    int arrived_piece_num = 0; 
    // ������ piece�� ���� �����ϴ� ������ Ȯ�ε�. ó�� 0���� ������. piece�� ũ�Ⱑ 100�� �Ǹ� 1�� �þ.
    // ��� �� user�� arrived_piece_num�� ó�� pieces�� ũ��� �������� ������ �����
    multiset<YutName> yut_list; 
    // ���� �Ͽ��� ���� ���� ����� �����ϴ� multiset. YutName Ŭ�������� �����ϴ� ������ Ȯ�ε�.
};



class AnimalPlayer : public Player {
    /////////Feel free to add or subtract functions or variables. //////////
    // 0:pig 1:dog 2:sheep 3:cow

    public:
      AnimalPlayer() {}
      AnimalPlayer(string name, int animal_type) : name(name), animal_type(animal_type) { pieces = vector<int>(4,0); };

      // pieces�� �����ϴ� �Լ�
      void setPieces(vector<int> pieces) { this->pieces = pieces; }




      string getName() const { return name; }
      void setName(string name) { this->name = name; }
      int getAnimalType() const { return animal_type; }
      void setAnimalType(int type) { animal_type = type; }


    // pig
    // If someone else (player A) catches you, A ends his turn immediately. sheep ���� pig�� �� ��.
    // ���� pig�� ���� ��ƹ�����, pos ��ġ�� �ش��ϴ� pig�� ���� ���� ��� �� ���� position 0���� ����
    // void sendPieceToStart(int pos) { for (int& piece : pieces) { if (piece == pos) { piece = 0; } } } 
    // �긦 Ȱ���ϸ� �ǰڱ���.
    void resetYutList() { yut_list.clear(); }


    // dog
    // Even if the stick result is geol (�ϳ��� geol), you should throw again (�ٽ� �� �� �� ����!)
    void throwYutDog(Yut &yut);

    // sheep
    // If you catch someone else, you have two chances to throw again.
    //game_extension���� ����


    // cow ��� : You can only move along the specific path
    // cow�� 0,1,2,3,4,5,20,21,22,23,24,15,16,17,18,19,29,100�� ��Ʈ�θ� �̵���
    int movePlayerCow(int pos, string yut);

    void resetAnimalPlayer();


    protected:
      // �÷��̾� �̸��� �����ϴ� ����
      string name;
      // ������ ������ �����ϴ� ���� 0:pig 1:dog 2:sheep 3:cow�� ������.
      int animal_type;
      

};

#endif
