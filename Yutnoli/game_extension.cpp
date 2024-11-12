#include "game.hpp"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
>> required cout statements in run function
1. cout << "ID : ";
   cout << "PASSWORD : ";
2. cout << "Login Failed!" << endl;
   cout << "Login Succeed!" << endl;
*/
void GameExtension::login() {
   //read ID PASSWORD from user_info.txt

   //read ID PASSWORD from user_info.txt
   ifstream user_info("user_info.txt");
   string line;
   while (getline(user_info, line)) {
      stringstream ss(line);
      string id, password;
      ss >> id >> password;
        // Store id and password for further use
      addUserInfo(id, password);
    }
   user_info.close();

   // input
   cout << "ID : ";
   string id;
   cin >> id;
   cout << "PASSWORD : ";
   string password;
   cin >> password;


   // check if the id and password are correct
   bool login_succeed = false;
   for (auto& info : getUserdatabase()) {
      if (info.first == id && info.second == password) {
         login_succeed = true;
         cout << "Login Succeed!" << endl;
         addLoginUserInfo(id, password);
         break;
      }
   }

   if (!login_succeed) {
      cout << "Login Failed!" << endl;
   }
}

/* menuSelect function
This function is used to choose "game start / login / end program"
The function returns 0 if the user selects the end
program, and returns 1 if the user selects the game start.

>> required cout statements in run function
1. cout << "More than 1 player is needed to start the game" << endl;
2. cout << "Logged-in ID List : ";
3. cout << "No player is logged in" << endl;
*/
int GameExtension::menuSelect() {
    int i;
    while (1) {
        cout << "************************************************************"
             << endl;
        cout << "************************   Menu   **************************"
             << endl;
        cout << "************************************************************"
             << endl;


        printLoginUserInfo();
        cout << "1. game start" << endl;
        cout << "2. login" << endl;
        cout << "3. end program" << endl;
        cout << "Select the function you want : ";
        //////////////////IMPLEMENT HERE//////////////////////////////////////
        

         cin >> i;
         if (i == 1) {
            if (getLoginUserInfo().size() < 2) {
                cout << "More than 1 player is needed to start the game" << endl;
                continue;
            }
            else {
                  run();
                  
            }
        }
        else if (i == 2) {
            login();
        }
        else if (i == 3) {
            return 0;
        }
        else {
            cout << "Invalid input" << endl;
            continue;
        }
    }
}

/*
This function is used to run the game.
The function is called when the user selects the game start.
The function is used to run the game until the game ends.

>> required cout statements in run function
1. cout << "There is a saved game. Start a new game (0) / Resume (1) : ";
2. cout << "Select animal type of " << ??? << endl;
   cout << "(0: pig, 1: dog, 2: sheep, 3:cow) : ";
3. cout << "Continue (0) / Save and Exit the game (1) : ";
4. cout << "Game saved successfully!" << endl;
5. cout << "Write down the position of the player to move and yut" << endl;
   cout << "(back-do, do, gae, geol, yut, and mo)" << endl;
   cout << ">> position : ";
   cout << ">> yut : ";
6. cout << "Player " << ??? << " win" << endl;
;*/


   // 로그인과 관련하여 데이터가 다 입력되었으니 게임을 시작합시다.
   // 게임이 시작되면 한 사람의 말이 모두 100 100 100 100이 될 때까지 계속 반복합니다.
   // 자기 턴이 끝나면 다음 플레이어로 넘어가기 전에 저장할지 안하고 끌지 물어봅니다.
   // 게임이 끝나면 승자를 출력하고 게임을 종료합니다.
   // 그리고 게임에 있던 각종 데이터를 모두 다 clear() 초기화 작업후, 다시 menuSelect()로 돌아갑니다.
   // 각 윷놀이 동물별 특성을 고려
    // pig
    // If someone else (player A) catches you, A ends his turn immediately. sheep 보다 pig가 더 셈.
    // dog
    // Even if the stick result is geol (하나의 geol), you should throw again (다시 한 번 더 던짐!)
    // sheep
    // If you catch someone else, you have two chances to throw again.
    // cow 기술 : You can only move along the specific path
    // cow는 0,1,2,3,4,5,20,21,22,23,24,15,16,17,18,19,29,100의 루트로만 이동함


