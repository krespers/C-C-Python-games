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


   // �α��ΰ� �����Ͽ� �����Ͱ� �� �ԷµǾ����� ������ �����սô�.
   // ������ ���۵Ǹ� �� ����� ���� ��� 100 100 100 100�� �� ������ ��� �ݺ��մϴ�.
   // �ڱ� ���� ������ ���� �÷��̾�� �Ѿ�� ���� �������� ���ϰ� ���� ����ϴ�.
   // ������ ������ ���ڸ� ����ϰ� ������ �����մϴ�.
   // �׸��� ���ӿ� �ִ� ���� �����͸� ��� �� clear() �ʱ�ȭ �۾���, �ٽ� menuSelect()�� ���ư��ϴ�.
   // �� ������ ������ Ư���� ���
    // pig
    // If someone else (player A) catches you, A ends his turn immediately. sheep ���� pig�� �� ��.
    // dog
    // Even if the stick result is geol (�ϳ��� geol), you should throw again (�ٽ� �� �� �� ����!)
    // sheep
    // If you catch someone else, you have two chances to throw again.
    // cow ��� : You can only move along the specific path
    // cow�� 0,1,2,3,4,5,20,21,22,23,24,15,16,17,18,19,29,100�� ��Ʈ�θ� �̵���


void GameExtension::run() {
   //////////////////IMPLEMENT HERE/////////////////////////////////////
   ifstream game_info("game_info.txt");
   string line;
   while (getline(game_info, line)) {
      istringstream iss(line);
      string name;
      vector<string> players;
      while (iss >> name && name.find('|') == std::string::npos) { 
         // '|' ���ڸ� ���� ������ �̸��� �н��ϴ�.
         players.push_back(name);
      }
      addGameSavefile_Players(players);
   }
   game_info.close();


   // ���࿡ game_info.txt�� ����� ���ӿ� ���� �÷��̾� �̸��� �ִٸ�
   // �� �̸��� �޾ƿ� �ǰ� �� �ǰ�?
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
               // ������ �����ϰ� animalplayers�� ������. �� ����
               updatingGame_info();
               animalSelect();
               setgameturn(0); // ���� ���� 0���� �ʱ�ȭ�մϴ�.

               break;
         }
         cout << "Invalid input. Please enter 0 to start a new game or 1 to resume: " << endl;
      }
   } else {
      animalSelect();
      setgameturn(0); // ���� ���� 0���� �ʱ�ȭ. �� ����.
   }

   Board board;
   board.initializeBoard();

   // board.printPlayerToBoard(); // ����� Ȯ�ο� �ڵ�
   // printAnimalPlayerInfo2();  
   // �ϴ� ���� ó�� �����ϱ� ���� ���� ���� �����

   int start = getgameturn();
   
   while (!isGameEnd()) {
      // gameturn checking.
      // i�� 0�̸� 0���� ����, �ƴϸ� �ٸ� ������ ������ ��.
   // 2���̼� ������ �ߴ� ġ��. �׷��� 0,1,0,1,0,1,0,1 �̷��� ���ư��鼭 ������ �����.
   // getgameturn�� 0���ݾ�. start=0
      for (int i = start; i < start + Animalplayers.size(); ++i) {
         int currentTurn = i % Animalplayers.size();

         setgameturn(currentTurn); // ???

         fillPlayerToBoard(board);
         board.printBoard();
         printAnimalPlayerInfo();
         printPieceState();
         // ��� ����� �ڵ�. 0,1 �Է�...
         bool isbackup = backupChecker(); 
         if (isbackup) {
            // �������� ������ ���� ���, ��� �����͸� �ʱ�ȭ
            // board�� ���Ͽ�
            board.initializeBoard();
            // Animalplayer�� ���Ͽ�
            for(auto& player : Animalplayers) {
               player.resetAnimalPlayer(); // 
            }
            // game�� ���Ͽ�
            Animalplayers.clear();
            resetGameExtension();

            return;
         }

         // i��° �÷��̾��� �� ����
         // i��° �÷��̾ �ϴ��� �ڱ� ���� �����ϱ� ó����, ���� �����ϴ�.
         AnimalPlayer &current_player = Animalplayers[currentTurn];

         if (current_player.getAnimalType() == 1) {
            current_player.throwYutDog(yut); // dog�� ���ؼ���.
         } else {
            current_player.throwYut(yut);
         }
// animalplayers[i]�� yut_list�� �� ����� �������� Ȥ�� �ڱⰡ ��� pieces�� ��ġ�� ����(100) �ƴϸ� �� �ȳ���.
         
         while (!current_player.isYutListEmpty()) {      
         // �ϴ� �ڱⰡ ���� �ִ� ���� üũ�� ���¿��� ������ ������ �ʾҴٸ� �Ʒ��� ������.
            if(current_player.getArrivedPieceNum() == 4) {
               break;
            }
            
            fillPlayerToBoard(board); //���ӿ� �������� "��� �÷��̾�"�� �� ��ġ�� ���忡 ä���� �մϴ�.
            board.printBoard(); // ���� ���� ���¸� ��� 
            // board.printPlayerToBoard(); // ����� Ȯ�ο� �ڵ� �ڵ�
            printAnimalPlayerInfo();
            printPieceState(); // ���� ���¸� ����մϴ�.
            
            printCurrentTurn(currentTurn); // ���� �÷��̾��� ���� ����մϴ�.
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
         

            int solution_position;
            if (current_player.getAnimalType() == 3) {
               solution_position = current_player.movePlayerCow(position, input_yut);
            } else {
               solution_position = current_player.movePlayer(position, input_yut);
            }
            
            // ���࿡ ���� ����� solution_position ��ġ�� 0�̶��, �̵��� �� �ִ� ��ġ�� ���ٴ� ���̴�
            //if (solution_position == 0) {
               // i++; 
               // �̷��� �ع������� i�� ���ڱ� �þ������ ū�ϳ���.
            //   continue;
            //}

            

            // Ž���ϴ� �Լ� ���� ����� solution_position�� �ٸ� �÷��̾��� ���� �ִ� ���
            current_player.sortPieces();
            // pig�� ������ sheep ���� �ƴ����� ���� �����ϰ�, ���� ���̶� ���� �� ��ΰ� ���� ��ġ�� ��.
            // �׸��� pig�� ���� �༮�� yut�� ��� �ʱ�ȭ���ѹ���.
            // sheep�� ���� ������ ���� �� �� �� ������ �� ����Ʈ�� �߰���.
                         
            // �ٸ��÷��̾��� ���� �ִ��� Ȯ���մϴ�.
            bool hasOtherPlayerPiece = false;
            bool isCatchedPlayerIsPig = false;
            
            if (solution_position != 0) {
               for (AnimalPlayer& other_player : Animalplayers) {
                  if (&other_player != &current_player && other_player.hasPieceAt(solution_position)) {
                     // ���� ���� ���� ��ġ�� �����ϴ�.
                     other_player.sendPieceToStart(solution_position);
                     if (other_player.getAnimalType() == 0) {
                        isCatchedPlayerIsPig = true;
                     }
                     // ���� �� �� �� ������ �� ����Ʈ�� �߰��մϴ�.
                     current_player.throwYut(yut);
                     // ���� ���࿡ sheep�̸� ���� �� �� �� �����ϴ�.
                     if (current_player.getAnimalType() == 2) {
                        current_player.throwYut(yut);
                     }
                     hasOtherPlayerPiece = true;
                     break;
                  }
               }
            }


            // �ٸ� �÷��̾��� ���� ������ �� ���� ���, ������ �׳� ���� �̵��մϴ�.
            current_player.movePiece(position, solution_position);
            current_player.updateArrivedPieceNum();// ������ ���� ������ ������Ʈ�մϴ�.
            // pieces vector�� ������ ������������ �����ϴ� �뵵��(?) Ȱ����
            current_player.sortPieces();

         //   cout << "solution_position : " << solution_position << endl;
         //   cout << "currentTurn : " << i << endl;            
               
            if (isCatchedPlayerIsPig) {
               current_player.resetYutList();
               break;
            }

         }

         // �� �������� �̰��� ��쿡 (���� player0�� �� �� ���� �̰�µ� player1�� �� ������ �ʰ� ������ ������ �ϹǷ�)
         if (current_player.getArrivedPieceNum() == 4) {
            break;
         }
      }
   }

   // ���� �����ϴ� �ɷ� while(for()) loop�� ���������� ��쿡�� ������ ��������
   // �̰Ŵ� ������ ���� ���� ���� ����� �ϴ� �Ŵϱ� ���� �� �� �ʿ� ����. 
    // ���ڸ� Ȯ��.
    for (int i = 0; i < Animalplayers.size(); ++i) {
        if (Animalplayers[i].getArrivedPieceNum() == 4) {
            cout << "Player " << i << " win" << endl;
        }
    }
   /////////////////////////////////////////////////////////////////////////
   // �������� ������ ���� ���, ��� �����͸� �ʱ�ȭ
   // board�� ���Ͽ�
   board.initializeBoard();


   // Animalplayer�� ���Ͽ�
   for(auto& player : Animalplayers) {
      player.resetAnimalPlayer(); // 
   }

   // game�� ���Ͽ�
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


