#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "board.h"
#include <iostream>

class Entity {
    private:
        Board* board;
        int x, y;
        int nextX, nextY;
        bool removed;
        Entity* original;

    protected:
        // Put a copy of current Entity onto the next Grid. Also put the copy's position in nextX, nextY.
        virtual void putSelf(Grid* nextGrid, int x, int y) = 0;

        // Put a brand new Entity onto the next Grid.
        virtual void putClone(Grid* nextGrid, int x, int y) const = 0;

    public:
        Entity(Board* board);
        virtual ~Entity();

        // Accessors
        Board* getBoard() const { return board; }
        int getX() const { return x; }
        int getY() const { return y; }
        bool isRemoved() const { return removed; }

        // Mutators
        void setX(const int x) { this->x = x; }
        void setY(const int y) { this->y = y; }

        // Set nextX and nextY to locate this entity on the nextGrid.
        void setNextSelf(Entity* entity);

        // Called when this entity would be killed. Need to remove copy from nextGrid.
        void removeSelf(Grid* nextGrid);

        virtual void update(Grid* nextGrid) = 0;
        virtual char toChar() const = 0;
};

#endif // __ENTITY_H__