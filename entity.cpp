#include "entity.h"

// Constructor
Entity::Entity(Board* board): board(board), x(-1), y(-1), nextX(-1), nextY(-1), removed(false), original(nullptr)
{ 
    board->addEntityCount(1);
}

// Destructor
Entity::~Entity() 
{ 
    board->addEntityCount(-1); 
}

// Link this Entity with an entity on the nextGrid, so that it can be removed if needed
// Set nextX and nextY to find its position on nextGrid
void Entity::setNextSelf(Entity* entity) { 
    nextX = entity->getX();
    nextY = entity->getY();
    entity->original = this;
}

// Remove the copy from nextGrid, whose position is determined by nextX and nextY
void Entity::removeSelf(Grid* nextGrid) { 
    if (removed) return;
    removed = true;
    if (nextGrid->getCell(nextX, nextY) && nextGrid->getCell(nextX, nextY)->original == this) {
        nextGrid->deleteCell(nextX, nextY);
    }
}