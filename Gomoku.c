#include <conio.h>  // �ϥ�getch();
#include <stdio.h>
#include <stdlib.h>  // �ϥ�system();
#include <string.h>
#include <windows.h>   //�ϥ�sleep
char a[15][15][5];     // �ѽL�}�C
int ex[15][15] = {0};  // examine�Ϊ� 1�N���2�N���
int re[225][3] = {0};  // �����U�Ѫ��B�J
int game = 0;          // �������l��
// �C�������A��ܿ��
char initialization() {
    printf("******************************\n");
    printf("*****       ���l��        ****\n");
    printf("*****1.�}�l�C�� 0.�h�X����****\n");
    printf("      �i�J�C����п�J�y��    \n");
    printf("     ��Хѥ��ܥk�� 0 ~ 14  \n");
    printf("     �a���ХѤW�ܤU�� 0 ~ 14 \n");
    printf("��J��k����� �Ů� �a���� ���UEnter\n");
    printf("      �C���}�l�w�]�´ѥ��U    \n");
    printf("        ���j�a'��'�}�o��      \n");
    printf("******************************\n");
    return getch();
}
void clear() {  // �M��
    printf("\033[2J\033[H");
}
// ��l�ƴѽL�A�]�m���
void set() {
    system("color f0");  // ����ù��C��
    int i, j;
    clear();
    for (i = 0; i < 15; i++) {
        for (j = 0; j < 15; j++) {
            if (i == 0 && j == 0) {
                strcpy(a[i][j], " �z");
            } 
            else if (i == 0 && j != 0 && j != 14) {
                strcpy(a[i][j], "-�s");
            } 
            else if (i == 0 && j == 14) {
                strcpy(a[i][j], "-�{");
            } 
            else if (i > 0 && i < 14 && j == 0) {
                strcpy(a[i][j], " �u");
            } 
            else if (i > 0 && i < 14 && j != 0 && j != 14) {
                strcpy(a[i][j], "-�q");
            } 
            else if (i > 0 && i < 14 && j == 14) {
                strcpy(a[i][j], "-�t");
            } 
            else if (i == 14 && j == 0) {
                strcpy(a[i][j], " �|");
            } 
            else if (i == 14 && j != 0 && j != 14) {
                strcpy(a[i][j], "-�r");
            } 
            else {
                strcpy(a[i][j], "-�}");
            }
        }
    }
}
// ø�s�ѽL
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
// �U�Ѩ�ơA��J�Ѥl��m
void play_chess(char* symbol1, char* symbol2) {
    int i, j;
    printf("%s : %d\n", "���l��", game);
    printf("%s�и��l:", ((strcmp(symbol1, " ��") == 0) ? "�¤�" : "�դ�"));
    while (scanf(" %d %d", &i, &j) != 2 || i < 0 || i > 14 || j < 0 || j > 14 ||
           ex[i][j] != 0) {
        getchar();  // �M���w�İ�
        clear();
        draw();  // ��ø�ѽL
        printf("%s : %d\n", "���l��", game);
        printf("%s�и��l:", ((strcmp(symbol1, " ��") == 0) ? "�¤�" : "�դ�"));
    }
    strcpy(a[i][j], (j == 0) ? symbol1 : symbol2);
    ex[i][j] = (strcmp(symbol1, " ��") == 0) ? 1 : 2;
    re[game][0] = i;
    re[game][1] = j;
    re[game][2] = ex[i][j];
    game++;
    draw();
}
// �ӧQ�ˬd���
int checkwin(char* symbol) {
    int i, j;
    int count = 0, num = (strcmp(symbol, " ��") == 0) ? 1 : 2;
    // ��V�ˬd
    for (i = 0; i < 15 && count < 4; i++) {
        for (j = 0; j < 14 && count < 4; j++) {
            count = (ex[i][j] == num && ex[i][j + 1] == num) ? ++count : 0;
        }
    }
    // �a�V�ˬd
    for (j = 0; j < 15 && count < 4; j++) {
        for (i = 0; i < 14 && count < 4; i++) {
            count = (ex[i][j] == num && ex[i + 1][j] == num) ? ++count : 0;
        }
    }
    // �צV�ˬd \ ��V
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
    // �צV�ˬd / ��V
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
void review() {  // �_�L
    int i, j;
    for (i = 0; re[i][2] != 0; i++) {
        int num_1 = re[i][0];  // ��Ƹ��
        int num_2 = re[i][1];  // ���Ƹ��
        if (re[i][2] == 1) {
            strcpy(a[num_1][num_2], (num_2 == 0) ? " ��" : "-��");
        } else {
            strcpy(a[num_1][num_2], (num_2 == 0) ? " ��" : "-��");
        }
        draw();
        Sleep(1000);
    }
}
char again() {
    clear();
    puts("���UEnter���s�}�l");
    puts("���UEsc�h�X�C��");
    puts("���U�ť���_�L�ðh�X");
    return getch();
}
// �D���
int main() {
    int i, j;
    char ch;  // �O�_�n����
    char mode = initialization();
    clear();
    while (mode != '0') {
        switch (mode) {
            case '1':
                set();
                draw();
                while (1) {
                    play_chess(" ��", "-��");  // black chess
                    if (checkwin(" ��") == 4) {
                        puts("�³�");
                        system("pause");
                        break;
                    }
                    play_chess(" ��", "-��");  // White chess
                    if (checkwin(" ��") == 4) {
                        puts("�ճ�");
                        system("pause");
                        break;
                    }
                }
                ch = again();
                while (ch != 27 && ch != 13 && ch != 32) {
                    ch = again();
                }
                if (ch == 27) {  // ���Uesc
                    clear();
                    mode = '0';
                    break;
                } else if (ch == 32) {  // ���U�ť���
                    set();
                    draw();
                    review();
                    mode = '0';
                    break;
                } else {  // �ܼƭ��s�]�w
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