void GameExtension::run() {
   //////////////////IMPLEMENT HERE/////////////////////////////////////
   ifstream game_info("game_info.txt");
   string line;
   while (getline(game_info, line)) {
      istringstream iss(line);
      string name;
      vector<string> players;
      while (iss >> name && name.find('|') == std::string::npos) { 
         // '|' 문자를 만날 때까지 이름을 읽습니다.
         players.push_back(name);
      }
      addGameSavefile_Players(players);
   }
   game_info.close();


   // 만약에 game_info.txt에 저장된 게임에 같은 플레이어 이름이 있다면
   // 그 이름을 받아올 건가 말 건가?
   //cout << "Select animal type of " << ??? << endl;

   
   if (isSameIgnoreOrder(getLoginUserInfo(), getGameSavefile_Players())) {
      cout << "There is a saved game. Start a new game (0) / Resume (1) : ";
      int i;
      while (true) {
         cin >> i;
         if (i == 1) {
               restoreGame();
               break;
         }
         if (i == 0) {
               // 동물을 선택하고 animalplayers에 저장함. 새 게임
               updatingGame_info();
               animalSelect();
               setgameturn(0); // 게임 턴을 0으로 초기화합니다.

               break;
         }
         cout << "Invalid input. Please enter 0 to start a new game or 1 to resume: " << endl;
      }
   } else {
      animalSelect();
      setgameturn(0); // 게임 턴을 0으로 초기화. 새 게임.
   }

   Board board;
   board.initializeBoard();

   // board.printPlayerToBoard(); // 디버깅 확인용 코드
   // printAnimalPlayerInfo2();  
   // 일단 제일 처음 시작하기 전에 게임 저장 물어보기

   int start = getgameturn();
   
   while (!isGameEnd()) {
      // gameturn checking.
      // i가 0이면 0부터 시작, 아니면 다른 데부터 시작할 것.
   // 2명이서 시작을 했다 치자. 그러면 0,1,0,1,0,1,0,1 이렇게 돌아가면서 게임이 진행됨.
   // getgameturn이 0이잖아. start=0
      for (int i = start; i < start + Animalplayers.size(); ++i) {
         int currentTurn = i % Animalplayers.size();

         setgameturn(currentTurn); // ???

         fillPlayerToBoard(board);
         board.printBoard();
         printAnimalPlayerInfo();
         printPieceState();
         // 백업 물어보는 코드. 0,1 입력...
         bool isbackup = backupChecker(); 
         if (isbackup) {
            // 마지막에 게임이 끝날 경우, 모든 데이터를 초기화
            // board에 대하여
            board.initializeBoard();
            // Animalplayer에 대하여
            for(auto& player : Animalplayers) {
               player.resetAnimalPlayer(); // 
            }
            // game에 대하여
            Animalplayers.clear();
            resetGameExtension();

            return;
         }

         // i번째 플레이어의 턴 시작
         // i번째 플레이어가 일단은 자기 턴이 왔으니까 처음에, 윷을 던집니다.
         AnimalPlayer &current_player = Animalplayers[currentTurn];

         if (current_player.getAnimalType() == 1) {
            current_player.throwYutDog(yut); // dog에 대해서만.
         } else {
            current_player.throwYut(yut);
         }
// animalplayers[i]의 yut_list를 다 써버릴 때까지는 혹은 자기가 모든 pieces의 위치를 도착(100) 아니면 턴 안끝남.
         
         while (!current_player.isYutListEmpty()) {      
         // 일단 자기가 갖고 있는 윷이 체크된 상태에서 게임이 끝나지 않았다면 아래를 실행함.
            if(current_player.getArrivedPieceNum() == 4) {
               break;
            }
            
            fillPlayerToBoard(board); //게임에 참여중인 "모든 플레이어"의 말 위치를 보드에 채워야 합니다.
            board.printBoard(); // 현재 보드 상태를 출력 
            // board.printPlayerToBoard(); // 디버깅 확인용 코드 코드
            printAnimalPlayerInfo();
            printPieceState(); // 말의 상태를 출력합니다.
            
            printCurrentTurn(currentTurn); // 현재 플레이어의 턴을 출력합니다.
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
         

            int solution_position;
            if (current_player.getAnimalType() == 3) {
               solution_position = current_player.movePlayerCow(position, input_yut);
            } else {
               solution_position = current_player.movePlayer(position, input_yut);
            }
            
            // 만약에 나온 결과가 solution_position 위치가 0이라면, 이동할 수 있는 위치가 없다는 것이다
            //if (solution_position == 0) {
               // i++; 
               // 이렇게 해버리면은 i가 갑자기 늘어나버리면 큰일난다.
            //   continue;
            //}

            

            // 탐색하는 함수 나온 결과에 solution_position에 다른 플레이어의 말이 있는 경우
            current_player.sortPieces();
            // pig를 잡으면 sheep 인지 아닌지도 전부 무시하고, 잡은 말이랑 잡힌 말 모두가 시작 위치로 감.
            // 그리고 pig을 잡은 녀석의 yut을 모두 초기화시켜버림.
            // sheep은 말을 잡으면 윷을 두 번 더 던져서 윷 리스트에 추가함.
                         
            // 다른플레이어의 말이 있는지 확인합니다.
            bool hasOtherPlayerPiece = false;
            bool isCatchedPlayerIsPig = false;
            
            if (solution_position != 0) {
               for (AnimalPlayer& other_player : Animalplayers) {
                  if (&other_player != &current_player && other_player.hasPieceAt(solution_position)) {
                     // 잡은 말을 시작 위치로 보냅니다.
                     other_player.sendPieceToStart(solution_position);
                     if (other_player.getAnimalType() == 0) {
                        isCatchedPlayerIsPig = true;
                     }
                     // 윷을 한 번 더 던져서 윷 리스트에 추가합니다.
                     current_player.throwYut(yut);
                     // 내가 만약에 sheep이면 윷을 한 번 더 던집니다.
                     if (current_player.getAnimalType() == 2) {
                        current_player.throwYut(yut);
                     }
                     hasOtherPlayerPiece = true;
                     break;
                  }
               }
            }


            // 다른 플레이어의 말이 있으면 그 말을 잡고, 없으면 그냥 말을 이동합니다.
            current_player.movePiece(position, solution_position);
            current_player.updateArrivedPieceNum();// 도착한 말의 개수를 업데이트합니다.
            // pieces vector의 순서를 오름차순으로 나열하는 용도로(?) 활용함
            current_player.sortPieces();

         //   cout << "solution_position : " << solution_position << endl;
         //   cout << "currentTurn : " << i << endl;            
               
            if (isCatchedPlayerIsPig) {
               current_player.resetYutList();
               break;
            }

         }

         // 딱 누군가가 이겼을 경우에 (만약 player0이 딱 다 들어가서 이겼는데 player1이 또 던지지 않고 게임을 끝내야 하므로)
         if (current_player.getArrivedPieceNum() == 4) {
            break;
         }
      }
   }

   // 게임 저장하는 걸로 while(for()) loop를 빠져나왔을 경우에는 게임이 끝났지만
   // 이거는 어차피 승자 있을 때만 출력을 하는 거니까 굳이 또 할 필요 없음. 
    // 승자를 확인.
    for (int i = 0; i < Animalplayers.size(); ++i) {
        if (Animalplayers[i].getArrivedPieceNum() == 4) {
            cout << "Player " << i << " win" << endl;
        }
    }
   /////////////////////////////////////////////////////////////////////////
   // 마지막에 게임이 끝날 경우, 모든 데이터를 초기화
   // board에 대하여
   board.initializeBoard();


   // Animalplayer에 대하여
   for(auto& player : Animalplayers) {
      player.resetAnimalPlayer(); // 
   }

   // game에 대하여
   Animalplayers.clear();
   resetGameExtension();

    /////////////////////////////////////////////////////////////////////////
}


