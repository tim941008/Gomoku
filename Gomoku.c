#include <conio.h>  // 使用getch();
#include <stdio.h>
#include <stdlib.h>  // 使用system();
#include <string.h>
#include <windows.h>   //使用sleep
char a[15][15][5];     // 棋盤陣列
int ex[15][15] = {0};  // examine用的 1代表黑2代表白
int re[225][3] = {0};  // 紀錄下棋的步驟
int game = 0;          // 紀錄落子數
// 遊戲首頁，顯示選單
char initialization() {
    printf("******************************\n");
    printf("*****       五子棋        ****\n");
    printf("*****1.開始遊戲 0.退出游戲****\n");
    printf("      進入遊戲後請輸入座標    \n");
    printf("     橫坐標由左至右為 0 ~ 14  \n");
    printf("     縱坐標由上至下為 0 ~ 14 \n");
    printf("輸入方法為橫坐標 空格 縱坐標 按下Enter\n");
    printf("      遊戲開始預設黑棋先下    \n");
    printf("        祝大家'棋'開得勝      \n");
    printf("******************************\n");
    return getch();
}
void clear() {  // 清屏
    printf("\033[2J\033[H");
}
// 初始化棋盤，設置邊框
void set() {
    system("color f0");  // 控制螢幕顏色
    int i, j;
    clear();
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (i == 0 && j == 0) {
                strcpy(a[i][j], " ┌");
            } 
            else if (i == 0 && j != 0 && j != 14) {
                strcpy(a[i][j], "-┬");
            } 
            else if (i == 0 && j == 14) {
                strcpy(a[i][j], "-┐");
            } 
            else if (i > 0 && i < 14 && j == 0) {
                strcpy(a[i][j], " ├");
            } 
            else if (i > 0 && i < 14 && j != 0 && j != 14) {
                strcpy(a[i][j], "-┼");
            } 
            else if (i > 0 && i < 14 && j == 14) {
                strcpy(a[i][j], "-┤");
            } 
            else if (i == 14 && j == 0) {
                strcpy(a[i][j], " └");
            } 
            else if (i == 14 && j != 0 && j != 14) {
                strcpy(a[i][j], "-┴");
            } 
            else {
                strcpy(a[i][j], "-┘");
            }
        }
    }
}
// 繪製棋盤
void draw() {
    int i, j;
    clear();
    printf("   ");
    for (i = 0; i < 15; i++) {
        if (i < 10) {
            printf("%d ", i);
        } else {
            printf("%d", i);
        }
    }
    printf("\n");
    for (i = 0; i < 15; i++) {
        if (i < 10) {
            printf("%d ", i);
        } else {
            printf("%d", i);
        }
        for (j = 0; j < 15; j++) {
            printf("%s", a[i][j]);
        }
        printf("\n");
    }
}
// 下棋函數，輸入棋子位置
void play_chess(char* symbol1, char* symbol2) {
    int i, j;
    printf("%s : %d\n", "落子數", game);
    printf("%s請落子:", ((strcmp(symbol1, " ●") == 0) ? "黑方" : "白方"));
    while (scanf(" %d %d", &i, &j) != 2 || i < 0 || i > 14 || j < 0 || j > 14 ||
           ex[i][j] != 0) {
        getchar();  // 清除緩衝區
        clear();
        draw();  // 重繪棋盤
        printf("%s : %d\n", "落子數", game);
        printf("%s請落子:", ((strcmp(symbol1, " ●") == 0) ? "黑方" : "白方"));
    }
    strcpy(a[i][j], (j == 0) ? symbol1 : symbol2);
    ex[i][j] = (strcmp(symbol1, " ●") == 0) ? 1 : 2;
    re[game][0] = i;
    re[game][1] = j;
    re[game][2] = ex[i][j];
    game++;
    draw();
}
// 勝利檢查函數
int checkwin(char* symbol) {
    int i, j;
    int count = 0, num = (strcmp(symbol, " ●") == 0) ? 1 : 2;
    // 橫向檢查
    for (i = 0; i < 15 && count < 4; i++) {
        for (j = 0; j < 14 && count < 4; j++) {
            count = (ex[i][j] == num && ex[i][j + 1] == num) ? ++count : 0;
        }
    }
    // 縱向檢查
    for (j = 0; j < 15 && count < 4; j++) {
        for (i = 0; i < 14 && count < 4; i++) {
            count = (ex[i][j] == num && ex[i + 1][j] == num) ? ++count : 0;
        }
    }
    // 斜向檢查 \ 方向
    for (i = 0; i < 11 && count < 4; i++) {
        for (j = 0; j < 14 - i && count < 4; j++) {
            count = (ex[i + j][j] == num && ex[i + j + 1][j + 1] == num)
                        ? ++count
                        : 0;
        }
        for (j = 0; j < 14 - i && count < 4; j++) {
            count = (ex[j][i + j] == num && ex[j + 1][i + j + 1] == num)
                        ? ++count
                        : 0;
        }
    }
    // 斜向檢查 / 方向
    for (i = 0; i < 11 && count < 4; i++) {
        for (j = 14; j > i && count < 4; j--) {
            count =
                (ex[14 - j + i][j] == num && ex[14 - j + i + 1][j - 1] == num)
                    ? ++count
                    : 0;
        }

        for (j = 14; j > i && count < 4; j--) {
            count =
                (ex[14 - j][j - i] == num && ex[14 - j + 1][j - i - 1] == num)
                    ? ++count
                    : 0;
        }
    }
    return count;
}
void review() {  // 復盤
    int i, j;
    for (i = 0; re[i][2] != 0; i++) {
        int num_1 = re[i][0];  // 橫排資料
        int num_2 = re[i][1];  // 直排資料
        if (re[i][2] == 1) {
            strcpy(a[num_1][num_2], (num_2 == 0) ? " ●" : "-●");
        } else {
            strcpy(a[num_1][num_2], (num_2 == 0) ? " ○" : "-○");
        }
        draw();
        Sleep(1000);
    }
}
char again() {
    clear();
    puts("按下Enter重新開始");
    puts("按下Esc退出遊戲");
    puts("按下空白鍵復盤並退出");
    return getch();
}
// 主函數
int main() {
    int i, j;
    char ch;  // 是否要重來
    char mode = initialization();
    clear();
    while (mode != '0') {
        switch (mode) {
            case '1':
                set();
                draw();
                while (1) {
                    play_chess(" ●", "-●");  // black chess
                    if (checkwin(" ●") == 4) {
                        puts("黑勝");
                        system("pause");
                        break;
                    }
                    play_chess(" ○", "-○");  // White chess
                    if (checkwin(" ○") == 4) {
                        puts("白勝");
                        system("pause");
                        break;
                    }
                }
                ch = again();
                while (ch != 27 && ch != 13 && ch != 32) {
                    ch = again();
                }
                if (ch == 27) {  // 按下esc
                    clear();
                    mode = '0';
                    break;
                } else if (ch == 32) {  // 按下空白鍵
                    set();
                    draw();
                    review();
                    mode = '0';
                    break;
                } else {  // 變數重新設定
                    game = 0;
                    for (i = 0; i < 15; i++) {
                        for (j = 0; j < 15; j++) {
                            ex[i][j] = 0;
                        }
                    }
                    for (i = 0; i < 225; i++) {
                        for (j = 0; j < 3; j++) {
                            re[i][j] = 0;
                        }
                    }
                    break;
                }
            default:
                mode = initialization();
                clear();
                break;
        }
    }
    return 0;
}