// gamesavefile_players, loginuserinfo �񱳿뵵 - �α��� ���� ���� ���� ���� ����� ������ �ִ��� Ȯ��
bool GameExtension::isSameIgnoreOrder(const vector<pair<string,string>>& v1, const vector<vector<string>>& v2) {
    vector<string> v1_strings;
    for (const auto& pair : v1) {
        v1_strings.push_back(pair.first);  // ù ��° ���ڿ��� �����մϴ�.
    }
    sort(v1_strings.begin(), v1_strings.end());


    for (const auto& vec : v2) {
        vector<string> v2_strings;
        for (const auto& str : vec) {
            v2_strings.push_back(str);  // �� ������ ��� ���ڿ��� �����մϴ�.
        }
        sort(v2_strings.begin(), v2_strings.end());
        if (v1_strings == v2_strings) {
            // �� ��° ���� ���� ������ ������ Ȯ���մϴ�.
            
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
// ������ �����ϰ� animalplayers�� ������. 

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
�̷� ���·ν� ����� �ϱ� ����.
*/

// GameExtension class
void GameExtension::printAnimalPlayerInfo() {
   cout << "-----------------------------------------" << endl;
   for (int i = 0; i < Animalplayers.size(); i++) {
      cout << Animalplayers[i].getName() << '(';
      // ������ ������ �����ϴ� ���� 0:pig 1:dog 2:sheep 3:cow�� ������.
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

   // ������ �ҷ����� �ʰ� �� ������ �����ϸ� game_info�� ���� ���������� ������ϴ�. 
   // ��� �ϰڴٰ� �ϴ��� ���� ���� ������ ������Ʈ �Ǿ���ϹǷ�, ���� ���� ������ �������ϴ�. 



void GameExtension::restoreGame() {
   // ���� game_info.txt�� �޾ư�����, 
   // �ϴ��� �� ���� ���� �� ���� �� �̷��� txt ������ �Ǿ� �ִ� Ĩ�ô�.
   // �׷����� �ϴ� ù ��° �ٿ��� Ethan Liam | Ethan 0 0 0 0 0 | Liam 1 0 0 0 2 | 0 ��Ʈ���� 
   // Ethan Liam�� �޾ư����� �̰� ���࿡ isSameIgnoreOrder �ϰ� ������ �� 
   // ���ٸ��� �� ������ �ִ� �͵��� �޾ư����� Animalplayers�� ������ �ϸ� �˴ϴ�.
   // Ethan Liam | Ethan 0 0 0 0 0 | Liam 1 0 0 0 2 | 0
   // Olivia Ava Sophia | Olivia 2 0 0 10 10 | Ava 1 0 0 2 100 | Sophia 3 0 3 100 100 | 2
   // Noah Liam | Noah 1 0 100 100 100 | Liam 0 1 5 5 5 | 1
   // �ϴ� �α��� �� �������� �̸��� �޾ư����� ������ �س����ϴ�.

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
      linenumbercounter++; // ���� ���� ������ ī���� ����

      stringstream ss(line);
      string name;
      vector<string> players;

      while (ss >> name && name.find('|') == std::string::npos) { 
         // ó������ '|' ���ڸ� ���� ������ �̸��� �н��ϴ�.
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
      // players, vector<pair<string,string>> LoginUserInfo.first() �κа� ���� ���غ��ϴ�.
      // ���࿡ ���ٸ��� �� ������ �ִ� �͵��� �޾ư����� Animalplayers�� ������ �ϸ� �˴ϴ�.
    }
   file.close();

   
   // deleteline ��° ������ �����ϴ� �ڵ带 �߰��մϴ�.
   //deleteline


   
   fstream file2("game_info.txt", ios::in);
   vector<string> templines;
   string line2;
   int targetline = 0;

   while (getline(file2, line2)) {
      targetline++;
      if (targetline != deleteline) // deleteline�� ��ġ���� �ʴ� ���θ� templines�� �����մϴ�.
         templines.push_back(line2);
   }
   file2.close();

   file2.open("game_info.txt", ios::out | ios::trunc); // ���� ������ ��� ����.
   for (int i = 0; i < templines.size(); i++) {
      if (i != templines.size() - 1) {
         file2 << templines[i] << endl; // templines�� ����� ������ ���Ͽ� ���ϴ�.
      } else {
         file2 << templines[i]; // ������ ���ο����� endl�� ������� �ʽ��ϴ�.
      }
   }
   file2.close();
}


void GameExtension::updatingGame_info() {
   // ���� ���� ������ ����ϴ�!!
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
      linenumbercounter++; // ���� ���� ������ ī���� ����
      stringstream ss(line);
      string name;
      vector<string> players;

      while (ss >> name && name.find('|') == std::string::npos) { 
         // ó������ '|' ���ڸ� ���� ������ �̸��� �н��ϴ�.
         players.push_back(name);
      }
      sort(players.begin(), players.end());
      
      if (logInUsers == players) {
         deleteline = linenumbercounter;

      } else {
         continue;
      }
      // players, vector<pair<string,string>> LoginUserInfo.first() �κа� ���� ���غ��ϴ�.
      // ���࿡ ���ٸ��� �� ������ �ִ� �͵��� �޾ư����� Animalplayers�� ������ �ϸ� �˴ϴ�.
    }
   file.close();

   
   fstream file2("game_info.txt", ios::in);
   vector<string> templines;
   string line2;
   int targetline = 0;

   while (getline(file2, line2)) {
      targetline++;
      if (targetline != deleteline) // deleteline�� ��ġ���� �ʴ� ���θ� templines�� �����մϴ�.
         templines.push_back(line2);
   }
   file2.close();

   file2.open("game_info.txt", ios::out | ios::trunc); // ���� ������ ��� ����.
   for (int i = 0; i < templines.size(); i++) {
      if (i != templines.size() - 1) {
         file2 << templines[i] << endl; // templines�� ����� ������ ���Ͽ� ���ϴ�.
      } else {
         file2 << templines[i]; // ������ ���ο����� endl�� ������� �ʽ��ϴ�.
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
�ϴ� ������ �� ��Ȯ�ϰ� �ؾ� �� �Ͱ����ϴ�.
����� ������ �ҷ��� ���: ���Ŀ� ����� �ش� ���� ������ ������Ʈ
���ο� ������ ������ ���: ���Ӱ� ���� ���� ���� (4��)
�� ���� ������ ���� ������ �״�� �����Ǿ�� �մϴ�.
ó���� ���� ���� ������ �ҷ��´ٸ� �ҷ��� �� �ش� ������ ���Ű� �˴ϴ�.
�׸��� ���Ŀ� �����ϸ� Ethan Liam | Ethan 0 0 0 100 100 | Liam 1 0 0 100 100 | 1  �� ����� ���Դϴ�.
����Ƽ�� ���� ������ ���� �տ��� ����帰 ������ �����غ��ø� Ethan Liam �� �÷��̾ ���� ���� ������ �������� �� �� �����ϴ�.
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
         // ���õ� �÷��̾��� �� ��ġ�� �����ɴϴ�.
         vector<int> playerPieces = Animalplayers[player_order].getPieces();
   
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
      cout << "Yut : ";
      // ������ Yut list�� ���, ������� �� ����.
      if (player_order >= 0 && player_order < Animalplayers.size()) {
         const multiset<YutName>& yut_list = Animalplayers[player_order].getYutList();
         for (const YutName& yut : yut_list) {
               cout << yut.getName() << ' ';
         }
      }
      cout << '\n';
}



void GameExtension::fillPlayerToBoard(Board& board) {
   // player_to_board �� �ʱ�ȭ
   board.initializeBoard();

   // �� �÷��̾��� ���� ��ġ�� ��ȸ�ϰ� board Ŭ������ �ִ� ���� player_to_board�� ��������.
   for (int i = 0; i < Animalplayers.size(); i++) {
        for (const int& pos : Animalplayers[i].getPieces()) {
            // player_to_board�� ���� ������ �� ���� �����ɴϴ�.
            auto& player_to_board = board.getPlayerToBoard();

            if (pos > 0 && pos < board.getBoardMapping().size()) {
                int_pair mapped_pos = board.getBoardMapping()[pos];
                int row = mapped_pos.first;
                int col = mapped_pos.second;

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
                // �״�� �� ������ -1 0 ���°� �ǰԲ� ������ ��Ų��.
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
               cout << color << " �� " << COLOR_DEFAULT;
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
               cout << color << " �� " << COLOR_DEFAULT;
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