void GameExtension::printLoginUserInfo() {
    cout << "Logged-in ID List : ";
    if (getLoginUserInfo().empty()) {
        cout << "No player is logged in" << endl;
    }
    else {
        for (auto& info : getLoginUserInfo()) {
            cout << info.first << " ";
        }
        cout << endl;
    }
}


// gamesavefile_players, loginuserinfo 비교용도 - 로그인 이후 게임 시작 전에 저장된 게임이 있는지 확인
bool GameExtension::isSameIgnoreOrder(const vector<pair<string,string>>& v1, const vector<vector<string>>& v2) {
    vector<string> v1_strings;
    for (const auto& pair : v1) {
        v1_strings.push_back(pair.first);  // 첫 번째 문자열을 선택합니다.
    }
    sort(v1_strings.begin(), v1_strings.end());


    for (const auto& vec : v2) {
        vector<string> v2_strings;
        for (const auto& str : vec) {
            v2_strings.push_back(str);  // 각 벡터의 모든 문자열을 선택합니다.
        }
        sort(v2_strings.begin(), v2_strings.end());
        if (v1_strings == v2_strings) {
            // 몇 번째 줄이 같은 정보를 갖는지 확인합니다.
            
            return true;
        }
    }
    return false;
}


/*
Select animal type of Liam
(0: pig, 1: dog, 2: sheep, 3:cow) : 0
Select animal type of Ava
(0: pig, 1: dog, 2: sheep, 3:cow) : 0
*/
// 동물을 선택하고 animalplayers에 저장함. 

