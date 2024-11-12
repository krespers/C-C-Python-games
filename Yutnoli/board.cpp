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
��ü���� ���¸� �����ϸ鼭 �� ĭ�� �ش� ������ ���� �ִ� ���� ǥ�� (���� ���� ǥ��)
���� ��ġ�� [] �ε�, �̰��� ���� ��ġ�� list�� �̾ƿͼ� �� ��ġ�� ��ǥ�� �����Ű��
�� ��ǥ�� �ش��ϴ� ���� �ҷ� �ͼ� ����ϵ��� �Ͽ��� ��.

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
����
���� ���, player_to_board[0][0]�� {1, 3}�̸�, 
�̴� ������ (0, 0) ��ġ�� �÷��̾� 1�� �� 3���� ������ �ǹ��մϴ�.
���� �ʱ� ���´� ��� ��ġ�� { -1, 0 }�� �ʱ�ȭ�Ǿ� �ֽ��ϴ�. 
�̴� �ش� ��ġ�� �ƹ��� �÷��̾��� ���� ������ ��Ÿ���ϴ�.
*/



    // vector<vector<int_pair>> player_to_board;
    
// �ϴ� �� ���� �����鼭 printPlayer() �� üũ�ذ��鼭 ����ؾ� ��.

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
    // ���带 ����մϴ�.
    // ù°��
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

    // ��°��
    //  | [ ]                     [ ] |
    cout << " | [" ;
    printPlayer(player_to_board[1][1].first, player_to_board[1][1].second);
    cout << "]                     [" ;
    printPlayer(player_to_board[1][9].first, player_to_board[1][9].second);
    cout << "] |" << endl;

    // ��°��
    // [ ]    .                 .    [ ]
    cout << "[" ;
    printPlayer(player_to_board[2][0].first, player_to_board[2][0].second);
    cout << "]    .                 .    [" ;
    printPlayer(player_to_board[2][10].first, player_to_board[2][10].second);
    cout << "]" << endl;

    // ��°��
    //  |       [ ]         [ ]       |
    cout << " |       [" ;
    printPlayer(player_to_board[3][3].first, player_to_board[3][3].second);
    cout << "]         [" ;
    printPlayer(player_to_board[3][7].first, player_to_board[3][7].second);
    cout << "]       |" << endl;
    
    // �ټ�°��
    // [ ]          .     .          [ ]
    cout << "[" ;
    printPlayer(player_to_board[4][0].first, player_to_board[4][0].second);
    cout << "]          .     .          [" ;
    printPlayer(player_to_board[4][10].first, player_to_board[4][10].second);
    cout << "]" << endl;

    // ����°��
    //  |             [ ]             |
    cout << " |             [" ;
    printPlayer(player_to_board[5][5].first, player_to_board[5][5].second);
    cout << "]             |" << endl;
    
    // �ϰ�°��
    // [ ]          .     .          [ ]
    cout << "[" ;
    printPlayer(player_to_board[6][0].first, player_to_board[6][0].second);
    cout << "]          .     .          [" ;
    printPlayer(player_to_board[6][10].first, player_to_board[6][10].second);
    cout << "]" << endl;
    
    // ����°��
    //  |       [ ]         [ ]       |
    cout << " |       [" ;
    printPlayer(player_to_board[7][3].first, player_to_board[7][3].second);
    cout << "]         [" ;
    printPlayer(player_to_board[7][7].first, player_to_board[7][7].second);
    cout << "]       |" << endl;
    
    // ��ȩ°��
    // [ ]    .                 .    [ ]
    cout << "[" ;
    printPlayer(player_to_board[8][0].first, player_to_board[8][0].second);
    cout << "]    .                 .    [" ;
    printPlayer(player_to_board[8][10].first, player_to_board[8][10].second);
    cout << "]" << endl;

    // ��°��
    //  | [ ]                     [ ] |
    cout << " | [" ;
    printPlayer(player_to_board[9][1].first, player_to_board[9][1].second);
    cout << "]                     [" ;
    printPlayer(player_to_board[9][9].first, player_to_board[9][9].second);
    cout << "] |" << endl;

    // ����°��
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