#include <iostream>

#include "board.h"
#include "grass.h"
#include "sheep.h"
#include "wolf.h"

int main() {
    Board board;

    char input[BOARD_SIZE_W+2+5]; // leave some reserved space
    std::cin.getline(input, sizeof(input));
    for (int i = 0; i < BOARD_SIZE_W+2; ++i) {
        if (input[i] != '=') {
            std::cout << "Invalid input file (upper border not detected)." << std::endl;
            return 0;
        }
    }
    
    for (int y = 0; y < BOARD_SIZE_H; ++y) {
        std::cin.getline(input, sizeof(input));
        if (input[0] != '|') {
            std::cout << "Invalid input file (left border not detected)." << std::endl;
            return 0;
        }
        for (int x = 0; x < BOARD_SIZE_W; ++x) {
            switch (input[x+1]) {
                case ' ':
                    // Empty cell, do nothing
                    break;
                case '.':
                    board.getGrid()->setCell(new Grass(&board), x, y);
                    break;
                case 'S':
                    board.getGrid()->setCell(new Sheep(&board), x, y);
                    break;
                case 'W':
                    board.getGrid()->setCell(new Wolf(&board), x, y);
                    break;
                default:
                    std::cout << "Invalid input file (Unrecognized cell character)." << std::endl;
                    return 0;
            }
        }
        if (input[BOARD_SIZE_W+1] != '|') {
            std::cout << "Invalid input file (right border not detected)." << std::endl;
            return 0;
        }
    }

    std::cin.getline(input, sizeof(input));
    for (int i = 0; i < BOARD_SIZE_W+2; ++i) {
        if (input[i] != '=') {
            std::cout << "Invalid input file (lower border not detected)." << std::endl;
            return 0;
        }
    }

    int numSteps;
    std::cin >> numSteps;

    board.updateSteps(numSteps);
    board.print();

    return 0;
}