void GameExtension::animalSelect() {
   for (int i = 0; i < getLoginUserInfo().size(); i++) {
      cout << "Select animal type of " << getLoginUserInfo()[i].first << endl;
      cout << "(0: pig, 1: dog, 2: sheep, 3:cow) : ";
      int animal_type;
      cin >> animal_type;
      Animalplayers.push_back(AnimalPlayer(getLoginUserInfo()[i].first, animal_type));
   }
}

/*
-----------------------------------------
Liam(pig) Ava(pig) 
이런 형태로써 출력을 하기 위함.
*/

// GameExtension class
void GameExtension::printAnimalPlayerInfo() {
   cout << "-----------------------------------------" << endl;
   for (int i = 0; i < Animalplayers.size(); i++) {
      cout << Animalplayers[i].getName() << '(';
      // 동물의 종류를 저장하는 변수 0:pig 1:dog 2:sheep 3:cow로 설정됨.
      switch (Animalplayers[i].getAnimalType()) {
         case 0:
            cout << "pig";
            break;
         case 1:
            cout << "dog";
            break;
         case 2:
            cout << "sheep";
            break;
         case 3:
            cout << "cow";
            break;
      }
      cout << ") ";
   }
   cout << endl;
}

// restoreGame()

   // 게임을 불러오지 않고 새 게임을 시작하면 game_info의 기존 게임정보가 사라집니다. 
   // 계속 하겠다고 하더라도 기존 게임 정보가 업데이트 되어야하므로, 기존 게임 정보는 지워집니다. 



void GameExtension::restoreGame() {
   // 나는 game_info.txt를 받아가지고, 
   // 일단은 한 줄을 읽을 때 예를 들어서 이렇게 txt 파일이 되어 있다 칩시다.
   // 그러면은 일단 첫 번째 줄에서 Ethan Liam | Ethan 0 0 0 0 0 | Liam 1 0 0 0 2 | 0 파트에서 
   // Ethan Liam을 받아가지고 이게 만약에 isSameIgnoreOrder 하고 비교했을 때 
   // 같다면은 그 다음에 있는 것들을 받아가지고 Animalplayers에 저장을 하면 됩니다.
   // Ethan Liam | Ethan 0 0 0 0 0 | Liam 1 0 0 0 2 | 0
   // Olivia Ava Sophia | Olivia 2 0 0 10 10 | Ava 1 0 0 2 100 | Sophia 3 0 3 100 100 | 2
   // Noah Liam | Noah 1 0 100 100 100 | Liam 0 1 5 5 5 | 1
   // 일단 로그인 된 유저들의 이름을 받아가지고 정렬을 해놓습니다.

   vector<string> logInUsers;
   for (int i = 0; i < getLoginUserInfo().size(); i++) {
      logInUsers.push_back(getLoginUserInfo()[i].first);
   }
   sort(logInUsers.begin(), logInUsers.end());

   fstream file("game_info.txt");
   string line;
   int linenumbercounter = 0;
   int deleteline = 0;

   while (getline(file, line)) {
      linenumbercounter++; // 라인 읽을 떄마다 카운터 증가

      stringstream ss(line);
      string name;
      vector<string> players;

      while (ss >> name && name.find('|') == std::string::npos) { 
         // 처음으로 '|' 문자를 만날 때까지 이름을 읽습니다.
         players.push_back(name);
      }
      sort(players.begin(), players.end());
      
      if (logInUsers == players) {
         deleteline = linenumbercounter;

         string name;
         int animal_type;
         vector<int> pieces;
         int turn;

         for (int i = 0; i < players.size(); i++) {
            string temp;
            getline(ss, temp, '|');
            stringstream iss(temp);
            iss >> name >> animal_type;
            for (int j = 0; j < 4; j++) {
               int piece;
               iss >> piece;
               pieces.push_back(piece);
            }
            Animalplayers.push_back(AnimalPlayer(name, animal_type));
            Animalplayers[i].setPieces(pieces);
            Animalplayers[i].updateArrivedPieceNum();
            pieces.clear();
         }

         string temp;
         getline(ss, temp);
         stringstream iss(temp);
         iss >> turn;
         setgameturn(turn);

      } else {
         continue;
      }
      // players, vector<pair<string,string>> LoginUserInfo.first() 부분과 각각 비교해봅니다.
      // 만약에 같다면은 그 다음에 있는 것들을 받아가지고 Animalplayers에 저장을 하면 됩니다.
    }
   file.close();

   
   // deleteline 번째 라인을 삭제하는 코드를 추가합니다.
   //deleteline


   
   fstream file2("game_info.txt", ios::in);
   vector<string> templines;
   string line2;
   int targetline = 0;

   while (getline(file2, line2)) {
      targetline++;
      if (targetline != deleteline) // deleteline과 일치하지 않는 라인만 templines에 저장합니다.
         templines.push_back(line2);
   }
   file2.close();

   file2.open("game_info.txt", ios::out | ios::trunc); // 기존 라인을 모두 삭제.
   for (int i = 0; i < templines.size(); i++) {
      if (i != templines.size() - 1) {
         file2 << templines[i] << endl; // templines에 저장된 라인을 파일에 씁니다.
      } else {
         file2 << templines[i]; // 마지막 라인에서는 endl을 사용하지 않습니다.
      }
   }
   file2.close();
}


