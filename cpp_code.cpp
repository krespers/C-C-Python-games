#include <stdio.h>

int Bingo(int arr[3][3], int n);

int main() {
    int board[3][3] = { {11, 12, 13}, {14, 15, 16}, {17, 18, 19} }; // 게임보드 각 칸 번호
    int player = 0; // player number
    int x, y; // 착수 위치
    int choice = 0; // 진행 횟수

    while (1) {
        printf("player [%d]의 착수위치(x,y)를 입력하시오 : ", player);
        scanf("%d %d", &x, &y);

        if (board[x][y] < 11 || x > 2 || x < 0 || y > 2 || y < 0) {
            printf("\n잘못된 입력입니다. 다시 입력하시오. \n\n");
            continue;
        }

        if (player == 0) {
            board[x][y] = 1;
            player = 1;
        } else {
            board[x][y] = 2;
            player = 0;
        }

        choice++;

        printf("\n");

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == 1) {
                    printf("%c", 'O');
                } else if (board[i][j] == 2) {
                    printf("%c", 'X');
                } else {
                    printf("*");
                }
            }
            printf("\n");
        } // 출력

        int result = Bingo(board, choice);

        if (result == 0) {
            if (player == 0) {
                printf("player[1] 승리 ! \n");
            } else {
                printf("player[0] 승리 ! \n");
            }
            break;
        } else if (result == 1) {
            printf("무승부. \n");
            break;
        }
    }

    return 0;
}

int Bingo(int ary[3][3], int n) {
    if ((ary[0][0] == ary[1][1] && ary[0][0] == ary[2][2]) || (ary[0][2] == ary[1][1] && ary[0][2] == ary[2][0])) {
        return 0;
    } // 대각선으로 빙고가 생기는지 확인

    for (int line = 0; line <= 2; line++) {
        if ((ary[line][0] == ary[line][1] && ary[line][0] == ary[line][2]) || (ary[0][line] == ary[1][line] && ary[0][line] == ary[2][line])) {
            return 0;
            
        } // 가로, 세로줄로 빙고가 생기는지 확인, line은 각 가로, 세로줄의 줄 번호
    }

    if (n == 9) {
        return 1;
    } // 시행횟수가 9번이면 무승부로 결정

    return 2; // 추가: 빙고가 아직 없고 무승부도 아니면 계속 진행
}
