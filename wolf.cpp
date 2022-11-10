#include "wolf.h"
#include "sheep.h"
#include "grass.h"
#include "helper.h"

/**
 * TODO: TASK 4
 * 
 * Place a copy of this Wolf onto nextGrid at the specified position.
 * You may implement this similar to Sheep::putSelf().
*/
void Wolf::putSelf(Grid* nextGrid, const int x, const int y) {
    
}

/**
 * TODO: TASK 4
 * 
 * Place a brand new Wolf onto nextGrid at the specified position.
 * You may implement this similar to Sheep::putClone().
*/
void Wolf::putClone(Grid* nextGrid, const int x, const int y) const {
    
}

/**
 * TODO: TASK 4
 * 
 * Implement this function similar to Sheep::eat().
 * The only difference is that Wolf eats Sheep instead of Grass.
*/
void Wolf::eat(Grid* nextGrid) {
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
 * TODO: TASK 4
 * 
 * Implement this function similar to Sheep::breed().
 * The only difference is that Wolf breeds by finding a Wolf instead of Sheep.
*/
void Wolf::breed(Grid* nextGrid) {
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
 * TODO: TASK 4
 * 
 * If there is at least one Sheep on the board, Wolf tries to move towards it.
 * 
 * You should loop over the board in the same order as Board calling update(), 
 * calculate Euclidean distance to each cell containing a Sheep, and keep track of the shortest distance found.
 * Ignore sheeps that have been eaten (removed).
 * No need to keep track of Sheeps with the same distance as shortest one found so far.
 * 
 * If a Sheep is found, move to the adjacent cell closest to that Sheep. If that cell is occupied with another Animal,
 * the Wolf stays at its position.
 * 
 * If no Sheep is found, the Wolf moves randomly like a Sheep.
 * 
 * You may follow the structure below to implement the function.
*/
void Wolf::move(Grid* nextGrid) {
    // First, find a sheep to target
    
    // ?
    for (int x=0; x<BOARD_SIZE_W; ++x) {
        for (int y=0; y<BOARD_SIZE_H; ++y) {

            // ?

        }
    }

    if (false) { // Edit this line with the appropriate condition
        // If a sheep with the closest distance is found, try to move towards it
        
        // ?
    }
    else {
        // No sheep found, move randomly
        
        // ?
    }
}