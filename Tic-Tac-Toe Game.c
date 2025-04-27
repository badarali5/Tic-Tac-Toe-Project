#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void displayBoard(char board[5][5], int size);
int checkWinner(char board[5][5], int size);
int checkDraw(char board[5][5], int size);
int makeMove(char board[5][5], int size, char currentPlayer, const char *playerName, int timeLimit);
void printLine(int size);
void tournamentMode(int size, char *player1Name, char *player2Name);
void timeAttackMode(int size, char *player1Name, char *player2Name);
int main() {
    int size;
    char mode;
     printf("\nWelcome to Tic-Tac-Toe: The Ultimate Showdown! \nTest your strategy and speed against your opponent.\n\n");
    printf("Modes available:\nT - Tournament Mode (Best of 3 rounds)\nA - Time Attack Mode (5-second time limit per move)\n\n");

    printf("Enter the board size (3 for 3x3, 4 for 4x4, 5 for 5x5): ");
    scanf("%d", &size);

    if (size < 3 || size > 5) {
        printf("\nInvalid size!");
        return 0;
    }

    printf("Choose a game mode (T for Tournament, A for Time Attack): ");
    getchar();
    scanf("%c", &mode);

    if(mode != 'a'&& mode !='A'&& mode !='t' && mode !='T' ){
    printf("Invalid INput");
    return 0;
    }
    char player1Name[50], player2Name[50];

    printf("Enter name for Player 1 (X): ");
    scanf("%s", player1Name);
    printf("Enter name for Player 2 (O): ");
    scanf("%s", player2Name);

    if (mode == 'T' || mode == 't') {
        tournamentMode(size, player1Name, player2Name);
    }
else {
        timeAttackMode(size, player1Name, player2Name);
    }
   
    return 0;
}

void displayBoard(char board[5][5], int size) {
    printf("\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf(" %c ", board[i][j]);
            if (j < size - 1) {
                printf("|");
            }
        }
        printf("\n");
        if (i < size - 1) {
            printLine(size);
        }
    }
    printf("\n");
}

void printLine(int size) {
    for (int j = 0; j < size; j++) {
        printf("---");
        if (j < size - 1) {
            printf("+");
        }
    }
    printf("\n");
}

int checkWinner(char board[5][5], int size) {
    for (int i = 0; i < size; i++) {
        int rowWin = 1;
        for (int j = 1; j < size; j++) {
            if (board[i][j] != board[i][0] || board[i][j] == ' ') {
                rowWin = 0;
                break;
            }
        }
        if (rowWin) return 1;

        int colWin = 1;
        for (int j = 1; j < size; j++) {
            if (board[j][i] != board[0][i] || board[j][i] == ' ') {
                colWin = 0;
                break;
            }
        }
        if (colWin) return 1;
    }

    int diag1Win = 1, diag2Win = 1;
    for (int i = 1; i < size; i++) {
        if (board[i][i] != board[0][0] || board[i][i] == ' ') {
            diag1Win = 0;
        }
        if (board[i][size - i - 1] != board[0][size - 1] || board[i][size - i - 1] == ' ') {
            diag2Win = 0;
        }
    }
    if (diag1Win || diag2Win) return 1;

    return 0;
}

int checkDraw(char board[5][5], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void timeAttackMode(int size, char *player1Name, char *player2Name) {
    char currentPlayer = 'X';
    int winner = 0;

    char board[5][5] = {{' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' '}, {' ', ' ', ' ', ' ', ' '}}; 

     displayBoard(board, size);
    while (!winner && !checkDraw(board, size)) {
       
        time_t startTime, endTime;
        double timeTaken;
        time(&startTime);

        int moveSuccess = makeMove(board, size, currentPlayer, (currentPlayer == 'X') ? player1Name : player2Name, 5);
        
        if (!moveSuccess) {
            printf("%s loses their turn for taking too long!\n", (currentPlayer == 'X') ? player1Name : player2Name);
        } else {
            time(&endTime);
            timeTaken = difftime(endTime, startTime);
            printf("Time taken for move: %.2f seconds\n", timeTaken);
        }

        winner = checkWinner(board, size);
         displayBoard(board, size);
        if (winner) {
            printf("Congratulations %s! You win the game.\n", (currentPlayer == 'X') ? player1Name : player2Name);
        } 
		
		else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }

    if (checkDraw(board, size)) {
        printf("It's a draw!\n");
    }
}

int makeMove(char board[5][5], int size, char currentPlayer, const char *playerName, int timeLimit) {
    int row, col;
    time_t startTime, endTime;
    double timeTaken;

    if (timeLimit > 0) {
        time(&startTime);
    }

    printf("%s's turn (%c). Enter row and column: ", playerName, currentPlayer);
    while (1) {
        if (scanf("%d %d", &row, &col) == 2) {
            if (row >= 0 && row < size && col >= 0 && col < size) {
                if (board[row][col] == ' ') {
                    if (timeLimit > 0) {
                        time(&endTime);
                        timeTaken = difftime(endTime, startTime);
                        if (timeTaken > timeLimit) {
                            printf("You took %.2f seconds, which exceeds the time limit! Turn skipped.\n", timeTaken);
                            return 0;
                        }
                    }
                    board[row][col] = currentPlayer;
                    return 1;
                } else {
                    printf("Invalid move! The spot is already occupied. Try again: ");
                }
            } else {
                printf("Invalid move! Out of bounds. Try again: ");
            }
        } else {
            printf("Invalid input! Enter two numbers separated by a space: ");
            fflush(stdin);
        }

        if (timeLimit > 0) {
            time(&endTime);
            timeTaken = difftime(endTime, startTime);
            if (timeTaken > timeLimit) {
                printf("You took %.2f seconds, which exceeds the time limit! Turn skipped.\n", timeTaken);
                return 0;
            }
        }
    }
}

void tournamentMode(int size, char *player1Name, char *player2Name) {
    int player1Wins = 0, player2Wins = 0;
    int rounds = 3;
    char currentPlayer;
    char board[5][5];

    for (int round = 1; round <= rounds; round++) {
        printf("\nRound %d:\n", round);
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                board[i][j] = ' ';
            }
        }

        currentPlayer = 'X';
        int winner = 0;
         displayBoard(board, size);
        while (!winner && !checkDraw(board, size)) {

            if (!makeMove(board, size, currentPlayer, (currentPlayer == 'X') ? player1Name : player2Name, 0)) {
                printf("%s loses their turn for taking too long!\n", (currentPlayer == 'X') ? player1Name : player2Name);
            } else {
                winner = checkWinner(board, size);
                 displayBoard(board, size);
                if (winner) {
                    printf("Congratulations %s! You win the round.\n", (currentPlayer == 'X') ? player1Name : player2Name);
                    if (currentPlayer == 'X') {
                        player1Wins++;
                    } else {
                        player2Wins++;
                    }
                }
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            }
        }

        if (checkDraw(board, size) && !winner) {
            printf("The round is a draw!\n");
        }
    }

    printf("\nTournament Results:\n");
    printf("%s: %d wins\n", player1Name, player1Wins);
    printf("%s: %d wins\n", player2Name, player2Wins);

    if (player1Wins > player2Wins) {
        printf("Congratulations %s, you are the Tournament Champion!\n", player1Name);
    } else if (player2Wins > player1Wins) {
        printf("Congratulations %s, you are the Tournament Champion!\n", player2Name);
    } else {
       printf("Well done! You both tried well! \nBut no one wins. \"IT'S A TIE\" \n");
    }
}