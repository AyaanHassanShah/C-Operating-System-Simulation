#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 20
#define INITIAL_LENGTH 3

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point pos[WIDTH * HEIGHT];
    int length;
    char direction;
} Snake;

Snake snake;
Point food;
int score = 0;

void gotoxy(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() 
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void setup() {
    // Center snake
    snake.length = INITIAL_LENGTH;
    for(int i = 0; i < snake.length; i++) {
        snake.pos[i].x = WIDTH/2;
        snake.pos[i].y = HEIGHT/2 + i;
    }
    snake.direction = 'U';
    
    // Place food
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;
}

// Replace existing draw() function
void draw() 
{
    gotoxy(0, 0);
    
    // Draw top wall
    for(int i = 0; i < WIDTH+2; i++) printf("#");
    printf("\n");
    
    // Draw game area
    for(int y = 0; y < HEIGHT; y++) {
        printf("#");
        for(int x = 0; x < WIDTH; x++) {
            int isSnake = 0;
            for(int i = 0; i < snake.length; i++) {
                if(snake.pos[i].x == x && snake.pos[i].y == y) {
                    printf("O");
                    isSnake = 1;
                    break;
                }
            }
            if(!isSnake) {
                printf(x == food.x && y == food.y ? "*" : " ");
            }
        }
        printf("#\n");
    }
    
    // Draw bottom wall
    for(int i = 0; i < WIDTH+2; i++) printf("#");
    printf("\nScore: %d", score);
}

void move() {
    // Move body
    for(int i = snake.length-1; i > 0; i--) {
        snake.pos[i] = snake.pos[i-1];
    }
    
    // Move head
    switch(snake.direction) {
        case 'U': snake.pos[0].y--; break;
        case 'D': snake.pos[0].y++; break;
        case 'L': snake.pos[0].x--; break;
        case 'R': snake.pos[0].x++; break;
    }
    
    // Check food
    if(snake.pos[0].x == food.x && snake.pos[0].y == food.y) {
        score += 10;
        snake.length++;
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;
    }
}

int game_over() {
    // Wall collision
    if(snake.pos[0].x < 0 || snake.pos[0].x >= WIDTH ||
       snake.pos[0].y < 0 || snake.pos[0].y >= HEIGHT)
        return 1;
        
    // Self collision
    for(int i = 1; i < snake.length; i++)
        if(snake.pos[0].x == snake.pos[i].x && 
           snake.pos[0].y == snake.pos[i].y)
            return 1;
            
    return 0;
}

// Modify main() function
int main() 
{
    system("cls");  // Clear screen once at start
    hideCursor();   // Hide cursor for clean look
    srand(time(NULL));
    setup();
    
    while(!game_over()) {
        draw();
        Sleep(50);  // Reduced delay for smoother movement
        
        if(_kbhit()) {
            switch(_getch()) {
                case 72: if(snake.direction != 'D') snake.direction = 'U'; break;
                case 80: if(snake.direction != 'U') snake.direction = 'D'; break;
                case 75: if(snake.direction != 'R') snake.direction = 'L'; break;
                case 77: if(snake.direction != 'L') snake.direction = 'R'; break;
                case 27: return 0;  // ESC to quit
            }
        }
        move();
    }
    
    gotoxy(0, HEIGHT + 3);  // Move cursor below game area
    printf("Game Over! Score: %d\n", score);
    printf("Press any key to exit...");
    _getch();
    return 0;
}
