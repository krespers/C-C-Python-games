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
    // �ʿ�� �ۼ�...
    // menuSelect�� �ϰ� 
    // game start�� ������ run �Լ��� ����

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
            // i == 1�� ������ ��쿡,
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

    // ���ӿ� �ʿ��� player ����ŭ �����ϰ�, �� �÷��̾�� ���� ������ �����մϴ�.
    //vector<Player> players;

    for (int i = 0; i < num_players; ++i) {
        players.push_back(Player(num_pieces));
    }
    
    //���� ������ ��ġ�� ���(?)
    /*
    for (int i = 0; i < num_players; ++i) {
        const vector<int>& playerPieces = players[i].getPieces();
        cout << "Player " << i+1 << " has " << playerPieces.size() << " pieces.\n";
        for (int j = 0; j < playerPieces.size(); ++j) {
            cout << "Piece " << j+1 << " is at position " << playerPieces[j] << ".\n";
        }
    }
    */

   // ���带 ����.
    Board board;
    board.initializeBoard();

    // �÷��̾� 0,1,2,3 (2,3�� ���� players.size() ũ�⿡ ���� ���������� ���ư��鼭 ����.)
    // �÷��̾ ���� �ϴ� ����
    // ������ ���� board.printBoard(); printPieceState(); 

    // bool is_game_end()


    // �ϴ� �������� ���� piece�� �� ������ ���ƿ��� �׶��� ������ ������.
    // �׸��� ������ ������ ������ �ٽ� ���۵ȴ�!
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


    // �ٵ� ������ ������ ������ �ʴ� ��Ȳ�̴�. ���� ���� �ʿ�

    /*
     ���� ������ ��Ȳ (�̱� ��� ���, �������� �̱�� ���� ����,
     ������ ������ ���� �ٽ� �޴��� ���ư���) / 
     �������κ��� ����� ��쿡 ���� 2���� �̵��ϴ� ���� �߰�
     ���� yut �Լ��� ó���� �鵵 �� player0�� player1�� ������ �ϴµ� player0�� �Ǵٽ� ������ �̻�(?) ���� �߰�
    */




    while (!isGameEnd()) {
        for (int i = 0; i < players.size(); ++i) {



            // i��° �÷��̾ �ϴ��� �ڱ� ���� �����ϱ� ó����, ���� �����ϴ�.
            Player &current_player = players[i];
            current_player.throwYut(yut);

            // players[i]�� yut_list�� �� ����� �������� Ȥ�� �ڱⰡ ��� pieces�� ��ġ�� ����(100)���� ������ ������
            // �ڽ��� ���� ������ �ʽ��ϴ�
            while (!current_player.isYutListEmpty()) {      

                // �ϴ� �ڱⰡ ���� �ִ� ���� üũ�� ���¿��� ������ ������ �ʾҴٸ� �Ʒ��� ������.
                if(current_player.getArrivedPieceNum() == num_pieces) {
                    break;
                }

                fillPlayerToBoard(board); //���ӿ� �������� "��� �÷��̾�"�� �� ��ġ�� ���忡 ä���� �մϴ�.
                board.printBoard(); // ���� ���� ���¸� ��� 
                // board.printPlayerToBoard(); // ����� Ȯ�ο� �ڵ� �ڵ�
                printPieceState(); // ���� ���¸� ����մϴ�.
                printCurrentTurn(i); // ���� �÷��̾��� ���� ����մϴ�.

                // �÷��̾��� �Է��� �޽��ϴ�.
                cout << "Write down the position of the player to move and yut" << endl;
                cout << "(back-do, do, gae, geol, yut, and mo)" << endl;
                cout << ">> position : ";
                int position;
                cin >> position;
                cout << ">> yut : ";
                string input_yut;
                cin >> input_yut;
                current_player.removeYut(input_yut); // ����� yut�� yut_list���� ����

                // �̵� ���� �����̰�, �� player�� yut list�� �ִ� �� �߿� �Է��� �Ͱ� ��ġ�ϴ� ���� ����
                // ���� movePlayer�� ���� ��, �� player�� ��� piece 0 position�� ���� ���
                // ������ �ϳ��� piece���� �ű�ϴ�. ���� ��ġ�� 1~29�� �ִ� ��� �̵��� �ؾ� �մϴ�.
                // �� �Լ��� Ư�� position�� �ִ� ���� �Էµ� yut ��ŭ �̵��Ͽ��� ��, ��� ��ġ�� �������� ��ȯ�մϴ�.

                int solution_position = current_player.movePlayer(position, input_yut);
                // ���࿡ ���� ����� solution_position ��ġ�� 0�̶��, �̵��� �� �ִ� ��ġ�� ���ٴ� ���̹Ƿ� ��

                if (solution_position == 0) {
                    continue;
                }

                

                // Ž���ϴ� �Լ� ���� ����� solution_position�� �ٸ� �÷��̾��� ���� �ִ� ���
                current_player.sortPieces();
                
                // �ٸ� �÷��̾��� ���� �ִ��� Ȯ���մϴ�.
                bool hasOtherPlayerPiece = false;
                for (Player& other_player : players) {
                    if (&other_player != &current_player && other_player.hasPieceAt(solution_position)) {
                        // ���� ���� ���� ��ġ�� �����ϴ�.
                        other_player.sendPieceToStart(solution_position);  

                        // ���� �� �� �� ������ �� ����Ʈ�� �߰��մϴ�.
                        current_player.throwYut(yut); 

                        hasOtherPlayerPiece = true;
                        break;
                    }
                }

                // �ٸ� �÷��̾��� ���� ������ �� ���� ���, ������ �׳� ���� �̵��մϴ�.
                current_player.movePiece(position, solution_position);
                current_player.updateArrivedPieceNum();// ������ ���� ������ ������Ʈ�մϴ�.


                // pieces vector�� ������ ������������ �����ϴ� �뵵��(?) Ȱ����
                current_player.sortPieces();
            }
        // �� �������� �̰��� ��쿡 (���� player0�� �� �� ���� �̰�µ� player1�� �� ������ �ʰ� ������ ������ �ϹǷ�)
        if (current_player.getArrivedPieceNum() == num_pieces) {
            break;
        }
        
        }
    }

    // ���ڸ� Ȯ��.
    for (int i = 0; i < players.size(); ++i) {
        if (players[i].getArrivedPieceNum() == num_pieces) {
            cout << "Player " << i << " win" << endl;
        }
    }
    /////////////////////////////////////////////////////////////////////////
    // �������� ������ ���� ���, ��� �����͸� �ʱ�ȭ�Ͽ��� ��.
    // board�� ���Ͽ�
    board.initializeBoard();
    
    // player�� ���Ͽ�
    /*
    vector<int> pieces; => �� �÷��̾�� �̰��� �ƿ� ó������ ���� �ɷ� ���ƹ����� ��.
    int arrived_piece_num = 0; => 0���� �ʱ�ȭ�ع���
    multiset<YutName> yut_list; => 
    */
    for (Player& player : players) {
        player.resetPlayer();
    }

    // game �����Ϳ� ���Ͽ�
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
        // ���õ� �÷��̾��� �� ��ġ�� �����ɴϴ�.
        vector<int> playerPieces = players[player_order].getPieces();

        // ���� ��ġ�� 0 �̻� 29 ������ ��쿡�� ����ϴ�.
        playerPieces.erase(std::remove_if(playerPieces.begin(), playerPieces.end(),
                                        [](int pos) { return pos < 0 || pos > 29; }),
                            playerPieces.end());

        // ���� ��ġ�� ������������ �����մϴ�.
        std::sort(playerPieces.begin(), playerPieces.end());

        // ���� ��ġ�� ����մϴ�.
        for (int pos : playerPieces) {
            cout << pos << ' ';
        }
    }

    cout << '\n';
    

    // Yut list�� ����ϱ� ���Ͽ� ���� �÷��̾��� �ڱ� ���ʿ����� Yut list�� �����ɴϴ�.

    cout << "Yut : ";
    // ������ Yut list�� ���, ������� �� ����.
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
 ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��
