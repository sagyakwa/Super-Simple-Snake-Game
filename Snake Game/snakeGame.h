//
// Created by Samuel Agyakwa on 3/27/2020.
//

#ifndef CPP_PRACTICE_SNAKEGAME_H
#define CPP_PRACTICE_SNAKEGAME_H
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <random>


class SnakeGame {
private:
    bool gameOver = false;
    const unsigned short int width = 80;
    const unsigned short int height = 25;
    short unsigned int x{}, y{}, score{};
    unsigned short int targetY{};
    unsigned short int targetX{};
    unsigned short int tailX[100]{}, tailY[100]{}; // snake coordinates
    short int nTail{};

    void setUp();
    void draw();
    void takeInput();
    void snakeAlgorithm();
    static void clearScreen();
    static void hideCursor();
    static void setConsoleXY(const unsigned short int&, const unsigned short int&);
    static void setTextXY(const unsigned short int&, const unsigned short int&, const char*, const int&, const unsigned short int&);
    static unsigned short int generateRandomNumberBetween(const unsigned short int&, const unsigned short int&);
public:
    void startGame();

    enum class eDirection {
        STOP = 0, LEFT, RIGHT, UP, DOWN
    };
};


#endif //CPP_PRACTICE_SNAKEGAME_H
