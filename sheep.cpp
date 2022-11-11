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

    Sheep* sheep_copy = new Sheep(*this);
    

    // putAnimal will delete sheep_copy if the put is unsuccessful
    if (putAnimal(sheep_copy, nextGrid, x, y)) {
        this->setNextSelf(sheep_copy);
    } 
    
}

/**
 * TODO: TASK 3
 * 
 * Place a brand new Sheep onto nextGrid at the specified position.
 * You may implement this similar to Grass::putClone().
 * Hint: putAnimal() can be used.
*/
void Sheep::putClone(Grid* nextGrid, const int x, const int y) const {
    Sheep* new_sheep = new Sheep(this->getBoard());
    // putAnimal will delete new_sheep if the put is unsuccessful
    putAnimal(new_sheep, nextGrid, x, y);
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

        // if adjEntity is grass, remove it from the next grid, then.... eat it?
        if (adjEntity->toChar() == '.' && !adjEntity->isRemoved()) {
            adjEntity->removeSelf(nextGrid);
            this->setHungerCounter(this->getHungerCooldown());
            return;
        }


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
        // if found a sheep, and the sheep is not removed? I don't think it hurts to check...
        if (adjEntity->toChar() == 'S' && !adjEntity->isRemoved()) {


            // random_index prequalifies the tile, meaning it is either grass or empty.
            int random_index = getRandomMovementIndex(nextGrid);
            // if no cells are available.
            if (random_index == -1) {
                return;
            }
            int put_baby_sheep_X = getX() + getAdjX(random_index);
            int put_baby_sheep_Y = getY() + getAdjY(random_index);

            putClone(nextGrid, put_baby_sheep_X, put_baby_sheep_Y);
            // reset breedCounter to MAX == breedCooldown();
            this->setBreedCounter(this->getBreedCooldown());
            return;

        }
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
    int random_index = getRandomMovementIndex(nextGrid);
    // if all adjacent tiles are full, just stay still.
    if (random_index == -1) {
        putSelf(nextGrid, this->getX(), this->getY());
        return;
    }


    int move_sheep_X = getX() + getAdjX(random_index);
    int move_sheep_Y = getY() + getAdjY(random_index);
    putSelf(nextGrid, move_sheep_X, move_sheep_Y);




    
}