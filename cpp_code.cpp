#include <stdio.h>

int Bingo(int arr[3][3], int n);

int main() {
    int board[3][3] = { {11, 12, 13}, {14, 15, 16}, {17, 18, 19} }; // ���Ӻ��� �� ĭ ��ȣ
    int player = 0; // player number
    int x, y; // ���� ��ġ
    int choice = 0; // ���� Ƚ��

    while (1) {
        printf("player [%d]�� ������ġ(x,y)�� �Է��Ͻÿ� : ", player);
        scanf("%d %d", &x, &y);

        if (board[x][y] < 11 || x > 2 || x < 0 || y > 2 || y < 0) {
            printf("\n�߸��� �Է��Դϴ�. �ٽ� �Է��Ͻÿ�. \n\n");
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
        } // ���

        int result = Bingo(board, choice);

        if (result == 0) {
            if (player == 0) {
                printf("player[1] �¸� ! \n");
            } else {
                printf("player[0] �¸� ! \n");
            }
            break;
        } else if (result == 1) {
            printf("���º�. \n");
            break;
        }
    }

    return 0;
}

int Bingo(int ary[3][3], int n) {
    if ((ary[0][0] == ary[1][1] && ary[0][0] == ary[2][2]) || (ary[0][2] == ary[1][1] && ary[0][2] == ary[2][0])) {
        return 0;
    } // �밢������ ���� ������� Ȯ��

    for (int line = 0; line <= 2; line++) {
        if ((ary[line][0] == ary[line][1] && ary[line][0] == ary[line][2]) || (ary[0][line] == ary[1][line] && ary[0][line] == ary[2][line])) {
            return 0;
            
        } // ����, �����ٷ� ���� ������� Ȯ��, line�� �� ����, �������� �� ��ȣ
    }

    if (n == 9) {
        return 1;
    } // ����Ƚ���� 9���̸� ���ºη� ����

    return 2; // �߰�: ���� ���� ���� ���ºε� �ƴϸ� ��� ����
}
