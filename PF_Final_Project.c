#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

char board[3][3];
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove(char);
void computerMove();
char checkWinner();
void printWinner(char);

int main()
{
    char winner = ' ';
    char response = ' ';

    do
    {
        winner = ' ';
        response = ' ';
        resetBoard();

        int gameMode;
        printf("Choose game mode:\n");
        printf("1. Play against computer\n");
        printf("2. Play with two players\n");
        scanf("%d", &gameMode);

        while (winner == ' ' && checkFreeSpaces() != 0)
        {
            printBoard();

            if (gameMode == 1)
            {
                playerMove(PLAYER_X);
                winner = checkWinner();
                if (winner != ' ' || checkFreeSpaces() == 0)
                {
                    break;
                }

                computerMove();
            }
            else if (gameMode == 2)
            {
                playerMove(PLAYER_X);
                winner = checkWinner();
                if (winner != ' ' || checkFreeSpaces() == 0)
                {
                    break;
                }

                printBoard();

                playerMove(PLAYER_O);
                winner = checkWinner();
                if (winner != ' ' || checkFreeSpaces() == 0)
                {
                    break;
                }
            }
        }

        printBoard();
        printWinner(winner);

        printf("\nWould you like to play again? (Y/N): ");
        scanf(" %c", &response);
        response = toupper(response);
    } while (response == 'Y');
    
    printf("Thanks for playing!");
    
    return 0;
}
void resetBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}
void printBoard()
{
    printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}
int checkFreeSpaces()
{
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}
void playerMove(char player)
{
    int x, y;
    do
    {
        printf("Player %c, enter row #(1-3): ", player);
        scanf("%d", &x);
        x--;
        printf("Player %c, enter column #(1-3): ", player);
        scanf("%d", &y);
        y--;

        if (board[x][y] != ' ')
        {
            printf("Invalid move!\n");
        }
        else
        {
            board[x][y] = player;
            break;
        }
    } while (board[x][y] != ' ');
}
void computerMove()
{
    srand(time(0));
    int x, y;
    if (checkFreeSpaces() > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
    else
    {
        printWinner(' ');
    }
}
char checkWinner()
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }
    return ' ';
}
void printWinner(char winner)
{
    if (winner == PLAYER_X || winner == PLAYER_O)
    {
        printf("Player %c WINS!", winner);
    }
    else if (winner == COMPUTER)
    {
        printf("COMPUTER WINS!");
    }
    else
    {
        printf("IT'S A TIE!");
    }
}
