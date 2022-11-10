#ifndef __SHEEP_H__
#define __SHEEP_H__

#include "animal.h"

const int SHEEP_HUNGER_COOLDOWN = 4 * 4;
const int SHEEP_BREED_COOLDOWN = 2 * 4;
const int SHEEP_MOVE_COOLDOWN = 4;

class Sheep: public Animal {

    protected:
        virtual const int getHungerCooldown() const override { return SHEEP_HUNGER_COOLDOWN; } 
        virtual const int getBreedCooldown() const override { return SHEEP_BREED_COOLDOWN; } 
        virtual const int getMoveCooldown() const override { return SHEEP_MOVE_COOLDOWN; } 

        virtual void putSelf(Grid* nextGrid, int x, int y) override;
        virtual void putClone(Grid* nextGrid, int x, int y) const override;

    public:
        Sheep(Board* board): 
            Animal(board, SHEEP_HUNGER_COOLDOWN / 2, SHEEP_BREED_COOLDOWN, SHEEP_MOVE_COOLDOWN) {}
        Sheep(const Sheep& sheep):
            Animal(sheep.getBoard(), sheep.getHungerCounter(), sheep.getBreedCounter(), sheep.getMoveCounter()) {}

        virtual void eat(Grid* nextGrid) override;
        virtual void breed(Grid* nextGrid) override;
        virtual void move(Grid* nextGrid) override;

        virtual char toChar() const override { return 'S'; }
};

#endif // __SHEEP_H__