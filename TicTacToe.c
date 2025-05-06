#include <stdio.h>
#include <string.h>

#define SIZE 3

void printBoard(char board[SIZE][SIZE]) 
{
    printf("\n    1   2   3\n");
    for (int i = 0; i < SIZE; i++) 
    {
        printf("  -------------\n");
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++) 
        {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }
    printf("  -------------\n");
}

int checkWinner(char board[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    return 0;
}

int isDraw(char board[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

void playGame() 
{
    char board[SIZE][SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    char player1[50], player2[50];
    char currentPlayerSymbol = 'X';
    char currentPlayerName[50];
    int row, col, winner = 0;

    printf("Enter Player 1 name: ");
    scanf("%s", player1);
    printf("Enter Player 2 name: ");
    scanf("%s", player2);

    printf("\n╔════════════════════════════════════════════╗\n");
    printf("║ 🎮 %s is 'X'  vs  %s is 'O'           ║\n", player1, player2);
    printf("╚════════════════════════════════════════════╝\n");

    while (!winner && !isDraw(board)) 
    {
        printBoard(board);
        strcpy(currentPlayerName, (currentPlayerSymbol == 'X') ? player1 : player2);

        printf("\n%s (%c), enter your move (row column): ", currentPlayerName, currentPlayerSymbol);
        scanf("%d %d", &row, &col);

        if (row >= 1 && row <= SIZE && col >= 1 && col <= SIZE && board[row - 1][col - 1] == ' ') 
        {
            board[row - 1][col - 1] = currentPlayerSymbol;
            winner = checkWinner(board);
            currentPlayerSymbol = (currentPlayerSymbol == 'X') ? 'O' : 'X';
        } 
        else 
        {
            printf("\n❌ Invalid move! Please try again.\n");
        }
    }

    printBoard(board);

    printf("\n╔════════════════════════════════════╗\n");
    if (winner) 
    {
        strcpy(currentPlayerName, (winner == 'X') ? player1 : player2);
        printf("║ 🎉 %s wins the game! 🏆          ║\n", currentPlayerName);
    } 
    else 
    {
        printf("║ 🤝 It's a draw! Well played both!  ║\n");
    }
    printf("╚════════════════════════════════════╝\n");
}

int main() 
{
    printf("╔════════════════════════════════════╗\n");
    printf("║      🧠 Welcome to Tic Tac Toe     ║\n");
    printf("╚════════════════════════════════════╝\n");

    playGame();
    return 0;
}
