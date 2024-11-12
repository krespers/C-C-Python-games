#include "player.hpp"
#include "yut.hpp"
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

/*
- player throws yut using Yut class
(Yut class declares Player class as a friend class)
- The results of the thrown yut should be insert into multiset<YutName>
yut_list;
- If the result is yut or mo, the player should throw one more time.
  (ex1) yut yut geol
  (ex2) mo gae
  (ex3) gae
  (ex4) do
  (ex5) mo yut back-do
*/
void Player::throwYut(Yut &yut) {
    string yuts = yut.throwFourYuts();
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    yut_list.insert(YutName{yuts});
    do {
        if (yuts == "yut" || yuts == "mo") {
            yuts = yut.throwFourYuts();
            yut_list.insert(YutName{yuts});
        } else {
            break;
        }
    } while (1);
    // 윷 결과를 multiset에 추가
    // "윷" 또는 "모"가 나오면 계속 윷을 던짐
    //////////////////////////////////////////////////////////////////////
}

/*
- A function that moves the player's piece based on the yut result.
- The results of the position should be updated in a (vector<int> piece) and an
(int arrived_piece_num).

- Input
    - pos: current position of the player's piece
    - yut: yut result (back-do, do, gae, geol, yut, and mo)
- Output
    - return value: the final position of the player's piece
*/



