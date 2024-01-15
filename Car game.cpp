#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 29
#define WIN_WIDTH 70

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = {' ', '+', '+', ' ',
                  '+', '+', '+', '+',
                  ' ', '+', '+', ' ',
                  '+', '+', '+', '+'};

int carpos = WIN_WIDTH / 2;
int score = 0;

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(int visible, DWORD size) {
    if (size == 0)
        size = 50;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void drawBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < 18; j++) {
            gotoxy(0 + j, i);
            printf("*");
            gotoxy(WIN_WIDTH - j, i);
            printf("*");
        }
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(SCREEN_WIDTH, i);
        printf("*");
    }
}

void genEnemy(int ind) {
    enemyX[ind] = 17 + rand() % (33);
}

void drawEnemy(int ind) {
    if (enemyFlag[ind] == 1) {
        gotoxy(enemyX[ind], enemyY[ind]);
        printf("****");
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        printf(" ** ");
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        printf("****");
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        printf(" ** ");
    }
}

void eraseEnemy(int ind) {
    if (enemyFlag[ind] == 1) {
        gotoxy(enemyX[ind], enemyY[ind]);
        printf("    ");
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        printf("    ");
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        printf("    ");
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        printf("    ");
        gotoxy(WIN_WIDTH - 40, 0);
        printf("     ||     ");
        gotoxy(WIN_WIDTH - 40, 5);
        printf("     ||     ");
        gotoxy(WIN_WIDTH - 40, 10);
        printf("     ||     ");
        gotoxy(WIN_WIDTH - 40, 15);
        printf("     ||     ");
        gotoxy(WIN_WIDTH - 40, 20);
        printf("     ||     ");
        gotoxy(WIN_WIDTH - 40, 25);
        printf("     ||     ");
    }
}

void resetEnemy(int ind) {
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void drawCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carpos, i + 22);
            printf("%c", car[i][j]);
        }
    }
}

void eraseCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carpos, i + 22);
            printf(" ");
        }
    }
}

int collision() {
    if (enemyY[0] + 4 >= 23) {
        if (enemyX[0] + 4 - carpos >= 0 && enemyX[0] + 4 - carpos < 9) {
            return 1;
        }
    }
    return 0;
}

void gameover() {
    system("cls");
    printf("\n\t\t----------------------------\n");
    printf("\t\t--------- Game Over --------\n");
    printf("\t\t----------------------------\n");
    printf("\t\tPress any Key to go back to menu.");
    getch();
}

void updateScore() {
    gotoxy(WIN_WIDTH + 7, 5);
    printf("Score: %d\n", score);
}

void instructions() {
    system("cls");
    printf("Instructions");
    printf("\n-----------------");
    printf("\n Avoid car by moving left or right.");
    printf("\n\n Press 'Arrow Keys' to move the Car");
    printf("\n\n Press 'escape' to Exit");
    printf("\n\n Press any Key to go back to the menu");
    getch();
}

void play() {
    carpos = -1 + WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    system("cls");
    drawBorder();
    updateScore();
    genEnemy(0);
    genEnemy(1);

    gotoxy(WIN_WIDTH + 7, 2);
    printf("Car Game");
    gotoxy(WIN_WIDTH + 6, 4);
    printf("----------");
    gotoxy(WIN_WIDTH + 6, 6);
    printf("----------");
    gotoxy(WIN_WIDTH + 7, 12);
    printf("Control ");
    gotoxy(WIN_WIDTH + 7, 13);
    printf("-------- ");
    gotoxy(WIN_WIDTH + 2, 14);
    printf("A Key - Left");
    gotoxy(WIN_WIDTH + 2, 15);
    printf("D Key - Right");
    gotoxy(WIN_WIDTH + 2, 16);
    printf("Left Arrow - Left");
    gotoxy(WIN_WIDTH + 2, 17);
    printf("Right Arrow - Right");

    gotoxy(18, 5);
    printf("Press any key to start");
    getch();
    gotoxy(18, 5);
    printf("                      ");

    while (1) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 'a' || ch == 'A' || ch == 75) {
                if (carpos > 18)
                    carpos -= 4;
            }
            if (ch == 'd' || ch == 'D' || ch == 77) {
                if (carpos < 50)
                    carpos += 4;
            }
            if (ch == 27) {
                break;
            }
        }

        drawCar();
        drawEnemy(0);
        drawEnemy(1);
        if (collision() == 1) {
            gameover();
            return;
        }
        Sleep(50);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        if (enemyY[0] == 10)
            if (enemyFlag[1] == 0)
                enemyFlag[1] = 1;

        if (enemyFlag[0] == 1)
            enemyY[0] += 1;

        if (enemyFlag[1] == 1)
            enemyY[1] += 1;

        if (enemyY[0] > SCREEN_HEIGHT - 4) {
            resetEnemy(0);
            score++;
            updateScore();
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4) {
            resetEnemy(1);
            score++;
            updateScore();
        }
    }
}

int main() {
    setcursor(0, 0);
    srand((unsigned)time(NULL));

    do {
        system("cls");
        gotoxy(10, 5);
        printf(" -------------------------- ");
        gotoxy(10, 6);
        printf(" |        Car Game        | ");
        gotoxy(10, 7);
        printf(" --------------------------");
        gotoxy(10, 9);
        printf("1. Start Game");
        gotoxy(10, 10);
        printf("2. Instructions");
        gotoxy(10, 11);
        printf("3. Quit");
        gotoxy(10, 13);
        printf("Select option: ");
        char op = getch();

        if (op == '1') {
            play();
        } else if (op == '2') {
            instructions();
        } else if (op == '3') {
            exit(0);
        }

    } while (1);

    return 0;
}
