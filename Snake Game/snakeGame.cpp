//
// Created by Samuel Agyakwa on 3/27/2020.
//

#include "snakeGame.h"

SnakeGame::eDirection dir;

// Random Number Generator
unsigned short int
SnakeGame::generateRandomNumberBetween(const unsigned short int& numberFrom, const unsigned short int& numberTo) {
    std::random_device dev;
    std::mt19937_64 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(numberFrom,
        numberTo - 1); // distribution in range [unsigned short, unsigned short]
    return dist6(rng);
}

void SnakeGame::setTextXY(const unsigned short int& xCoord, const unsigned short int& yCoord, const char* toBuffer, const int& timesToBlink, const unsigned short int& delayInMilliSeconds) {
    clearScreen();
    COORD coord;

    coord.X = xCoord;
    coord.Y = yCoord;

    std::size_t len = strlen(toBuffer); //using size_t to prevent data loss
    char* p = new char[len + 1];
    memset(p, 32, len);
    p[len] = '\0';

    if (timesToBlink > 0)
        for (short int i = 0; i < timesToBlink; i++) {

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

            std::cout << p;

            ::Sleep(300);

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

            std::cout << toBuffer;

            ::Sleep(delayInMilliSeconds);
        }

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    std::cout << p;
    std::cout << toBuffer;
}

void SnakeGame::setUp() {
    gameOver = false;
    dir = eDirection::STOP;
    x = width / 2;
    y = height / 2;
    targetX = generateRandomNumberBetween(0, width);
    targetY = generateRandomNumberBetween(0, height);
    score = 0;
}

void SnakeGame::draw() {

    clearScreen();
    for (short int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;

    for (short int i = 0; i < height; i++) {
        for (short int j = 0; j < width; j++) {
            if (j == 0)
                std::cout << "#";
            if (i == y && j == x)
                std::cout << "O";
            else if (i == targetY && j == targetX)
                std::cout << "X";
            else {
                bool print = false;
                for (short int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "+";
                        print = true;
                    }
                }
                if (!print)
                    std::cout << " ";
            }

            if (j == width - 1)
                std::cout << "#";
        }
        std::cout << std::endl;
    }

    for (short int i = 0; i < width + 2; i++)
        std::cout << "#";
    std::cout << std::endl;
    std::cout << "Score:" << score << std::endl;
    std::cout << "Controls: A S W D" << std::endl;
    std::cout << "Instructions: You are O. Eat X to gain length. Press x to quit." << std::endl;
}

void SnakeGame::takeInput() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            dir = eDirection::LEFT;
            break;
        case 'd':
            dir = eDirection::RIGHT;
            break;
        case 'w':
            dir = eDirection::UP;
            break;
        case 's':
            dir = eDirection::DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void SnakeGame::snakeAlgorithm() {
    // On every new iteration, we store the previous position of the head and save it to prevX, prevY.
    // When we update array with snake's parts positions (tailX, tailY get new head coordinates).
    // After that for each number in arrays except the first ones, we make changes.
    // We save tailX[i], tailY[i] to prevX2, prevY2 and make tailX[i] and tailY[i] equal to prevX, prevY.
    // Then make prevX, prevY equal to prevX2, prevY2.

    unsigned short int prevX = tailX[0];
    unsigned short int prevY = tailY[0];
    unsigned short int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (short int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case eDirection::LEFT:
        x--;
        break;
    case eDirection::RIGHT:
        x++;
        break;
    case eDirection::UP:
        y--;
        break;
    case eDirection::DOWN:
        y++;
        break;
    default:
        break;
    }
    //if (x > width || x < 0 || y > height || y < 0)
    //	gameOver = true;
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (short int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == targetX && y == targetY) {
        score += 10;
        targetX = generateRandomNumberBetween(0, width);
        targetY = generateRandomNumberBetween(0, height);
        nTail++;
    }
}

void SnakeGame::clearScreen() {
    // Function which cleans the screen without flickering
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void SnakeGame::hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void SnakeGame::setConsoleXY(const unsigned short int& width, const unsigned short int& height) {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); //stores the console's current dimensions

    MoveWindow(console, r.left, r.top, width, height, TRUE); // 800 width, 100 height
}

void SnakeGame::startGame() {
    setConsoleXY(700, 535);
    setUp();
    hideCursor();
    while (!gameOver) {
        draw();
        takeInput();
        snakeAlgorithm();
        Sleep(1); //sleep(10);
    }
    clearScreen();
    const char gameOverBuff[] = "GAME OVER!";
    setTextXY(33, 12, gameOverBuff, 6, 1000);
}