int Player::movePlayer(int pos, string yut) {
    //////////////////IMPLEMENT HERE//////////////////////////////////////

   // yut와 move에 대하여 분류
    int move;
    if (yut == "do") {
        move = 1;
    } else if (yut == "gae") {
        move = 2;
    } else if (yut == "geol") {
        move = 3;
    } else if (yut == "yut") {
        move = 4;
    } else if (yut == "mo") {
        move = 5;
    } else if (yut == "back-do") {
        move = -1;
    }

    int pos_result = 0;

    // pos 별로 이동을 분류...
    // 특수한 동물의 경우 특정 코스로 이동하므로 그에 대응하여 추후에 추가.
    if (pos == 0) {
        if (move == -1) {
            pos_result = 0;
        } else if  (move == 1) {
            pos_result = 1;
        } else if (move == 2) {
            pos_result = 2;
        } else if (move == 3) {
            pos_result = 3;
        } else if (move == 4) {
            pos_result = 4;
        } else if (move == 5) {
            pos_result = 5;
        }
    } else if (pos == 1) {
        if (move == -1) {
            pos_result = 29;
        } else if (move == 1) {
            pos_result = 2;
        } else if (move == 2) {
            pos_result = 3;
        } else if (move == 3) {
            pos_result = 4;
        } else if (move == 4) {
            pos_result = 5;
        } else if (move == 5) {
            pos_result = 6;
        }
    } else if (pos == 2) {
        if (move == -1) {
            pos_result = 1;
        } else if (move == 1) {
            pos_result = 3;
        } else if (move == 2) {
            pos_result = 4;
        } else if (move == 3) {
            pos_result = 5;
        } else if (move == 4) {
            pos_result = 6;
        } else if (move == 5) {
            pos_result = 7;
        
        }
    } else if (pos == 3) {
        if (move == -1) {
            pos_result = 2;
        } else if (move == 1) {
            pos_result = 4;
        } else if (move == 2) {
            pos_result = 5;
        } else if (move == 3) {
            pos_result = 6;
        } else if (move == 4) {
            pos_result = 7;
        } else if (move == 5) {
            pos_result = 8;
        }
    } else if (pos == 4) {
        if (move == -1) {
            pos_result = 3;
        } else if (move == 1) {
            pos_result = 5;
        } else if (move == 2) {
            pos_result = 6;
        } else if (move == 3) {
            pos_result = 7;
        } else if (move == 4) {
            pos_result = 8;
        } else if (move == 5) {
            pos_result = 9;
        }
    }
     else if (pos == 5) {
        if (move == -1) {
            pos_result = 4;
        } else if (move == 1) {
            pos_result = 20;
        } else if (move == 2) {
            pos_result = 21;
        } else if (move == 3) {
            pos_result = 22;
        } else if (move == 4) {
            pos_result = 23;
        } else if (move == 5) {
            pos_result = 24;
        }
    } else if (pos == 6) {
        if (move == -1) {
            pos_result = 5;
        } else if (move == 1) {
            pos_result = 7;
        } else if (move == 2) {
            pos_result = 8;
        } else if (move == 3) {
            pos_result = 9;
        } else if (move == 4) {
            pos_result = 10;
        } else if (move == 5) {
            pos_result = 11;
        }
    } else if (pos == 7) {
        if (move == -1) {
            pos_result = 6;
        } else if (move == 1) {
            pos_result = 8;
        } else if (move == 2) {
            pos_result = 9;
        } else if (move == 3) {
            pos_result = 10;
        } else if (move == 4) {
            pos_result = 11;
        } else if (move == 5) {
            pos_result = 12;
        }
    } else if (pos == 8) {
        if (move == -1) {
            pos_result = 7;
        } else if (move == 1) {
            pos_result = 9;
        } else if (move == 2) {
            pos_result = 10;
        } else if (move == 3) {
            pos_result = 11;
        } else if (move == 4) {
            pos_result = 12;
        } else if (move == 5) {
            pos_result = 13;
        }
    } else if (pos == 9) {
        if (move == -1) {
            pos_result = 8;
        } else if (move == 1) {
            pos_result = 10;
        } else if (move == 2) {
            pos_result = 11;
        } else if (move == 3) {
            pos_result = 12;
        } else if (move == 4) {
            pos_result = 13;
        } else if (move == 5) {
            pos_result = 14;
        }
    } else if (pos == 10) {
        if (move == -1) {
            pos_result = 9;
        } else if (move == 1) {
            pos_result = 25;
        } else if (move == 2) {
            pos_result = 26;
        } else if (move == 3) {
            pos_result = 22;
        } else if (move == 4) {
            pos_result = 27;
        } else if (move == 5) {
            pos_result = 28;
        }
    } else if (pos == 11) {
        if (move == -1) {
            pos_result = 10;
        } else if (move == 1) {
            pos_result = 12;
        } else if (move == 2) {
            pos_result = 13;
        } else if (move == 3) {
            pos_result = 14;
        } else if (move == 4) {
            pos_result = 15;
        } else if (move == 5) {
            pos_result = 16;
        }
    } else if (pos == 12) {
        if (move == -1) {
            pos_result = 11;
        } else if (move == 1) {
            pos_result = 13;
        } else if (move == 2) {
            pos_result = 14;
        } else if (move == 3) {
            pos_result = 15;
        } else if (move == 4) {
            pos_result = 16;
        } else if (move == 5) {
            pos_result = 17;
        }
    } else if (pos == 13) {
        if (move == -1) {
            pos_result = 12;
        } else if (move == 1) {
            pos_result = 14;
        } else if (move == 2) {
            pos_result = 15;
        } else if (move == 3) {
            pos_result = 16;
        } else if (move == 4) {
            pos_result = 17;
        } else if (move == 5) {
            pos_result = 18;
        }
    } else if (pos == 14) {
        if (move == -1) {
            pos_result = 13;
        } else if (move == 1) {
            pos_result = 15;
        } else if (move == 2) {
            pos_result = 16;
        } else if (move == 3) {
            pos_result = 17;
        } else if (move == 4) {
            pos_result = 18;
        } else if (move == 5) {
            pos_result = 19;
        }
    } else if (pos == 15) {
        if (move == -1) {
            pos_result = 14;
        } else if (move == 1) {
            pos_result = 16;
        } else if (move == 2) {
            pos_result = 17;
        } else if (move == 3) {
            pos_result = 18;
        } else if (move == 4) {
            pos_result = 19;
        } else if (move == 5) {
            pos_result = 29;
        }
    } else if (pos == 16) {
        if (move == -1) {
            pos_result = 15;
        } else if (move == 1) {
            pos_result = 17;
        } else if (move == 2) {
            pos_result = 18;
        } else if (move == 3) {
            pos_result = 19;
        } else if (move == 4) {
            pos_result = 29;
        } else if (move == 5) {
            pos_result = 100;
        }
    } else if (pos == 17) {
        if (move == -1) {
            pos_result = 16;
        } else if (move == 1) {
            pos_result = 18;
        } else if (move == 2) {
            pos_result = 19;
        } else if (move == 3) {
            pos_result = 29;
        } else if (move == 4) {
            pos_result = 100;
        } else if (move == 5) {
            pos_result = 100;
        }
    } else if (pos == 18) {
        if (move == -1) {
            pos_result = 17;
        } else if (move == 1) {
            pos_result = 19;
        } else if (move == 2) {
            pos_result = 29;
        } else if (move == 3) {
            pos_result = 100;
        } else if (move == 4) {
            pos_result = 100;
        } else if (move == 5) {
            pos_result = 100;
        }
    } else if (pos == 19) {
        if (move == -1) {
            pos_result = 18;
        } else if (move == 1) {
            pos_result = 29;
        } else if (move == 2) {
            pos_result = 100;
        } else if (move == 3) {
            pos_result = 100;
        } else if (move == 4) {
            pos_result = 100;
        } else if (move == 5) {
            pos_result = 100;
        }
    } else if (pos == 20) {
        if (move == -1) {
            pos_result = 5;
        } else if (move == 1) {
            pos_result = 21;
        } else if (move == 2) {
            pos_result = 22;
        } else if (move == 3) {
            pos_result = 23;
        } else if (move == 4) {
            pos_result = 24;
        } else if (move == 5) {
            pos_result = 15;
        }
    } else if (pos == 21) {
        if (move == -1) {
            pos_result = 20;
        } else if (move == 1) {
            pos_result = 22;
        } else if (move == 2) {
            pos_result = 23;
        } else if (move == 3) {
            pos_result = 24;
        } else if (move == 4) {
            pos_result = 15;
        } else if (move == 5) {
            pos_result = 16;
        }
    } else if (pos == 22) {
        if (move == -1) {
            pos_result = 21;
        } else if (move == 1) {
            pos_result = 27;
        } else if (move == 2) {
            pos_result = 28;
        } else if (move == 3) {
            pos_result = 29;
        } else {
            pos_result = 100;
        }
    } else if (pos == 23) {
        if (move == -1) {
            pos_result = 22;
        } else if (move == 1) {
            pos_result = 24;
        } else if (move == 2) {
            pos_result = 15;
        } else if (move == 3) {
            pos_result = 16;
        } else if (move == 4) {
            pos_result = 17;
        } else if (move == 5) {
            pos_result = 18;
        }
    } else if (pos == 24) {
        if (move == -1) {
            pos_result = 23;
        } else if (move == 1) {
            pos_result = 15;
        } else if (move == 2) {
            pos_result = 16;
        } else if (move == 3) {
            pos_result = 17;
        } else if (move == 4) {
            pos_result = 18;
        } else if (move == 5) {
            pos_result = 19;
        }
    } else if (pos == 25) {
        if (move == -1) {
            pos_result = 10;
        } else if (move == 1) {
            pos_result = 26;
        } else if (move == 2) {
            pos_result = 22;
        } else if (move == 3) {
            pos_result = 27;
        } else if (move == 4) {
            pos_result = 28;
        } else if (move == 5) {
            pos_result = 29;
        }
    } else if (pos == 26) {
        if (move == -1) {
            pos_result = 25;
        } else if (move == 1) {
            pos_result = 22;
        } else if (move == 2) {
            pos_result = 27;
        } else if (move == 3) {
            pos_result = 28;
        } else if (move == 4) {
            pos_result = 29;
        } else if (move == 5) {
            pos_result = 100;
        }
    } else if (pos == 27) {
        if (move == -1) {
            pos_result = 22;
        } else if (move == 1) {
            pos_result = 28;
        } else if (move == 2) {
            pos_result = 29;
        } else if (move == 3) {
            pos_result = 100;
        } else if (move == 4) {
            pos_result = 100;
        } else if (move == 5) {
            pos_result = 100;
        }
    } else if (pos == 28) {
        if (move == -1) {
            pos_result = 27;
        } else if (move == 1) {
            pos_result = 29;
        } else {
            pos_result = 100;
        }
    } else if (pos == 29) {
        if (move == -1) {
            pos_result = 19;
        } else {
            pos_result = 100;
        }
        

    
    //////////////////////////////////////////////////////////////////////
    }
    return pos_result;
}