void GameExtension::updatingGame_info() {
   // 기존 게임 정보를 지웁니다!!
   vector<string> logInUsers;
   for (int i = 0; i < getLoginUserInfo().size(); i++) {
      logInUsers.push_back(getLoginUserInfo()[i].first);
   }
   sort(logInUsers.begin(), logInUsers.end());

   fstream file("game_info.txt");
   string line;
   int linenumbercounter = 0;
   int deleteline = 0;

   while (getline(file, line)) {
      linenumbercounter++; // 라인 읽을 떄마다 카운터 증가
      stringstream ss(line);
      string name;
      vector<string> players;

      while (ss >> name && name.find('|') == std::string::npos) { 
         // 처음으로 '|' 문자를 만날 때까지 이름을 읽습니다.
         players.push_back(name);
      }
      sort(players.begin(), players.end());
      
      if (logInUsers == players) {
         deleteline = linenumbercounter;

      } else {
         continue;
      }
      // players, vector<pair<string,string>> LoginUserInfo.first() 부분과 각각 비교해봅니다.
      // 만약에 같다면은 그 다음에 있는 것들을 받아가지고 Animalplayers에 저장을 하면 됩니다.
    }
   file.close();

   
   fstream file2("game_info.txt", ios::in);
   vector<string> templines;
   string line2;
   int targetline = 0;

   while (getline(file2, line2)) {
      targetline++;
      if (targetline != deleteline) // deleteline과 일치하지 않는 라인만 templines에 저장합니다.
         templines.push_back(line2);
   }
   file2.close();

   file2.open("game_info.txt", ios::out | ios::trunc); // 기존 라인을 모두 삭제.
   for (int i = 0; i < templines.size(); i++) {
      if (i != templines.size() - 1) {
         file2 << templines[i] << endl; // templines에 저장된 라인을 파일에 씁니다.
      } else {
         file2 << templines[i]; // 마지막 라인에서는 endl을 사용하지 않습니다.
      }
   }
   file2.close();

}


bool GameExtension::backupChecker() {
   cout << "Continue (0) / Save and Exit the game (1) : ";
   int i;
   while (1) {
      cin >> i;
      if (i == 1) {
         //cout << "backup..." << endl;
         backupGame();
         return true;
      }
      if (i == 0) {
         //cout << "continue..." << endl;
         return false;
      }
      cout << "Invalid input. Please enter 0 to continue or 1 to save and exit: " << endl;
   }
}



/*
하던 게임을 더 명확하게 해야 할 것같습니다.
저장된 게임을 불러온 경우: 추후에 저장시 해당 게임 정보를 업데이트
새로운 게임을 시작한 경우: 새롭게 게임 정보 저장 (4줄)
그 외의 기존의 게임 정보는 그대로 유지되어야 합니다.
처음에 기존 게임 정보를 불러온다면 불러올 때 해당 게임은 제거가 됩니다.
그리고 추후에 저장하면 Ethan Liam | Ethan 0 0 0 100 100 | Liam 1 0 0 100 100 | 1  로 저장될 것입니다.
피피티에 적힌 로직과 제가 앞에서 설명드린 로직을 생각해보시면 Ethan Liam 두 플레이어에 대한 게임 정보가 여러개가 될 수 없습니다.
*/

