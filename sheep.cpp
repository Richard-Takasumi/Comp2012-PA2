#include "sheep.h"
#include "grass.h"
#include "helper.h"

/**
 * TODO: TASK 3
 * 
 * Place a copy of this Sheep onto nextGrid at the specified position.
 * You may implement this similar to Grass::putSelf(), and call setNextSelf() accordingly.
 * Hint: putAnimal() can be used.
*/
void Sheep::putSelf(Grid* nextGrid, const int x, const int y) {
    
}

/**
 * TODO: TASK 3
 * 
 * Place a brand new Sheep onto nextGrid at the specified position.
 * You may implement this similar to Grass::putClone().
 * Hint: putAnimal() can be used.
*/
void Sheep::putClone(Grid* nextGrid, const int x, const int y) const {
    
}

/**
 * TODO: TASK 3
 * 
 * Check if any adjacent cell of current Grid points to Grass.
 * If a Grass is found and has not been removed, destroy it using removeSelf(),
 * and reset the hungerCounter to full.
 * Exit from the function since a Sheep can only eat at most once per turn.
 * 
 * The code has been partially completed so that adjacent cells are checked in the order of adjacency index.
*/
void Sheep::eat(Grid* nextGrid) {
    for (int i=0; i<9; ++i) {
        if (i == 4) continue;
        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        Entity* adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);

        if (!adjEntity) {
            // Out of bounds or empty space, ignore
            continue;
        }

        // ?
    }
}

/**
 * TODO: TASK 3
 * 
 * Check if any adjacent cell of current Grid points to Sheep.
 * If a Sheep is found, try to spawn a new Sheep on an adjacent cell.
 * You can use the getRandomMovementIndex() function to get an available adjacent cell.
 * If a cell is found, spawn a new Sheep at that position and reset the breedCounter to full.
 * Exit from the function since a Sheep can only breed at most once per turn.
 * 
 * The code has been partially completed so that adjacent cells are checked in the order of adjacency index.
*/
void Sheep::breed(Grid* nextGrid) {
    for (int i=0; i<9; ++i) {
        if (i == 4) continue;
        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        Entity* adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);

        if (!adjEntity) {
            // Out of bounds or empty space, ignore
            continue;
        }

        // ?
    }
}

/**
 * TODO: TASK 3
 * 
 * Get a random available adjacent cell to move to using getRandomMovementIndex().
 * If there is an adjacent cell, place the copy of this Sheep there.
 * Otherwise, place it in the current position.
*/
void Sheep::move(Grid* nextGrid) {
    
}