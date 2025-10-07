#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <random>  // For modern C++ random number generation

// Platform-specific headers for non-blocking input
#ifndef _WIN32
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#endif

#include "helloEx.h" // for printLine
#include "snake_gameEx.h"

// --- Terminal Control Functions (for non-blocking input on macOS/Linux) ---

#ifndef _WIN32
static struct termios old_tio, new_tio;

static void init_terminal() {
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

static void restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

static int kbhit() {
    struct timeval tv;
    fd_set rdfs;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);
    select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &rdfs);
}
#endif

class SnakeGame {
private:
    const int BOARD_WIDTH = 20;
    const int BOARD_HEIGHT = 20;

    struct Point {
        int x, y;
    };

    enum class Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

    bool gameOver;
    Direction dir;
    std::vector<Point> snake;
    Point fruit;
    int score;

    // Modern C++ random number generation
    std::mt19937 rng;
    std::uniform_int_distribution<int> distX;
    std::uniform_int_distribution<int> distY;

    void PlaceFruit() {
        fruit.x = distX(rng);
        fruit.y = distY(rng);
    }

public:
    SnakeGame() : rng(std::time(nullptr)),
                  distX(0, BOARD_WIDTH - 1),
                  distY(0, BOARD_HEIGHT - 1) {
        Setup();
    }

    void Setup() {
        gameOver = false;
        dir = Direction::STOP;
        snake.clear();
        snake.push_back({BOARD_WIDTH / 2, BOARD_HEIGHT / 2});
        PlaceFruit();
        score = 0;
    }

    void Draw() {
        // 1. Create a 2D buffer for the game board.
        std::vector<std::string> board(BOARD_HEIGHT, std::string(BOARD_WIDTH, ' '));

        // 2. Draw the game elements onto the buffer.
        // Draw fruit
        board[fruit.y][fruit.x] = 'F';

        // Draw snake body
        for (size_t i = 1; i < snake.size(); ++i) {
            board[snake[i].y][snake[i].x] = 'o';
        }

        // Draw snake head
        board[snake[0].y][snake[0].x] = 'O';

        // 3. Clear the console and print the entire frame at once.
        std::cout << "\033[2J\033[1;1H" << std::flush;

        for (int i = 0; i < BOARD_WIDTH + 2; i++) std::cout << "#";
        std::cout << std::endl;

        for (int i = 0; i < BOARD_HEIGHT; i++) {
            std::cout << "#" << board[i] << "#" << std::endl;
        }

        for (int i = 0; i < BOARD_WIDTH + 2; i++) std::cout << "#";
        std::cout << std::endl;

        std::cout << "Score: " << score << std::endl;
        std::cout << "Use W, A, S, D to move. Press X to quit." << std::endl;
    }

    void Input() {
    #ifndef _WIN32
        if (kbhit()) {
            char c = getchar();
            switch (c) {
                case 'a': if (dir != Direction::RIGHT) dir = Direction::LEFT; break;
                case 'd': if (dir != Direction::LEFT) dir = Direction::RIGHT; break;
                case 'w': if (dir != Direction::DOWN) dir = Direction::UP; break;
                case 's': if (dir != Direction::UP) dir = Direction::DOWN; break;
                case 'x': gameOver = true; break;
            }
        }
    #endif
    }

    void Logic() {
        if (dir == Direction::STOP) return;

        Point prev = snake[0];
        Point prev2;
        for (size_t i = 1; i < snake.size(); i++) {
            prev2 = snake[i];
            snake[i] = prev;
            prev = prev2;
        }

        switch (dir) {
            case Direction::LEFT:  snake[0].x--; break;
            case Direction::RIGHT: snake[0].x++; break;
            case Direction::UP:    snake[0].y--; break;
            case Direction::DOWN:  snake[0].y++; break;
            default: break;
        }

        if (snake[0].x >= BOARD_WIDTH || snake[0].x < 0 || snake[0].y >= BOARD_HEIGHT || snake[0].y < 0) {
            gameOver = true;
        }

        for (size_t i = 1; i < snake.size(); i++) {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                gameOver = true;
            }
        }

        if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
            score += 10;
            PlaceFruit();
            snake.push_back(prev);
        }
    }

    void Run() {
    #ifndef _WIN32
        init_terminal();
    #endif

        while (!gameOver) {
            Draw();
            Input();
            Logic();
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }

    #ifndef _WIN32
        restore_terminal();
    #endif

        std::cout << "\nGame Over!" << std::endl;
        std::cout << "Final Score: " << score << std::endl;
    }
};

void snake_gameEx(void) {
    printLine("Snake Game Example");
    std::cout << "Starting game..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    SnakeGame game;
    game.Run();
}