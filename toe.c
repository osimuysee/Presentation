#include <stdio.h>
#include <string.h>

#define SIZE 3

// Function prototypes
void initializeBoard(char board[SIZE][SIZE]);
void printBoard(char board[SIZE][SIZE]);
int checkWin(char board[SIZE][SIZE], char mark);
int isBoardFull(char board[SIZE][SIZE]);
int makeMove(char board[SIZE][SIZE], int move, char mark);
void flushInput();

int main() {
    char board[SIZE][SIZE];
    char player1[50], player2[50];
    int score1 = 0, score2 = 0, draw = 0;
    char mark1 = 'X', mark2 = 'O';
    int currentPlayer, move, win;
    char playAgain;

    printf("Enter Player 1 name: ");
    fgets(player1, sizeof(player1), stdin);
    player1[strcspn(player1, "\n")] = 0;  // Remove newline

    printf("Enter Player 2 name: ");
    fgets(player2, sizeof(player2), stdin);
    player2[strcspn(player2, "\n")] = 0;

    do {
        initializeBoard(board);
        currentPlayer = 1;
        win = 0;

        while (1) {
            printBoard(board);
            if (currentPlayer == 1)
                printf("%s's turn (%c). Enter position (1-9): ", player1, mark1);
            else
                printf("%s's turn (%c). Enter position (1-9): ", player2, mark2);

            if (scanf("%d", &move) != 1) {
                printf("Invalid input. Please enter a number between 1 and 9.\n");
                flushInput();
                continue;
            }

            if (move < 1 || move > 9) {
                printf("Invalid move. Position must be between 1 and 9.\n");
                continue;
            }

            char currentMark = (currentPlayer == 1) ? mark1 : mark2;
            if (!makeMove(board, move, currentMark)) {
                printf("Position already taken. Try again.\n");
                continue;
            }

            if (checkWin(board, currentMark)) {
                printBoard(board);
                if (currentPlayer == 1) {
                    printf("Congratulations %s! You won this round.\n", player1);
                    score1++;
                } else {
                    printf("Congratulations %s! You won this round.\n", player2);
                    score2++;
                }
                win = 1;
                break;
            }

            if (isBoardFull(board)) {
                printBoard(board);
                printf("It's a draw!\n");
                draw++;
                break;
            }

            currentPlayer = (currentPlayer == 1) ? 2 : 1;
        }

        printf("\nScoreboard:\n");
        printf("%s: %d\n", player1, score1);
        printf("%s: %d\n", player2, score2);
        printf("Draws: %d\n", draw);

        printf("\nDo you want to play again? (y/n): ");
        flushInput();
        scanf("%c", &playAgain);

    } while (playAgain == 'y' || playAgain == 'Y');

    printf("\nFinal Score:\n");
    printf("%s: %d\n", player1, score1);
    printf("%s: %d\n", player2, score2);
    printf("Draws: %d\n", draw);

    printf("Thank you for playing!\n");
    return 0;
}

void initializeBoard(char board[SIZE][SIZE]) {
    char pos = '1';
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++)
            board[i][j] = pos++;
}

void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < SIZE - 1) printf("---+---+---\n");
    }
    printf("\n");
}

int checkWin(char board[SIZE][SIZE], char mark) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if ((board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) ||
            (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark))
            return 1;
    }
    // Check diagonals
    if ((board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) ||
        (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark))
        return 1;

    return 0;
}

int isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) 
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
    return 1;
}

int makeMove(char board[SIZE][SIZE], int move, char mark) {
    int row = (move - 1) / SIZE;
    int col = (move - 1) % SIZE;

    if (board[row][col] != 'X' && board[row][col] != 'O') {
        board[row][col] = mark;
        return 1;
    }
    return 0;
}

void flushInput() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
