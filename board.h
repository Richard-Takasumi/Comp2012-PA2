#ifndef __BOARD_H__
#define __BOARD_H__

const int BOARD_SIZE_W = 20;
const int BOARD_SIZE_H = 10;

class Entity;

class Grid {
    private:
        Entity* cell[BOARD_SIZE_W][BOARD_SIZE_H];

    public:
        Grid(): cell() {}
        ~Grid();

        // Returns true if x and y results in out of bound position.
        bool outOfBounds(int x, int y) const;
        
        // Get the entity at position x, y. Returns nullptr if position is out of bound.
        Entity* getCell(int x, int y) const;

        // Set the cell at position x, y to point to entity, and update entity's x y positions.
        void setCell(Entity* entity, int x, int y);

        // Delete the cell at position x, y and set to nullptr.
        void deleteCell(int x, int y);
};

class Board {
    private:
        Grid* grid;
        int curStep;
        int totalEntityCount {0};

    public:
        Board(): grid(new Grid{}), curStep(0) {}
        ~Board() { delete grid; }

        Grid* getGrid() const { return grid; }

        void updateStep();

        void updateSteps(int numSteps);
        void updateTill(int stepToUpdateTo);

        void print() const;

        void addEntityCount(int modifier) { totalEntityCount += modifier; }
};

#endif // __BOARD_H__