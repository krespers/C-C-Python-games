#include "board.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Initialize the board
void Board::initializeBoard() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            player_to_board[i][j] = {-1, 0};
        }
    }
}

// If a player's pieces are on the board, print the number of pieces
void Board::printPlayer(int player_order, int num_pieces) {
    if (player_order == 0) {
        cout << COLOR_RED << num_pieces << COLOR_DEFAULT;
    } else if (player_order == 1) {
        cout << COLOR_BLUE << num_pieces << COLOR_DEFAULT;
    } else if (player_order == 2) {
        cout << COLOR_GREEN << num_pieces << COLOR_DEFAULT;
    } else if (player_order == 3) {
        cout << COLOR_YELLOW << num_pieces << COLOR_DEFAULT;
    } else {
        cout << COLOR_DEFAULT << ' ' << COLOR_DEFAULT;
    }
}

/*
- print the entire board state
(initialized board state)
[ ] - [ ] - [ ] - [ ] - [ ] - [ ]
 | [ ]                     [ ] |
[ ]    .                 .    [ ]
 |       [ ]         [ ]       |
[ ]          .     .          [ ]
 |             [ ]             |
[ ]          .     .          [ ]
 |       [ ]         [ ]       |
[ ]    .                 .    [ ]
 | [ ]                     [ ] |
[ ] - [ ] - [ ] - [ ] - [ ] - [ ]^Start
 .  .  .  .  .  .  .  .  .  .  .
전체적인 형태를 유지하면서 빈 칸에 해당 유저가 갖고 있는 말을 표현 (숫자 또한 표현)
말의 위치가 [] 인데, 이것은 말의 위치를 list로 뽑아와서 각 위치와 좌표를 연결시키고
그 좌표에 해당하는 값을 불러 와서 출력하도록 하여야 함.

class Board {
    /////////Feel free to add or subtract functions or variables. //////////
  public:
    Board() {
        player_to_board.assign(ROW, vector<int_pair>(COL, {-1, 0}));
        board_mapping = {{-1, -1}, {8, 10}, {6, 10}, {4, 10}, {2, 10},
                         {0, 10},  {0, 8},  {0, 6},  {0, 4},  {0, 2},
                         {0, 0},   {2, 0},  {4, 0},  {6, 0},  {8, 0},
                         {10, 0},  {10, 2}, {10, 4}, {10, 6}, {10, 8},
                         {1, 9},   {3, 7},  {5, 5},  {7, 3},  {9, 1},
                         {1, 1},   {3, 3},  {7, 7},  {9, 9},  {10, 10}};
    }
    void initializeBoard();
    void printBoard();

  private:
    const int ROW = 11;
    const int COL = 11;
    vector<int_pair> board_mapping;
    vector<vector<int_pair>> player_to_board;
    void printPlayer(int player_order, int num_pieces);
};


/*
예시
예를 들어, player_to_board[0][0]이 {1, 3}이면, 
이는 보드의 (0, 0) 위치에 플레이어 1의 말 3개가 있음을 의미합니다.
보드 초기 상태는 모든 위치가 { -1, 0 }로 초기화되어 있습니다. 
이는 해당 위치에 아무런 플레이어의 말도 없음을 나타냅니다.
*/



    // vector<vector<int_pair>> player_to_board;
    
// 일단 이 판을 만들어가면서 printPlayer() 를 체크해가면서 출력해야 함.

/*
[ ] - [ ] - [ ] - [ ] - [ ] - [ ]
 | [ ]                     [ ] |
[ ]    .                 .    [ ]
 |       [ ]         [ ]       |
[ ]          .     .          [ ]
 |             [ ]             |
[ ]          .     .          [ ]
 |       [ ]         [ ]       |
[ ]    .                 .    [ ]
 | [ ]                     [ ] |
[ ] - [ ] - [ ] - [ ] - [ ] - [ ]^Start
*/
    