Arrived:
 ��  ��
-----------------------------------------

/* printPieceState function
This function is used to print the state of the pieces.
The function is called when the user selects the game start.
The function is used to print the state of the pieces that are not started
and the pieces that have arrived.

(example)
-----------------------------------------
Not started : 
 ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  ��  �� 
Arrived : 
 ��  �� 
-----------------------------------------


��, ������ ������ ������ �����ϴ�. (The modifications are as follows)

Not started(whitespace):(whitespace)

Arrived(whitespace):(whitespace)

piecestate

cout << (whitespace)��(whitespace)(whitespace)��(whitespace)(whitespace)��(whitespace) <<endl;

cout << (whitespace)��(whitespace)(whitespace)��(whitespace) <<endl;

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
            cout << color << " �� " << COLOR_DEFAULT;
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
            cout << color << " �� " << COLOR_DEFAULT;
        }
    }
    cout << '\n';
    /////////////////////////////////////////////////////////////////////////
    cout << "-----------------------------------------" << endl;
}

//fillPlayerToBoard function
void Game::fillPlayerToBoard(Board& board) {
    // player_to_board �� �ʱ�ȭ
    board.initializeBoard();

    // �� �÷��̾��� ���� ��ġ�� ��ȸ�ϰ� board Ŭ������ �ִ� ���� player_to_board�� ��������.
    for (int i = 0; i < players.size(); i++) {
        for (const int& pos : players[i].getPieces()) {
            // player_to_board�� ���� ������ �� ���� �����ɴϴ�.
            auto& player_to_board = board.getPlayerToBoard();

            if (pos > 0 && pos < board.getBoardMapping().size()) {
                int_pair mapped_pos = board.getBoardMapping()[pos];
                int row = mapped_pos.first;
                int col = mapped_pos.second;

                // ���� ��Ȳ��
                // -1,0 �� ��Ȳ�� ���ؼ��� ���� mapping�� �Ǿ�����ϱ� ������ ��.
                // ���� �ɷ��ָ� �ȴ�. player_to_board ������ row col 0 ~ 10 �ΰ͸� mapping�ǰ�
                // �ɷ��ش�. 

                if (row >= 0 && row < player_to_board.size() && col >= 0 && col < player_to_board[row].size()) {
                    // player_to_board ������Ʈ
                    if (player_to_board[row][col].first == -1) {
                        // �� ��ġ�� �÷��̾��� ���� ���� ���
                        player_to_board[row][col] = {i, 1};
                    } else {
                        // �� ��ġ�� �̹� �÷��̾��� ���� �ִ� ���
                        player_to_board[row][col].second++;
                    }
                }
            }
            if (pos == 100) {
                // �̰��� (-1, 0) ���� �д�.
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