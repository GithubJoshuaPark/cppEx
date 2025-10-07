#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <string>
#include <random> // For modern C++ random number generation

// Platform-specific headers for non-blocking input and screen clearing
#ifndef _WIN32
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>
#endif

#include "helloEx.h" // for printLine
#include "tetris_gameEx.h"


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

// --- Tetris Game Class ---

class TetrisGame {
private:
    const int BOARD_WIDTH = 12;
    const int BOARD_HEIGHT = 22;
    std::vector<std::string> board;

    // Tetromino shapes (4 rotations for each)
    std::vector<std::string> tetrominoes;

    // Game state
    bool gameOver;
    int currentPiece;
    int currentRotation;
    int currentX;
    int currentY;
    int score;
    int speed;
    int speedCounter;
    bool forceDown;
    std::vector<int> lines;

    // Modern C++ random number generation
    std::mt19937 rng;
    std::uniform_int_distribution<int> pieceDist;

    // Rotates a piece within its 4x4 grid
    int Rotate(int px, int py, int r) {
        switch (r % 4) {
            case 0: return py * 4 + px;         // 0 degrees
            case 1: return 12 + py - (px * 4);  // 90 degrees
            case 2: return 15 - (py * 4) - px;  // 180 degrees
            case 3: return 3 - py + (px * 4);   // 270 degrees
        }
        return 0;
    }

    // Collision detection
    bool DoesPieceFit(int piece, int rotation, int posX, int posY) {
        for (int px = 0; px < 4; px++) {
            for (int py = 0; py < 4; py++) {
                int pieceIndex = Rotate(px, py, rotation);
                int boardIndexX = posX + px;
                int boardIndexY = posY + py;

                if (tetrominoes[piece][pieceIndex] == 'X') {
                    // Check if out of bounds
                    if (boardIndexX < 0 || boardIndexX >= BOARD_WIDTH || boardIndexY >= BOARD_HEIGHT) {
                        return false;
                    }
                    // Check for collision with existing pieces on the board
                    if (boardIndexY >= 0 && board[boardIndexY][boardIndexX] != L' ') {
                        return false;
                    }
                }
            }
        }
        return true;
    }

public:
    TetrisGame() : rng(std::time(nullptr)), pieceDist(0, 6) {
        // Initialize board
        board.resize(BOARD_HEIGHT, std::string(BOARD_WIDTH, ' '));
        for (int i = 0; i < BOARD_HEIGHT - 1; ++i) {
            board[i] = " " + std::string(BOARD_WIDTH - 2, ' ') + " ";
        }
        board[BOARD_HEIGHT - 1] = std::string(BOARD_WIDTH, '=');

        // Initialize tetrominoes
        tetrominoes.resize(7);
        tetrominoes[0] = "..X...X...X...X."; // I
        tetrominoes[1] = "..X..XX...X....."; // T
        tetrominoes[2] = ".....XX..XX....."; // O
        tetrominoes[3] = ".X...X...XX....."; // L
        tetrominoes[4] = "..X...X..XX....."; // J
        tetrominoes[5] = ".X...XX...X....."; // S
        tetrominoes[6] = "..X..XX..X......"; // Z

        Setup();
    }

    void Setup() {
        gameOver = false;
        currentPiece = pieceDist(rng);
        currentRotation = 0;
        currentX = BOARD_WIDTH / 2 - 2;
        currentY = 0;
        score = 0;
        speed = 20;
        speedCounter = 0;
        forceDown = false;
        lines.clear();
    }

    void Draw() {
        // Create a screen buffer to draw on
        std::vector<std::string> screen = board;

        // Draw current piece onto the screen buffer
        for (int px = 0; px < 4; px++) {
            for (int py = 0; py < 4; py++) {
                if (tetrominoes[currentPiece][Rotate(px, py, currentRotation)] == 'X') {
                    screen[currentY + py][currentX + px] = '#';
                }
            }
        }

        // Display the completed frame
        std::cout << "\033[2J\033[1;1H" << std::flush;
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            std::cout << screen[i] << std::endl;
        }
        std::cout << "Score: " << score << std::endl;
        std::cout << "Use W(Rotate), A(Left), S(Down), D(Right). Press X to quit." << std::endl;
    }

    void Run() {
    #ifndef _WIN32
        init_terminal();
    #endif

        while (!gameOver) {
            // Game Timing
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            speedCounter++;
            forceDown = (speedCounter == speed);

            // Input
            #ifndef _WIN32
            if (kbhit()) {
                char c = getchar();
                if(c) system("afplay eat.wav &");
                switch (c) {                    
                    case 'a': if (DoesPieceFit(currentPiece, currentRotation, currentX - 1, currentY)) currentX--; break;
                    case 'd': if (DoesPieceFit(currentPiece, currentRotation, currentX + 1, currentY)) currentX++; break;
                    case 's': if (DoesPieceFit(currentPiece, currentRotation, currentX, currentY + 1)) currentY++; break;
                    case 'w': if (DoesPieceFit(currentPiece, currentRotation + 1, currentX, currentY)) currentRotation++; break;
                    case 'x': gameOver = true; break;
                }                
            }
            #endif

            // Logic
            if (forceDown) {
                speedCounter = 0;
                if (DoesPieceFit(currentPiece, currentRotation, currentX, currentY + 1)) {
                    currentY++;
                } else {
                    // Lock the piece
                    for (int px = 0; px < 4; px++) {
                        for (int py = 0; py < 4; py++) {
                            if (tetrominoes[currentPiece][Rotate(px, py, currentRotation)] == 'X') {
                                board[currentY + py][currentX + px] = '#';
                            }
                        }
                    }

                    // Check for completed lines
                    for (int py = 0; py < 4; py++) {
                        if (currentY + py < BOARD_HEIGHT - 1) {
                            bool line = true;
                            for (int px = 1; px < BOARD_WIDTH - 1; px++) {
                                if (board[currentY + py][px] == ' ') {
                                    line = false;
                                    break;
                                }
                            }
                            if (line) {
                                for (int px = 1; px < BOARD_WIDTH - 1; px++) {
                                    board[currentY + py][px] = '=';
                                }
                                lines.push_back(currentY + py);
                            }
                        }
                    }
                    
                    system("afplay gameover.wav &");
                    score += 25;
                    if (!lines.empty()) score += (1 << lines.size()) * 100;

                    // Choose next piece
                    currentX = BOARD_WIDTH / 2 - 2;
                    currentY = 0;
                    currentRotation = 0;
                    currentPiece = pieceDist(rng);

                    // If piece does not fit, game over
                    gameOver = !DoesPieceFit(currentPiece, currentRotation, currentX, currentY);
                }
            }

            // Draw
            Draw();

            // Handle line clearing animation
            if (!lines.empty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(400));
                for (auto &v : lines) {
                    for (int px = 1; px < BOARD_WIDTH - 1; px++) {
                        for (int py = v; py > 0; py--) {
                            board[py][px] = board[py - 1][px];
                        }
                        board[0][px] = ' ';
                    }
                }
                lines.clear();
            }
        }

    #ifndef _WIN32
        restore_terminal();
    #endif
        system("afplay gameover.wav &");
        std::cout << "\nGame Over!" << std::endl;
        std::cout << "Final Score: " << score << std::endl;
    }
};

void tetris_gameEx(void) {
    printLine("Tetris Game Example");
    std::cout << "Starting game..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    TetrisGame game;
    game.Run();
}