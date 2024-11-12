#include "game.hpp"
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

/* menuSelect function
This function is used to choose "game start / end program"
The function returns 0 if the user selects the end
program, and returns 1 if the user selects the game start.
*/
int Game::menuSelect() {
    int i;
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    // 필요시 작성...
    // menuSelect를 하고 
    // game start를 누르면 run 함수를 실행

    //////////////////////////////////////////////////////////////////////
    while (1) {
        cout << "************************************************************"
             << endl;
        cout << "************************   Menu   **************************"
             << endl;
        cout << "************************************************************"
             << endl;

        cout << "1. game start" << endl;
        cout << "2. end program" << endl;
        cout << "Select the function you want : ";
        cin >> i;
        if (i < 1 || i > 2) {
            cout << "Type an integer from 1 to 2!" << endl;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        if (i == 2) {
            return 0;
        } else {
            // i == 1를 눌렀을 경우에,
            run();
            return 1;
        }
    }
    return 1;
}

/* run function
This function is used to run the game.
The function is called when the user selects the game start.
The function is used to run the game until the game ends.

>> required cout statements in run function
1. cout << "number of players (2, 3, 4) : ";
2. cout << "number of pieces per player (1, 2, 3, 4) : ";
3. cout << "Write down the position of the player to move and yut" << endl;
   cout << "(back-do, do, gae, geol, yut, and mo)" << endl;
   cout << ">> position : ";
   cout << ">> yut : ";
4. cout << "Player " << ??? << " win" << endl;
*/
void Game::run() {
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    cout << "number of players (2, 3, 4) : ";
    int num_players;
    cin >> num_players;

    cout << "number of pieces per player (1, 2, 3, 4) : ";
    int num_pieces;
    cin >> num_pieces;

    // 게임에 필요한 player 수만큼 생성하고, 각 플레이어에게 말의 개수를 설정합니다.
    //vector<Player> players;

    for (int i = 0; i < num_players; ++i) {
        players.push_back(Player(num_pieces));
    }
    
    //말의 갯수와 위치를 출력(?)
    /*
    for (int i = 0; i < num_players; ++i) {
        const vector<int>& playerPieces = players[i].getPieces();
        cout << "Player " << i+1 << " has " << playerPieces.size() << " pieces.\n";
        for (int j = 0; j < playerPieces.size(); ++j) {
            cout << "Piece " << j+1 << " is at position " << playerPieces[j] << ".\n";
        }
    }
    */

   // 보드를 생성.
    Board board;
    board.initializeBoard();

    // 플레이어 0,1,2,3 (2,3은 현재 players.size() 크기에 따라 순차적으로 돌아가면서 진행.)
    // 플레이어가 윷을 일단 던짐
    // 던지고 나서 board.printBoard(); printPieceState(); 

    // bool is_game_end()


    // 일단 누군가가 가진 piece가 다 집으로 돌아오면 그때는 게임이 끝난다.
    // 그리고 선택한 유형의 게임이 다시 시작된다!
    /*
    -----------------------------------------
Not started : 

Arrived : 

-----------------------------------------
Player 0 turn
Piece : 29 
Yut : gae 
Write down the position of the player to move and yut
(back-do, do, gae, geol, yut, and mo)
>> position : 29
>> yut : gae
Player 0 win
************************************************************
************************   Menu   **************************
************************************************************
1. game start
2. end program
Select the function you want : 
    */


    // 근데 지금은 게임이 끝나지 않는 상황이다. 버그 수정 필요

    /*
     게임 끝나는 상황 (이긴 사람 출력, 누군가가 이기면 게임 종료,
     게임이 끝나고 나서 다시 메뉴로 돌아가기) / 
     원점으로부터 출발할 경우에 말이 2개씩 이동하는 현상 발견
     구한 yut 함수에 처음에 백도 한 player0이 player1이 던져야 하는데 player0이 또다시 던지는 이상(?) 현상 발견
    */




    while (!isGameEnd()) {
        for (int i = 0; i < players.size(); ++i) {



            // i번째 플레이어가 일단은 자기 턴이 왔으니까 처음에, 윷을 던집니다.
            Player &current_player = players[i];
            current_player.throwYut(yut);

            // players[i]의 yut_list를 다 써버릴 때까지는 혹은 자기가 모든 pieces의 위치를 도착(100)으로 만들지 않으면
            // 자신의 턴이 끝나지 않습니다
            while (!current_player.isYutListEmpty()) {      

                // 일단 자기가 갖고 있는 윷이 체크된 상태에서 게임이 끝나지 않았다면 아래를 실행함.
                if(current_player.getArrivedPieceNum() == num_pieces) {
                    break;
                }

                fillPlayerToBoard(board); //게임에 참여중인 "모든 플레이어"의 말 위치를 보드에 채워야 합니다.
                board.printBoard(); // 현재 보드 상태를 출력 
                // board.printPlayerToBoard(); // 디버깅 확인용 코드 코드
                printPieceState(); // 말의 상태를 출력합니다.
                printCurrentTurn(i); // 현재 플레이어의 턴을 출력합니다.

                // 플레이어의 입력을 받습니다.
                cout << "Write down the position of the player to move and yut" << endl;
                cout << "(back-do, do, gae, geol, yut, and mo)" << endl;
                cout << ">> position : ";
                int position;
                cin >> position;
                cout << ">> yut : ";
                string input_yut;
                cin >> input_yut;
                current_player.removeYut(input_yut); // 사용한 yut은 yut_list에서 삭제

                // 이동 말을 움직이고, 그 player의 yut list에 있던 것 중에 입력한 것과 일치하는 것을 삭제
                // 또한 movePlayer을 했을 때, 그 player의 모든 piece 0 position에 있을 경우
                // 임의의 하나의 piece만을 옮깁니다. 또한 위치가 1~29에 있는 경우 이동을 해야 합니다.
                // 이 함수는 특정 position에 있는 것이 입력된 yut 만큼 이동하였을 때, 어느 위치로 가는지를 반환합니다.

                int solution_position = current_player.movePlayer(position, input_yut);
                // 만약에 나온 결과가 solution_position 위치가 0이라면, 이동할 수 있는 위치가 없다는 것이므로 둠

                if (solution_position == 0) {
                    continue;
                }

                

                // 탐색하는 함수 나온 결과에 solution_position에 다른 플레이어의 말이 있는 경우
                current_player.sortPieces();
                
                // 다른 플레이어의 말이 있는지 확인합니다.
                bool hasOtherPlayerPiece = false;
                for (Player& other_player : players) {
                    if (&other_player != &current_player && other_player.hasPieceAt(solution_position)) {
                        // 잡은 말을 시작 위치로 보냅니다.
                        other_player.sendPieceToStart(solution_position);  

                        // 윷을 한 번 더 던져서 윷 리스트에 추가합니다.
                        current_player.throwYut(yut); 

                        hasOtherPlayerPiece = true;
                        break;
                    }
                }

                // 다른 플레이어의 말이 있으면 그 말을 잡고, 없으면 그냥 말을 이동합니다.
                current_player.movePiece(position, solution_position);
                current_player.updateArrivedPieceNum();// 도착한 말의 개수를 업데이트합니다.


                // pieces vector의 순서를 오름차순으로 나열하는 용도로(?) 활용함
                current_player.sortPieces();
            }
        // 딱 누군가가 이겼을 경우에 (만약 player0이 딱 다 들어가서 이겼는데 player1이 또 던지지 않고 게임을 끝내야 하므로)
        if (current_player.getArrivedPieceNum() == num_pieces) {
            break;
        }
        
        }
    }

    // 승자를 확인.
    for (int i = 0; i < players.size(); ++i) {
        if (players[i].getArrivedPieceNum() == num_pieces) {
            cout << "Player " << i << " win" << endl;
        }
    }
    /////////////////////////////////////////////////////////////////////////
    // 마지막에 게임이 끝날 경우, 모든 데이터를 초기화하여야 함.
    // board에 대하여
    board.initializeBoard();
    
    // player에 대하여
    /*
    vector<int> pieces; => 각 플레이어별로 이것은 아예 처음부터 없던 걸로 갈아버려야 함.
    int arrived_piece_num = 0; => 0으로 초기화해버림
    multiset<YutName> yut_list; => 
    */
    for (Player& player : players) {
        player.resetPlayer();
    }

    // game 데이터에 대하여
    players.clear();
    pPlayer = nullptr;
    
    /////////////////////////////////////////////////////////////////////////
}

/* printCurrentTurn function
This function is used to print the current player's turn.
The function is called when the player's turn is changed.
The function is used to print information of which player's turn, the player's
current piece positions, and the current yut result list.

(example)
Player 0 turn
Piece : 0 1 1 3
Yut : gae
*/
void Game::printCurrentTurn(int player_order) {
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    if (player_order == 0) {
        cout << "Player " << COLOR_RED << player_order << COLOR_DEFAULT
             << " turn" << endl;
    } else if (player_order == 1) {
        cout << "Player " << COLOR_BLUE << player_order << COLOR_DEFAULT
             << " turn" << endl;
    } else if (player_order == 2) {
        cout << "Player " << COLOR_GREEN << player_order << COLOR_DEFAULT
             << " turn" << endl;
    } else if (player_order == 3) {
        cout << "Player " << COLOR_YELLOW << player_order << COLOR_DEFAULT
             << " turn" << endl;
    } else {
        cout << "Player " << player_order << " turn" << endl;
    }


    cout << "Piece : ";
    if (player_order >= 0 && player_order < players.size()) {
        // 선택된 플레이어의 말 위치를 가져옵니다.
        vector<int> playerPieces = players[player_order].getPieces();

        // 말의 위치가 0 이상 29 이하인 경우에만 남깁니다.
        playerPieces.erase(std::remove_if(playerPieces.begin(), playerPieces.end(),
                                        [](int pos) { return pos < 0 || pos > 29; }),
                            playerPieces.end());

        // 말의 위치를 오름차순으로 정렬합니다.
        std::sort(playerPieces.begin(), playerPieces.end());

        // 말의 위치를 출력합니다.
        for (int pos : playerPieces) {
            cout << pos << ' ';
        }
    }

    cout << '\n';
    

    // Yut list를 출력하기 위하여 현재 플레이어의 자기 차례에서의 Yut list를 가져옵니다.

    cout << "Yut : ";
    // 가능한 Yut list를 출력, 순서대로 잘 나옴.
    if (player_order >= 0 && player_order < players.size()) {
        const multiset<YutName>& yut_list = players[player_order].getYutList();
        for (const YutName& yut : yut_list) {
            cout << yut.getName() << ' ';
        }
    }
    
    cout << '\n';
    /////////////////////////////////////////////////////////////////////////
}

/* printPieceState function
This function is used to print the state of the pieces.
The function is called when the user selects the game start.
The function is used to print the state of the pieces that are not started
and the pieces that have arrived.

(example)
-----------------------------------------
Not started:
 □  □  □  □  □  □  □  □  □  □  □  □
Arrived:
 ■  ■
-----------------------------------------

/* printPieceState function
This function is used to print the state of the pieces.
The function is called when the user selects the game start.
The function is used to print the state of the pieces that are not started
and the pieces that have arrived.

(example)
-----------------------------------------
Not started : 
 □  □  □  □  □  □  □  □  □  □  □  □ 
Arrived : 
 ■  ■ 
-----------------------------------------


즉, 수정된 내용은 다음과 같습니다. (The modifications are as follows)

Not started(whitespace):(whitespace)

Arrived(whitespace):(whitespace)

piecestate

cout << (whitespace)□(whitespace)(whitespace)□(whitespace)(whitespace)□(whitespace) <<endl;

cout << (whitespace)■(whitespace)(whitespace)■(whitespace) <<endl;

*/
void Game::printPieceState() {
    cout << "-----------------------------------------" << endl;
    cout << "Not started : ";
    cout << endl;
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    for (int i = 0; i < players.size(); ++i) {
        const Player& player = players[i];
        int piecesAtPositionZero = std::count(player.getPieces().begin(), player.getPieces().end(), 0);
        string color;
        if (i == 0) {
            color = COLOR_RED;
        } else if (i == 1) {
            color = COLOR_BLUE;
        } else if (i == 2) {
            color = COLOR_GREEN;
        } else if (i == 3) {
            color = COLOR_YELLOW;
        }
        for (int j = 0; j < piecesAtPositionZero; ++j) {
            cout << color << " □ " << COLOR_DEFAULT;
        }

    }
    cout << '\n';
    /////////////////////////////////////////////////////////////////////////
    cout << "Arrived : " << endl;
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    for (int i = 0; i < players.size(); ++i) {
        const Player& player = players[i];
        int arrivedPieces = player.getArrivedPieceNum();
        string color;
        if (i == 0) {
            color = COLOR_RED;
        } else if (i == 1) {
            color = COLOR_BLUE;
        } else if (i == 2) {
            color = COLOR_GREEN;
        } else if (i == 3) {
            color = COLOR_YELLOW;
        }
        for (int j = 0; j < arrivedPieces; ++j) {
            cout << color << " ■ " << COLOR_DEFAULT;
        }
    }
    cout << '\n';
    /////////////////////////////////////////////////////////////////////////
    cout << "-----------------------------------------" << endl;
}

//fillPlayerToBoard function
void Game::fillPlayerToBoard(Board& board) {
    // player_to_board 를 초기화
    board.initializeBoard();

    // 각 플레이어의 말의 위치를 순회하고 board 클래스에 있는 변수 player_to_board를 수정해줌.
    for (int i = 0; i < players.size(); i++) {
        for (const int& pos : players[i].getPieces()) {
            // player_to_board에 대한 참조를 한 번만 가져옵니다.
            auto& player_to_board = board.getPlayerToBoard();

            if (pos > 0 && pos < board.getBoardMapping().size()) {
                int_pair mapped_pos = board.getBoardMapping()[pos];
                int row = mapped_pos.first;
                int col = mapped_pos.second;

                // 지금 상황이
                // -1,0 인 상황에 대해서도 지금 mapping이 되어버리니까 문제인 것.
                // 따라서 걸러주면 된다. player_to_board 범위가 row col 0 ~ 10 인것만 mapping되게
                // 걸러준다. 

                if (row >= 0 && row < player_to_board.size() && col >= 0 && col < player_to_board[row].size()) {
                    // player_to_board 업데이트
                    if (player_to_board[row][col].first == -1) {
                        // 이 위치에 플레이어의 말이 없는 경우
                        player_to_board[row][col] = {i, 1};
                    } else {
                        // 이 위치에 이미 플레이어의 말이 있는 경우
                        player_to_board[row][col].second++;
                    }
                }
            }
            if (pos == 100) {
                // 이것은 (-1, 0) 으로 둔다.
                continue;           
                
            }
        }
    }
}

bool Game::isGameEnd() {
    for (int i = 0; i < players.size(); ++i) {
        if (players[i].getArrivedPieceNum() == players[i].getPieces().size()) {
            return true;
        }
    }
    return false;
}