// 말을 움직이는 함수
// 현재 위치와 다음 위치를 받아서 현재 위치에 해당하는 말을 다음 위치로 옮김
// 대신, current_pos가 0, 0, 0, 0인 경우에 movePiece(0,1)을 받으면 1,1,1,1 이 되는게 아니고 0,0,0,1이 됨
// 그리고 current_pos가 1~29 사이에 있으며 동일한 위치에 두 개 이상의 말이 있는 경우에는 그 말들을 한꺼번에 옮김
// 입력한 것이 한 개만 움직여야 되는데 지금 2개가 움직이고 있음.

void Player::movePiece(int current_pos, int next_pos) {
    // pieces 벡터의 원소를 출력합니다.
    //std::cout << "Before moving: ";
    //for (const int& piece : pieces) {
    //    std::cout << piece << ' ';
    //}
    //std::cout << '\n';

    if (current_pos >= 1 && current_pos <= 29) {
        for (int& piece : pieces) {
            if (piece == current_pos) {
                piece = next_pos;
            }
        }
    } else if (current_pos == 0) {
        bool moved = false;
        for (int& piece : pieces) {
            if (piece == 0) {
                piece = next_pos;
                moved = true;
                break;  // 첫 번째로 발견된 말을 움직이고 for문을 종료합니다.
            }
        }
        if (moved) {
            return;  // 말을 움직였다면 함수를 종료합니다.
        }
    }

    // 말을 움직인 후의 pieces 벡터의 원소를 출력합니다.
    // std::cout << "After moving: ";
    // for (const int& piece : pieces) {
    //    std::cout << piece << ' ';
    // }
    // std::cout << '\n';
}

