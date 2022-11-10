#include <iostream>
#include "board.h"
#include "entity.h"

using namespace std;

/**
 * Grid functions
 */

Grid::~Grid() {
    for (int x=0; x<BOARD_SIZE_W; ++x) {
        for (int y=0; y<BOARD_SIZE_H; ++y) {
            delete cell[x][y];
        }
    }
}

bool Grid::outOfBounds(const int x, const int y) const {
    return x < 0 || x >= BOARD_SIZE_W || y < 0 || y >= BOARD_SIZE_H;
}

Entity* Grid::getCell(const int x, const int y) const {
    if (outOfBounds(x, y)) {
        // Out of bounds, return nullptr
        return nullptr;
    }
    return cell[x][y];
}

void Grid::setCell(Entity* entity, const int x, const int y) {
    if (outOfBounds(x, y)) {
        // Out of bounds, delete the entity
        delete entity;
        return;
    }
    delete cell[x][y];
    entity->setX(x);
    entity->setY(y);
    cell[x][y] = entity;
}

void Grid::deleteCell(const int x, const int y) {
    if (outOfBounds(x, y)) {
        // Out of bounds, do nothing
        return;
    }
    delete cell[x][y];
    cell[x][y] = nullptr;
}

/**
 * Board functions
 */

void Board::updateStep() {
    ++curStep;

    Grid* nextGrid = new Grid{};

    // Update every cells and put the next board state to nextGrid
    for (int x=0; x<BOARD_SIZE_W; ++x) {
        for (int y=0; y<BOARD_SIZE_H; ++y) {
            if (grid->getCell(x, y)) {
                // Cell is not empty, perform update() if entity is not already removed
                if (!grid->getCell(x, y)->isRemoved())
                    grid->getCell(x, y)->update(nextGrid);
            }
        }
    }

    // Delete the old grid
    delete grid;

    // Set nextGrid to current board
    grid = nextGrid;
}

void Board::updateSteps(const int numSteps) {
    for (int i=0; i<numSteps; ++i) {
        updateStep();
    }
}

void Board::updateTill(const int stepToUpdateTo) {
    while (curStep < stepToUpdateTo) {
        updateStep();
    }
}

void Board::print() const {
    cout << "Current step: " << curStep << endl;

    int entityCount = 0;

    for (int x=-1; x<BOARD_SIZE_W+1; ++x) cout << "=";
    cout << endl;

    for (int y=0; y<BOARD_SIZE_H; ++y) {
        cout << "|";
        for (int x=0; x<BOARD_SIZE_W; ++x) {
            if (grid->getCell(x, y)) {
                cout << grid->getCell(x, y)->toChar();
                ++entityCount;
            }
            else {
                // This is empty space
                cout << ' ';
            }
        }
        cout << "|" << endl;
    }

    for (int x=-1; x<BOARD_SIZE_W+1; ++x) cout << "=";
    cout << endl;

    cout << "Total Entity count: " << totalEntityCount << endl;
    cout << "Entity count: " << entityCount << endl;
}