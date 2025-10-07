#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <random>  // For modern C++ random number generation
#include <fstream> // For file I/O
#include <sstream> // For std::ostringstream
#include <iomanip> // For std::put_time

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

/**
 * @brief Terminal settings for non-blocking input.
 */
static struct termios old_tio, new_tio;

/**
 * @brief Initialize the terminal to read input without blocking and without echoing.
 * 게임 시작 전, 터미널을 "실시간 입력 모드"로 변경합니다. (Enter 없이, 화면에 표시 없이 키 입력 받기)
 * kbhit() 함수가 non-blocking 방식으로 키 입력을 감지할 수 있고, 
 * 사용자는 쾌적한 환경에서 스네이크 게임을 즐길 수 있게 됩
 */
static void init_terminal() {
    // 1. 현재 터미널의 설정을 'old_tio' 구조체에 저장합니다.
    tcgetattr(STDIN_FILENO, &old_tio);

    // 2. 새 설정을 위해 현재 설정을 복사합니다.
    new_tio = old_tio;

    // 3. 새 설정에서 두 가지 중요한 플래그를 끕니다.
    //    c_lflag는 터미널의 로컬 모드를 제어합니다.
    //    ~ (비트 NOT)과 & (비트 AND) 연산을 사용하여 특정 비트를 0으로 만듭니다.
    new_tio.c_lflag &= (~ICANON & ~ECHO);
    //    - ~ICANON: 정규 모드를 비활성화합니다. (Enter 없이 키 입력 즉시 받기)
    //    - ~ECHO:   입력된 문자를 화면에 표시하지 않습니다. (w, a, s, d가 화면에 안보이게 함)

    // 4. 변경된 새 설정(비정규모드)을 터미널에 즉시 적용합니다.
    // 비정규모드(row-mode)에서는 사용자가 키를 누르면 즉시 프로그램에 전달됩니다.
    // 또한, 입력된 문자가 화면에 표시되지 않습니다.
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
}

/**
 * @brief Restore the terminal settings to their original state.
 * 게임 종료 후, 터미널을 원래의 "일반 모드"로 되돌립니다.
 */
static void restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}

/**
 * @brief Gets the current system time as a formatted string.
 * @return A string representing the current timestamp (e.g., "YYYY-MM-DD HH:MM:SS").
 */
static std::string getCurrentTimestamp() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}


/**
 * @brief Saves the final score to "snake_game_recode.txt".
 * @param final_score The score to save.
 */
static void save_score(int final_score) {
    // Open the score file in append mode.
    std::ofstream score_file("snake_game_recode.txt", std::ios_base::app);
    if (score_file.is_open()) {
        score_file << "Date: " << getCurrentTimestamp() 
                   << ", Score: " << final_score << std::endl;
    }
}

/**
 * @brief Loads the high score from "snake_game_recode.txt".
 * @return The highest score found in the file, or 0 if no records exist.
 */
static int load_high_score() {
    std::ifstream score_file("snake_game_recode.txt");
    int high_score = 0;
    std::string line;

    if (score_file.is_open()) {
        while (std::getline(score_file, line)) {
            size_t pos = line.find("Score: ");
            if (pos != std::string::npos) {
                int score = std::stoi(line.substr(pos + 7));
                if (score > high_score) {
                    high_score = score;
                }
            }
        }
    }
    return high_score;
}


/**
 * @brief Check if a key has been pressed (non-blocking).
 * 키보드 버퍼에 사용자가 누른 키가 있는지 기다리지 않고 즉시 확인합니다
 * 눌린 키가 있으면 0이 아닌 값(보통 1)을 반환합니다.
 */
static int kbhit() {
    struct timeval tv;
    fd_set rdfs;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&rdfs);
    FD_SET(STDIN_FILENO, &rdfs);
    // select 함수는 지정된 시간(tv) 동안 파일 디스크립터(rdfs)의 상태 변화를 감시합니다.
    // 대기 시간을 0으로 설정했으므로, 기다리지 않고 즉시 상태를 확인하고 반환합니다.
    select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
    // FD_ISSET은 select 호출 후, STDIN_FILENO에 읽을 데이터(키 입력)가 있는지 확인합니다.
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
    std::uniform_int_distribution<int> distX;  // Range for x-coordinate
    std::uniform_int_distribution<int> distY;  // Range for y-coordinate

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

    void Draw(int high_score = 0) {
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

        std::cout << "High Score: " << high_score << std::endl;
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
            // The '&' at the end runs the command in the background so it doesn't block the game.
            system("afplay gameover.wav &");
            gameOver = true;
        }

        for (size_t i = 1; i < snake.size(); i++) {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
                system("afplay gameover.wav &");
                gameOver = true;
            }
        }

        if (snake[0].x == fruit.x && snake[0].y == fruit.y) {
            // The '&' at the end runs the command in the background so it doesn't block the game.
            system("afplay eat.wav &");
            score += 10;
            PlaceFruit();
            snake.push_back(prev);
        }
    }

    void Run(int high_score = 0) {
        if (high_score > 0) {
            std::cout << "Current High Score: " << high_score << std::endl;
        } else {
            std::cout << "No high score yet. Be the first to set one!" << std::endl;
        }
    #ifndef _WIN32
        init_terminal();
    #endif

        while (!gameOver) {
            Draw(high_score);
            Input();
            Logic();
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }

    #ifndef _WIN32
        restore_terminal();
    #endif

        std::cout << "\nGame Over!" << std::endl;
        std::cout << "Final Score: " << score << std::endl;

        // Save the score to the record file.
        save_score(score);
    }
};

void snake_gameEx(void) {
    printLine("Snake Game Example");

    int high_score = load_high_score();
    std::cout << "High Score: " << high_score << std::endl;

    std::cout << "Starting game..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    SnakeGame game;
    game.Run(high_score);
}