bool Player::hasPieceAt(int pos) const {
    if (pos == 100) {
        return false;
    }
    for (int piece : pieces) {
        if (piece == pos) {
            return true;
        }
    }
    return false;
}


void Player::sendPieceToStart(int pos) {
    if (pos == 100) {
        return;
    }
    for (int& piece : pieces) {
        if (piece == pos) {
            piece = 0;
        }
    }
}


void Player::resetPlayer() {
    pieces.clear();
    arrived_piece_num = 0;
    yut_list.clear();
}





////////////////////////////////////////////////////////////
    // pig
    // If someone else (player A) catches you, A ends his turn immediately. sheep 보다 pig가 더 셈.
    

    
    // dog
    // Even if the stick result is geol (하나의 geol), you should throw again
    

    // sheep
    // If you catch someone else, you have two chances to throw again.







    // cow 기술 : You can only move along the specific path
    // cow는 0,1,2,3,4,5,20,21,22,23,24,15,16,17,18,19,29,100의 루트로만 이동함
int AnimalPlayer::movePlayerCow(int pos, string yut) {
    
   // yut와 move에 대하여 분류
    int move;
    if (yut == "do") {
        move = 1;
    } else if (yut == "gae") {
        move = 2;
    } else if (yut == "geol") {
        move = 3;
    } else if (yut == "yut") {
        move = 4;
    } else if (yut == "mo") {
        move = 5;
    } else if (yut == "back-do") {
        move = -1;
    }
    int pos_result = 0;

    // pos 별로 이동을 분류...
    // 특수한 동물의 경우 특정 코스로 이동하므로 그에 대응하여 추후에 추가.
    if (pos == 0) {
        if (move == -1) {
            pos_result = 0;
        } else if  (move == 1) {
            pos_result = 1;
        } else if (move == 2) {
            pos_result = 2;
        } else if (move == 3) {
            pos_result = 3;
        } else if (move == 4) {
            pos_result = 4;
        } else if (move == 5) {
            pos_result = 5;
        }
    } else if (pos == 1) {
        if (move == -1) {
            pos_result = 29;
        } else if (move == 1) {
            pos_result = 2;
        } else if (move == 2) {
            pos_result = 3;
        } else if (move == 3) {
            pos_result = 4;
        } else if (move == 4) {
            pos_result = 5;
        } else if (move == 5) {
            pos_result = 20;
        }
    } else if (pos == 2) {
        if (move == -1) {
            pos_result = 1;
        } else if (move == 1) {
            pos_result = 3;
        } else if (move == 2) {
            pos_result = 4;
        } else if (move == 3) {
            pos_result = 5;
        } else if (move == 4) {
            pos_result = 20;
        } else if (move == 5) {
            pos_result = 21;
        
        }
    } else if (pos == 3) {
        if (move == -1) {
            pos_result = 2;
        } else if (move == 1) {
            pos_result = 4;
        } else if (move == 2) {
            pos_result = 5;
        } else if (move == 3) {
            pos_result = 20;
        } else if (move == 4) {
            pos_result = 21;
        } else if (move == 5) {
            pos_result = 22;
        }
    } else if (pos == 4) {
        if (move == -1) {
            pos_result = 3;
        } else if (move == 1) {
            pos_result = 5;
        } else if (move == 2) {
            pos_result = 20;
        } else if (move == 3) {
            pos_result = 21;
        } else if (move == 4) {
            pos_result = 22;
        } else if (move == 5) {
            pos_result = 23;
        }
    }
     else if (pos == 5) {
        if (move == -1) {
            pos_result = 4;
        } else if (move == 1) {
            pos_result = 20;
        } else if (move == 2) {
            pos_result = 21;
        } else if (move == 3) {
            pos_result = 22;
        } else if (move == 4) {
            pos_result = 23;
        } else if (move == 5) {
            pos_result = 24;
        }
    } else if (pos == 15) {
        if (move == -1) {
            pos_result = 24;
        } else if (move == 1) {
            pos_result = 16;
        } else if (move == 2) {
            pos_result = 17;
        } else if (move == 3) {
            pos_result = 18;
        } else if (move == 4) {
            pos_result = 19;
        } else if (move == 5) {
            pos_result = 29;
        }
    } else if (pos == 16) {
        if (move == -1) {
            pos_result = 15;
        } else if (move == 1) {
            pos_result = 17;
        } else if (move == 2) {
            pos_result = 18;
        } else if (move == 3) {
            pos_result = 19;
        } else if (move == 4) {
            pos_result = 29;
        } else if (move == 5) {
            pos_result = 100;
        }
    } else if (pos == 17) {
        if (move == -1) {
            pos_result = 16;
        } else if (move == 1) {
            pos_result = 18;
        } else if (move == 2) {
            pos_result = 19;
        } else if (move == 3) {
            pos_result = 29;
        } else if (move == 4) {
            pos_result = 100;
        } else if (move == 5) {
            pos_result = 100;
        }
    } else if (pos == 18) {
        if (move == -1) {
            pos_result = 17;
        } else if (move == 1) {
            pos_result = 19;
        } else if (move == 2) {
            pos_result = 29;
        } else if (move == 3) {
            pos_result = 100;
        } else if (move == 4) {
            pos_result = 100;
        } else if (move == 5) {
            pos_result = 100;
        }
    } else if (pos == 19) {
        if (move == -1) {
            pos_result = 18;
        } else if (move == 1) {
            pos_result = 29;
        } else if (move == 2) {
            pos_result = 100;
        } else if (move == 3) {
            pos_result = 100;
        } else if (move == 4) {
            pos_result = 100;
        } else if (move == 5) {
            pos_result = 100;
        }
    } else if (pos == 20) {
        if (move == -1) {
            pos_result = 5;
        } else if (move == 1) {
            pos_result = 21;
        } else if (move == 2) {
            pos_result = 22;
        } else if (move == 3) {
            pos_result = 23;
        } else if (move == 4) {
            pos_result = 24;
        } else if (move == 5) {
            pos_result = 15;
        }
    } else if (pos == 21) {
        if (move == -1) {
            pos_result = 20;
        } else if (move == 1) {
            pos_result = 22;
        } else if (move == 2) {
            pos_result = 23;
        } else if (move == 3) {
            pos_result = 24;
        } else if (move == 4) {
            pos_result = 15;
        } else if (move == 5) {
            pos_result = 16;
        }
    } else if (pos == 22) {
        if (move == -1) {
            pos_result = 21;
        } else if (move == 1) {
            pos_result = 23;
        } else if (move == 2) {
            pos_result = 24;
        } else if (move == 3) {
            pos_result = 15;
        } else if (move == 4) {
            pos_result = 16;
        } else if (move == 5) {
            pos_result = 17;
        }
    } else if (pos == 23) {
        if (move == -1) {
            pos_result = 22;
        } else if (move == 1) {
            pos_result = 24;
        } else if (move == 2) {
            pos_result = 15;
        } else if (move == 3) {
            pos_result = 16;
        } else if (move == 4) {
            pos_result = 17;
        } else if (move == 5) {
            pos_result = 18;
        }
    } else if (pos == 24) {
        if (move == -1) {
            pos_result = 23;
        } else if (move == 1) {
            pos_result = 15;
        } else if (move == 2) {
            pos_result = 16;
        } else if (move == 3) {
            pos_result = 17;
        } else if (move == 4) {
            pos_result = 18;
        } else if (move == 5) {
            pos_result = 19;
        }
    } else if (pos == 29) {
        if (move == -1) {
            pos_result = 19;
        } else {
            pos_result = 100;
        }  
    //////////////////////////////////////////////////////////////////////
    }
    return pos_result;
}



void AnimalPlayer::throwYutDog(Yut &yut) {
    string yuts = yut.throwFourYuts();
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    yut_list.insert(YutName{yuts});
    do {
        if (yuts == "geol" || yuts == "yut" || yuts == "mo") {
            yuts = yut.throwFourYuts();
            yut_list.insert(YutName{yuts});
        } else {
            break;
        }
    } while (1);
    // 윷 결과를 multiset에 추가
    // "윷" 또는 "모"가 나오면 계속 윷을 던짐
    //////////////////////////////////////////////////////////////////////
}

void AnimalPlayer::resetAnimalPlayer() {
    pieces.clear();
    arrived_piece_num = 0;
    yut_list.clear();
    name = "";
    animal_type = 0;
}