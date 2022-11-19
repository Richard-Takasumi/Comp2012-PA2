#include "animal.h"
#include "grass.h"
#include "helper.h"

/**
 * TODO: TASK 2
 * 
 * This function tries to set nextGrid's cell at position x, y to point to animal,
 * and returns a boolean of whether animal was placed successfully on nextGrid.
 * 
 * You can implement this similar to putGrass() in Task 1. However, if the current cell in nextGrid
 * is pointing to Grass, allow the animal to be placed there by calling deleteCell().
 * No need to worry about deleting the original Grass (if any).
 * Otherwise, if current cell contains an Animal, delete the passed animal and return false.
*/
bool Animal::putAnimal(Animal* animal, Grid* nextGrid, const int x, const int y) const {


    // if not out of bounds, and the cell is empty OR a grass
    if (!nextGrid->outOfBounds(x,y) && (nextGrid->getCell(x,y) == nullptr || nextGrid->getCell(x, y)->toChar() == '.')) {
        
        // set cell will delete the cell if it's grass anyway, so no need to call deleteCell()
        nextGrid->setCell(animal, x, y);  
        return true; 
    } else {
        // if the animal should not be put there, we must delete animal parameter because
        // in order to call putAnimal function we must create a new animal, which won't be used.
        delete animal;
    }
    
    return false;
}

/**
 * Choose a random cell from one of the 8 adjacent cells that does not contain an animal in current Grid or next Grid.
 * Returns an index number corresponding to one of the 8 adjacent cells:
 * 
 * 0 3 6
 * 1 _ 7
 * 2 5 8
 * 
 * If no tiles are available, returns -1.
*/
int Animal::getRandomMovementIndex(Grid* nextGrid) const {
    int numPossibleCells = 0;
    bool indexCandidate[9];
    for (int i=0; i<9; ++i) {
        indexCandidate[i] = false;
        if (i == 4) continue;

        int adjX = getX() + getAdjX(i);
        int adjY = getY() + getAdjY(i);
        if (nextGrid->outOfBounds(adjX, adjY)) {
            // Out of bounds, ignore
            continue;
        }

        Entity* adjEntity = getBoard()->getGrid()->getCell(adjX, adjY);
        if (dynamic_cast<Animal*>(adjEntity)) {
            // Adjacent cell is an animal, cannot move over
            continue;
        }

        Entity* adjNextEntity = nextGrid->getCell(adjX, adjY);
        if (dynamic_cast<Animal*>(adjNextEntity)) {
            // Adjacent cell in next grid has an animal, cannot move over
            continue;
        }

        // Found a place to move to
        ++numPossibleCells;
        indexCandidate[i] = true;
    }
    if (numPossibleCells > 0) {
        // Use a custom made random function to be consistent
        int randInd = pseudo_rand() % numPossibleCells;
        for (int i=0; i<9; ++i) {
            if (indexCandidate[i]) {
                if (randInd == 0) {
                    return i;
                }
                --randInd;
            }
        }
    }
    // No place to move to
    return -1;
}

/**
 * TODO: TASK 2
 * 
 * Implement the 3-stage update scheme of Animal. To ensure consistency, you should implement
 * the stages according to the below specifications. The code is partially completed to help with
 * following the specifications.
 * 
 * First, countdown the hungerCounter. If it reaches 0, the animal dies and the function can simply return.
 * Otherwise, call eat() to update the grid and hunger.
 * 
 * Next, if breedCounter is 1 and hungerCounter is more than 70% of maximum value, the animal tries to breed
 * by calling breed(). If breedCounter is greater than 1, do countdown instead.
 * 
 * Finally, countdown the moveCounter. If it reaches 0, call move() to move the animal. Otherwise, put the animal's
 * copy in its position.
*/
void Animal::update(Grid* nextGrid) {
    // If hunger reaches 0, the animal dies
    // Otherwise, the animal tries to eat
    if (countdown(hungerCounter, getHungerCooldown())) {
        // ?
        return;
    }
    else {
        eat(nextGrid);
        // ?
    }
  
    // Animal then tries to breed if breed cooldown has finished
    if (breedCounter == 1) {
        if (hungerCounter / static_cast<float>(getHungerCooldown()) > 0.7f) {
            // ?
            breed(nextGrid);
        }
    }
    else {
        countdown(breedCounter, getBreedCooldown());
    }

    // Animal finally moves if move cooldown is reached
    if (countdown(moveCounter, getMoveCooldown())) {
        // ?
        move(nextGrid);
    }
    else {
        // ?
        putSelf(nextGrid, getX(), getY());
    }
}