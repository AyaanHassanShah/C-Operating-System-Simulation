#include <stdio.h>

#define SIZE 3

void printBoard(char board[SIZE][SIZE]) 
{
    printf("\n");
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---|---|---\n");
    }
    printf("\n");
}

int checkWinner(char board[SIZE][SIZE]) 
{
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) 
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];
    // No winner
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
    char currentPlayer = 'X';
    int row, col, winner = 0;

    while (!winner && !isDraw(board)) 
    {
        printBoard(board);
        printf("Player %c, enter your move (row and column): ", currentPlayer);
        scanf("%d %d", &row, &col);

        if (row >= 1 && row <= SIZE && col >= 1 && col <= SIZE && board[row - 1][col - 1] == ' ') 
        {
            board[row - 1][col - 1] = currentPlayer;
            winner = checkWinner(board);
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        } 
        else 
        {
            printf("Invalid move. Try again.\n");
        }
    }

    printBoard(board);
    if (winner) 
    {
        printf("Player %c wins!\n", winner);
    } 
    else 
    {
        printf("It's a draw!\n");
    }
}

int main() 
{
    printf("Welcome to Tic Tac Toe!\n");
    playGame();
    return 0;
}