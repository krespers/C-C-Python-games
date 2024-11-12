#include "board.hpp"
#include "player.hpp"
#include "yut.hpp"
#include <algorithm>
#include <string>
#include <vector>
#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

using namespace std;

class Game {
    /////////Feel free to add or subtract functions or variables. //////////
  public:
    Game() {}
    ~Game() {}
    virtual int menuSelect();
    void run();
    virtual void printPieceState();
    virtual void printCurrentTurn(int player_order);

    virtual void fillPlayerToBoard(Board& board);
    virtual bool isGameEnd();
    Player* getCurrentPlayer() { return pPlayer; }
  protected:
    int player_num;
    int piece_num;
    Board board;
    Yut yut = Yut(0.5);

    vector<Player> players;
    int current_player_index;

  private:
    Player *pPlayer;
};




class GameExtension : public Game {
    /////////Feel free to add or subtract functions or variables. //////////
  public:
    // ���� ���� �����͸� ���Ϸκ��� �о�ͼ� ������ �����ϴ� �Լ�

    GameExtension() {}
    ~GameExtension() {}
    

    void restoreGame();
    void updatingGame_info();

    void animalSelect();

    int menuSelect() override;
    void login();
    void run();


    void printPieceState() override;
    void printCurrentTurn(int player_order) override;
    void fillPlayerToBoard(Board& board) override;
    bool isGameEnd() override;



    void addUserInfo(const string& id, const string& password) { userdatabase.push_back(make_pair(id, password)); }
    vector<pair<string,string>> getUserdatabase() const { return userdatabase; }

    void addGameSavefile_Players(const vector<string>& player) { gameSavefile_Players.push_back(player); }
    vector<vector<string>> getGameSavefile_Players() const { return gameSavefile_Players; }

    void printLoginUserInfo();
    void addLoginUserInfo(const string& id, const string& password) { LoginUserInfo.push_back(make_pair(id, password)); }
    vector<pair<string,string>> getLoginUserInfo() const { return LoginUserInfo; }

    int getgameturn() const { return gameturn; }
    void setgameturn(int turn) { gameturn = turn; }



    // ���� ���� �����͸� �����Ͽ� ���Ϸ� ����ϴ� �Լ�
    bool backupChecker();
    void backupGame();

    vector<AnimalPlayer> Animalplayers;

  
    // �Է��� ������ ���Ҹ� ���Ͽ�, ������ �����ϰ� ������ ��Ҹ����� ���ϼ��� �˻��ϴ� �Լ�
    bool isSameIgnoreOrder(const vector<pair<string,string>>& LoginUserInfo, const vector<vector<string>>& gameSavefile_Players);
    void printAnimalPlayerInfo();
    void printAnimalPlayerInfo2();  

    

    void resetGameExtension() {
      LoginUserInfo.clear();
      gameSavefile_Players.clear();
      userdatabase.clear();
      gameturn = 0;
    }


  private:
    vector<pair<string, string>> userdatabase;  // parsing�� ���� ������ �ϳ��� � ������ ������ �޴´�.

    int gameturn; // parsing�� ���� ������ �ϳ��� � ������ ������ �޴´�

    // loginInfo�� id�� password�� �����ϴ� vector
    vector<pair<string,string>> LoginUserInfo;

    //game savefile import database
    
    // Olivia Ava Sophia | Olivia 2 0 0 10 10 | Ava 1 0 0 2 100 | Sophia 3 0 3 100 100 | 2 
    vector<vector<string>> gameSavefile_Players; // ù file�� Olivia Ava Sophia���� ã�� ��.


};


#endif