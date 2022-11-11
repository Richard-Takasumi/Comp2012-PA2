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
    Wolf* wolf_copy = new Wolf(*this);

    // putAnimal will delete wolf_copy if the put is unsuccessful
    if (putAnimal(wolf_copy, nextGrid, x, y)) {
        this->setNextSelf(wolf_copy);
    } 
}

/**
 * TODO: TASK 4
 * 
 * Place a brand new Wolf onto nextGrid at the specified position.
 * You may implement this similar to Sheep::putClone().
*/
void Wolf::putClone(Grid* nextGrid, const int x, const int y) const {
    Wolf* new_wolf = new Wolf(this->getBoard());
    // putAnimal will delete new_sheep if the put is unsuccessful
    putAnimal(new_wolf, nextGrid, x, y);
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
        // if adjEntity is grass, remove it from the next grid, then.... eat it?
        if (adjEntity->toChar() == 'S' && !adjEntity->isRemoved()) {
            adjEntity->removeSelf(nextGrid);
            this->setHungerCounter(this->getHungerCooldown());
            return;
        }

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
        // if found a wolf, and the wolf is not removed? I don't think it hurts to check...
        if (adjEntity->toChar() == 'W' && !adjEntity->isRemoved()) {
            // random_index prequalifies the tile, meaning it is either grass or empty.
            int random_index = getRandomMovementIndex(nextGrid);
            // if no cells are available.
            if (random_index == -1) {
                return;
            }
            int put_baby_wolf_X = getX() + getAdjX(random_index);
            int put_baby_wolf_Y = getY() + getAdjY(random_index);

            putClone(nextGrid, put_baby_wolf_X, put_baby_wolf_Y);
            // reset breedCounter to MAX == breedCooldown();
            this->setBreedCounter(this->getBreedCooldown());
            return;

        }
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
    Entity* found_sheep = nullptr;
    int curr_wolf_X = this->getX();
    int curr_wolf_Y = this->getY();
    int closest_sheep_dist = 100000000; // some impossibly high number
    int closest_sheep_X = 20;   // to make it obvious if there is abug
    int closest_sheep_Y = 10;
    // ?
    for (int x=0; x<BOARD_SIZE_W; ++x) {
        for (int y=0; y<BOARD_SIZE_H; ++y) {
            Entity* cell = this->getBoard()->getGrid()->getCell(x,y);
            // ?

            // if not empty, and not removed, and is a sheep.
            if (cell != nullptr && !cell->isRemoved() && cell->toChar() == 'S') {

                //  (X_displacement^2 + Y_displacement^2) not square rooted, because we are comparing anyways
                //  sqrt a < sqrt b === a < b
                int euc_dist = ( (curr_wolf_X - cell->getX())*(curr_wolf_X - cell->getX()) + 
                                 (curr_wolf_Y - cell->getY())*(curr_wolf_Y - cell->getY()) );

                // if the sheep is closer than one previously found, replace the old sheep
                // otherwise, don't replace it.
                if (euc_dist < closest_sheep_dist) {
                    closest_sheep_dist = euc_dist;
                    closest_sheep_X = cell->getX();
                    closest_sheep_Y = cell->getY();
                    found_sheep = this->getBoard()->getGrid()->getCell(x,y);
                }
                
            }

        }
    }

    if (found_sheep != nullptr) { // Edit this line with the appropriate condition
        // If a sheep with the closest distance is found, try to move towards it
        int move_to_X = -1;
        int move_to_Y = -1;

        // same ROW 
        if (closest_sheep_Y == curr_wolf_Y) {
            // left or right?
            // if wolf is to the left of sheep, move right
            if (curr_wolf_X < closest_sheep_X) {
                move_to_X = this->getX() + getAdjX(7);
                move_to_Y = this->getY();

            }
            // if wolf is to the right of sheep, move left 
            else if (curr_wolf_X > closest_sheep_X) {
                move_to_X = this->getX() + getAdjX(1);
                move_to_Y = this->getY();
            } 
            else {
                std::cout << "this should never occur, wolf::move() case: Sheep is on top of wolf" << std:: endl;
            }
        }

        // same column
        else if (closest_sheep_X == curr_wolf_X) {
            // up or down?
            // if wolf is to the below the sheep, move up
            std::cout << "same column" << std::endl;
            if (curr_wolf_Y > closest_sheep_Y) {
                std::cout << "same column-1" << std::endl;
                move_to_X = this->getX();
                move_to_Y = this->getY() + getAdjX(3);
            }
            // if wolf is to the above the sheep, move down
            else if (curr_wolf_Y < closest_sheep_Y) {
                std::cout << "same column-2" << std::endl;
                move_to_X = this->getX();
                move_to_Y = this->getY() + getAdjX(5);

            } 
            else {
                std::cout << "this should never occur, wolf::move() case: Sheep is on top of wolf" << std:: endl;
            }
        }

        // not in same row, or column, so the wolf must move diagonally.
        else {
            // std::cout << "diagonal move" << std::endl;
            // if wolf is right and below of sheep, move left and up.
            if (curr_wolf_X > closest_sheep_X && curr_wolf_Y > closest_sheep_Y) {
                // std::cout << "diagonal move 1" << std::endl;
                move_to_X = this->getX() + getAdjX(0);
                move_to_Y = this->getY() + getAdjY(0);
            }
            // if wolf is left and above of sheep, move right and down.
            else if (curr_wolf_X < closest_sheep_X && curr_wolf_Y < closest_sheep_Y) {
                // std::cout << "diagonal move 2" << std::endl;
                move_to_X = this->getX() + getAdjX(8);
                move_to_Y = this->getY() + getAdjY(8);

            } 
            // if wolf is left and below of sheep, move right and up.
            else if (curr_wolf_X < closest_sheep_X && curr_wolf_Y > closest_sheep_Y) {
                // std::cout << "diagonal move 3" << std::endl;
                move_to_X = this->getX() + getAdjX(6);
                move_to_Y = this->getY() + getAdjY(6);

            } 
            // if wolf is right and above of sheep, move left and down.
            else if (curr_wolf_X > closest_sheep_X && curr_wolf_Y < closest_sheep_Y) {
                // std::cout << "diagonal move 4" << std::endl;
                move_to_X = this->getX() + getAdjX(2);
                move_to_Y = this->getY() + getAdjY(2);

            } 
        }

        if (move_to_X != -1 && move_to_Y != -1) {
            // std::cout << "Wolf x: " << this->getX() << " Wolf y: " << this->getY() << std::endl; 
            // // std::cout << "Sheep x: " << closest_sheep_X << " Sheep y: " << closest_sheep_Y << std::endl; 
            // std::cout << "move to  x: " << move_to_X << " move to y: " << move_to_Y << std::endl; 
            


            Entity* adjEntity = getBoard()->getGrid()->getCell(move_to_X, move_to_Y);
            Entity* adjNextEntity = nextGrid->getCell(move_to_X, move_to_Y);


            // for some reason putSelf is not being called on columns, 
            // need to test
            on rows


            // Adjacent cell is not an animal, can move over
            if ( !(dynamic_cast<Animal*>(adjEntity)) && !(dynamic_cast<Animal*>(adjNextEntity)) ){
                std::cout << "Wolf x: " << this->getX() << " Wolf y: " << this->getY() << std::endl; 
                // std::cout << "Sheep x: " << closest_sheep_X << " Sheep y: " << closest_sheep_Y << std::endl; 
                std::cout << "move to  x: " << move_to_X << " move to y: " << move_to_Y << std::endl; 
                
                putSelf(nextGrid, move_to_X, move_to_Y);
                return;
                
            } else {
                putSelf(nextGrid, this->getX(), this->getY());
                return;
            }

        } 
        else {
            std::cout << "something has gone wrong in wolf::move()" << std::endl;
        }



        

        // if sheep shares the same y coordinate, they are in the same row, 
        // the wolf should then move left or right

        // likewise for x
        // wolf should move up or down
        

        // otherwise, the wolf should move diagonally.

        





        // ?
    }
    else {
        // No sheep found, move randomly
        
        // ?
        int random_index = getRandomMovementIndex(nextGrid);
        // if all adjacent tiles are full, just stay still.
        if (random_index == -1) {
            putSelf(nextGrid, this->getX(), this->getY());
            return;
        }
        int move_wolf_X = getX() + getAdjX(random_index);
        int move_wolf_Y = getY() + getAdjY(random_index);
        putSelf(nextGrid, move_wolf_X, move_wolf_Y);

    }
}