void GameExtension::backupGame() {
   ofstream file("game_info.txt", ios::app); 
   if (file.fail()) {
    cerr << "Failed to open the file." << endl;
    return;
   }
   file << "\n";

   for (int i = 0; i < Animalplayers.size(); i++) {
      file << Animalplayers[i].getName() << " ";
   }
   file << "| ";
   for (int i = 0; i < Animalplayers.size(); i++) {
      file << Animalplayers[i].getName() << " " << Animalplayers[i].getAnimalType() << " ";
      for (int j = 0; j < 4; j++) {
         file << Animalplayers[i].getPieces()[j] << " ";
      }
      file << "| ";
   }

   file << getgameturn();
   file.close();
   cout << "Game saved successfully!" << endl;
}

/*
Continue (0) / Save and Exit the game (1) : 1
Game saved successfully!
*/





void GameExtension::printAnimalPlayerInfo2() {
   cout << Animalplayers.size() << endl;
   for (int i = 0; i < Animalplayers.size(); i++) {
      cout << Animalplayers[i].getName() << " " << Animalplayers[i].getAnimalType() << " ";
      for (int j = 0; j < 4; j++) {
         cout << Animalplayers[i].getPieces()[j] << " ";
      }
      cout << Animalplayers[i].getArrivedPieceNum() << endl;
   }
}



void GameExtension::printCurrentTurn(int player_order) {
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    if (player_order == 0) {
        cout << "Player " << COLOR_RED << player_order << COLOR_DEFAULT
             << " " << Animalplayers[player_order].getName() << " turn" << endl;
    } else if (player_order == 1) {
        cout << "Player " << COLOR_BLUE << player_order << COLOR_DEFAULT
             << " " << Animalplayers[player_order].getName() << " turn" << endl;
    } else if (player_order == 2) {
        cout << "Player " << COLOR_GREEN << player_order << COLOR_DEFAULT
             << " " << Animalplayers[player_order].getName() << " turn" << endl;
    } else if (player_order == 3) {
        cout << "Player " << COLOR_YELLOW << player_order << COLOR_DEFAULT
             << " " << Animalplayers[player_order].getName() << " turn" << endl;
    } else {
        cout << "Player " << player_order << Animalplayers[player_order].getName() << " turn" << endl;
    }

    cout << "Piece : ";
      if (player_order >= 0 && player_order < Animalplayers.size()) {
         // 선택된 플레이어의 말 위치를 가져옵니다.
         vector<int> playerPieces = Animalplayers[player_order].getPieces();
   
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
      cout << "Yut : ";
      // 가능한 Yut list를 출력, 순서대로 잘 나옴.
      if (player_order >= 0 && player_order < Animalplayers.size()) {
         const multiset<YutName>& yut_list = Animalplayers[player_order].getYutList();
         for (const YutName& yut : yut_list) {
               cout << yut.getName() << ' ';
         }
      }
      cout << '\n';
}



void GameExtension::fillPlayerToBoard(Board& board) {
   // player_to_board 를 초기화
   board.initializeBoard();

   // 각 플레이어의 말의 위치를 순회하고 board 클래스에 있는 변수 player_to_board를 수정해줌.
   for (int i = 0; i < Animalplayers.size(); i++) {
        for (const int& pos : Animalplayers[i].getPieces()) {
            // player_to_board에 대한 참조를 한 번만 가져옵니다.
            auto& player_to_board = board.getPlayerToBoard();

            if (pos > 0 && pos < board.getBoardMapping().size()) {
                int_pair mapped_pos = board.getBoardMapping()[pos];
                int row = mapped_pos.first;
                int col = mapped_pos.second;

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
                // 그대로 이 값들이 -1 0 형태가 되게끔 유지만 시킨다.
                continue;
            }
        }
    }
}


void GameExtension::printPieceState() {
      cout << "-----------------------------------------" << endl;
      cout << "Not started : ";
      cout << endl;
      //////////////////IMPLEMENT HERE//////////////////////////////////////
      for (int i = 0; i < Animalplayers.size(); ++i) {
         const AnimalPlayer& player = Animalplayers[i];
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
      for (int i = 0; i < Animalplayers.size(); ++i) {
         const AnimalPlayer& player = Animalplayers[i];
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



bool GameExtension::isGameEnd() {
    for (int i = 0; i < Animalplayers.size(); ++i) {
        if (Animalplayers[i].getArrivedPieceNum() == Animalplayers[i].getPieces().size()) {
            return true;
        }
    }
    return false;
}



