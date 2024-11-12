
#include <string>
#include <vector>
#ifndef __BOARD_H_INCLUDED__
#define __BOARD_H_INCLUDED__

using namespace std;
typedef pair<int, int> int_pair;
#define COLOR_RED "\033[31m"    /* Red */
#define COLOR_YELLOW "\033[33m" /* Yellow */
#define COLOR_BLUE "\033[94m"   /* Blue */
#define COLOR_GREEN "\033[32m"  /* Green */
#define COLOR_DEFAULT "\033[0m" /* Default */

class Board {
    /////////Feel free to add or subtract functions or variables. //////////
  public:
    Board() {
        player_to_board.assign(ROW, vector<int_pair>(COL, {-1, 0}));

/*
예시
예를 들어, player_to_board[0][0]이 {1, 3}이면, 
이는 보드의 (0, 0) 위치에 플레이어 1의 말 3개가 있음을 의미합니다.
보드 초기 상태는 모든 위치가 { -1, 0 }로 초기화되어 있습니다. 
이는 해당 위치에 아무런 플레이어의 말도 없음을 나타냅니다.
*/


        board_mapping = {{-1, -1}, {8, 10}, {6, 10}, {4, 10}, {2, 10},
                         {0, 10},  {0, 8},  {0, 6},  {0, 4},  {0, 2},
                         {0, 0},   {2, 0},  {4, 0},  {6, 0},  {8, 0},
                         {10, 0},  {10, 2}, {10, 4}, {10, 6}, {10, 8},
                         {1, 9},   {3, 7},  {5, 5},  {7, 3},  {9, 1},
                         {1, 1},   {3, 3},  {7, 7},  {9, 9},  {10, 10}};
    }
    void initializeBoard();
    void printBoard();

    const int getRow() { return ROW; }
    const int getCol() { return COL; }

    const vector<int_pair>& getBoardMapping() { return board_mapping; }
    vector<vector<int_pair>>& getPlayerToBoard() { return player_to_board; }
    // 레퍼런스로 리턴해야하는가???


    void printPlayerToBoard();

  private:
    const int ROW = 11;
    const int COL = 11;
    vector<int_pair> board_mapping;
    vector<vector<int_pair>> player_to_board;
    void printPlayer(int player_order, int num_pieces);
};

#endif