void Board::printBoard() {
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    // 보드를 출력합니다.
    // 첫째줄
    // [ ] - [ ] - [ ] - [ ] - [ ] - [ ]
    cout << "[" ;
    printPlayer(player_to_board[0][0].first, player_to_board[0][0].second);
    cout << "] - [" ;
    printPlayer(player_to_board[0][2].first, player_to_board[0][2].second);
    cout << "] - [" ;
    printPlayer(player_to_board[0][4].first, player_to_board[0][4].second);
    cout << "] - [" ;
    printPlayer(player_to_board[0][6].first, player_to_board[0][6].second);
    cout << "] - [" ;
    printPlayer(player_to_board[0][8].first, player_to_board[0][8].second);
    cout << "] - [" ;
    printPlayer(player_to_board[0][10].first, player_to_board[0][10].second);
    cout << "]" << endl;

    // 둘째줄
    //  | [ ]                     [ ] |
    cout << " | [" ;
    printPlayer(player_to_board[1][1].first, player_to_board[1][1].second);
    cout << "]                     [" ;
    printPlayer(player_to_board[1][9].first, player_to_board[1][9].second);
    cout << "] |" << endl;

    // 셋째줄
    // [ ]    .                 .    [ ]
    cout << "[" ;
    printPlayer(player_to_board[2][0].first, player_to_board[2][0].second);
    cout << "]    .                 .    [" ;
    printPlayer(player_to_board[2][10].first, player_to_board[2][10].second);
    cout << "]" << endl;

    // 넷째줄
    //  |       [ ]         [ ]       |
    cout << " |       [" ;
    printPlayer(player_to_board[3][3].first, player_to_board[3][3].second);
    cout << "]         [" ;
    printPlayer(player_to_board[3][7].first, player_to_board[3][7].second);
    cout << "]       |" << endl;
    
    // 다섯째줄
    // [ ]          .     .          [ ]
    cout << "[" ;
    printPlayer(player_to_board[4][0].first, player_to_board[4][0].second);
    cout << "]          .     .          [" ;
    printPlayer(player_to_board[4][10].first, player_to_board[4][10].second);
    cout << "]" << endl;

    // 여섯째줄
    //  |             [ ]             |
    cout << " |             [" ;
    printPlayer(player_to_board[5][5].first, player_to_board[5][5].second);
    cout << "]             |" << endl;
    
    // 일곱째줄
    // [ ]          .     .          [ ]
    cout << "[" ;
    printPlayer(player_to_board[6][0].first, player_to_board[6][0].second);
    cout << "]          .     .          [" ;
    printPlayer(player_to_board[6][10].first, player_to_board[6][10].second);
    cout << "]" << endl;
    
    // 여덟째줄
    //  |       [ ]         [ ]       |
    cout << " |       [" ;
    printPlayer(player_to_board[7][3].first, player_to_board[7][3].second);
    cout << "]         [" ;
    printPlayer(player_to_board[7][7].first, player_to_board[7][7].second);
    cout << "]       |" << endl;
    
    // 아홉째줄
    // [ ]    .                 .    [ ]
    cout << "[" ;
    printPlayer(player_to_board[8][0].first, player_to_board[8][0].second);
    cout << "]    .                 .    [" ;
    printPlayer(player_to_board[8][10].first, player_to_board[8][10].second);
    cout << "]" << endl;

    // 열째줄
    //  | [ ]                     [ ] |
    cout << " | [" ;
    printPlayer(player_to_board[9][1].first, player_to_board[9][1].second);
    cout << "]                     [" ;
    printPlayer(player_to_board[9][9].first, player_to_board[9][9].second);
    cout << "] |" << endl;

    // 열한째줄
    // [ ] - [ ] - [ ] - [ ] - [ ] - [ ]^Start
    cout << "[" ;
    printPlayer(player_to_board[10][0].first, player_to_board[10][0].second);
    cout << "] - [";
    printPlayer(player_to_board[10][2].first, player_to_board[10][2].second);
    cout << "] - [";
    printPlayer(player_to_board[10][4].first, player_to_board[10][4].second);
    cout << "] - [";
    printPlayer(player_to_board[10][6].first, player_to_board[10][6].second);
    cout << "] - [";
    printPlayer(player_to_board[10][8].first, player_to_board[10][8].second);
    cout << "] - [";
    printPlayer(player_to_board[10][10].first, player_to_board[10][10].second);
    cout << "]^Start" << endl;
    /////////////////////////////////////////////////////////////////////////
}


void Board::printPlayerToBoard() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            cout << player_to_board[i][j].first << " " << player_to_board[i][j].second << " ";
        }
        cout << endl;
    }
}