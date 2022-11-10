#include "grass.h"
#include "helper.h"

/**
 * TODO: TASK 1
 * 
 * This function tries to set nextGrid's cell at position x, y to point to grass,
 * and returns a boolean of whether grass was placed successfully on nextGrid.
 * 
 * If the position is out of bounds or the cell is already pointing at another Entity,
 * grass should be deleted and the function returns false.
 * Otherwise, modify nextGrid accordingly and return true.
*/
bool putGrass(Grass* grass, Grid* nextGrid, const int x, const int y) {
    
    // CASE 1:
    // x, y are NOT out of bounds AND the cell is NOT occupied
    if (!nextGrid->outOfBounds(x,y) && nextGrid->getCell(x,y) == nullptr) {
        nextGrid->setCell(grass, x, y);  
        return true; 
    }

    return false;
}

/**
 * TODO: TASK 1
 * 
 * Place a copy of this Grass onto nextGrid at the specified position.
 * 
 * You should use the copy constructor to create a Grass object representing this Grass in the next step.
 * You may use putGrass() implemented above. If the copy was placed successfully, call setNextSelf()
 * to properly link this Grass with the copy for deletion if necessary.
*/
void Grass::putSelf(Grid* nextGrid, const int x, const int y) {


    Grass* grass_copy = new Grass(*this);
    if (putGrass(grass_copy, nextGrid, x, y)) {
        this->setNextSelf(grass_copy);
    } else {
        delete grass_copy;
    }
    

}

/**
 * TODO: TASK 1
 * 
 * Place a brand new Grass onto nextGrid at the specified position.
 * 
 * You should use the normal constructor to create a new Grass object.
 * You may use putGrass() implemented above.
*/
void Grass::putClone(Grid* nextGrid, const int x, const int y) const {
    Grass* new_grass = new Grass(this->getBoard());
    if (putGrass(new_grass, nextGrid, x, y) == false) {
        delete new_grass;
    }

}

/**
 * TODO: TASK 1
 * 
 * Update the nextGrid according to the update rules of Grass. 
 * If the spread countdown is reached, spawn 4 Grasses onto the orthogonally adjacent tiles using putClone().
 * You may find the countdown() function in helper.cpp useful.
 * Otherwise, put a copy of this Grass onto this position using putSelf(). You don't need to worry about
 * checking if current cell has another Entity; it is done in putGrass().
*/
void Grass::update(Grid* nextGrid) {
    if (countdown(this->spreadCounter, this->getSpreadCooldown())) {
        int adjX_up = getX() + getAdjX(3);
        int adjY_up = getY() + getAdjY(3);
        this->putClone(nextGrid, adjX_up, adjY_up);

        int adjX_down = getX() + getAdjX(5);
        int adjY_down = getY() + getAdjY(5);
        this->putClone(nextGrid, adjX_down, adjY_down);

        int adjX_left = getX() + getAdjX(1);
        int adjY_left = getY() + getAdjY(1);
        this->putClone(nextGrid, adjX_left, adjY_left);

        int adjX_right = getX() + getAdjX(7);
        int adjY_right = getY() + getAdjY(7);
        this->putClone(nextGrid, adjX_right, adjY_right);

        //place copy on x, y of nextgrid
        this->putSelf(nextGrid, this->getX(), this->getY());

        // Place copy of grass on x,y of itself
        // place grass on all four sides

    } else {
        // Just place copy of grass on x, y of itself
        this->putSelf(nextGrid, this->getX(), this->getY());
    }

}