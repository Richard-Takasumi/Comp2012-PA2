#ifndef __WOLF_H__
#define __WOLF_H__

#include "animal.h"

const int WOLF_HUNGER_COOLDOWN = 20 * 3;
const int WOLF_BREED_COOLDOWN = 10 * 3;
const int WOLF_MOVE_COOLDOWN = 3;

class Wolf: public Animal {

    protected:
        virtual const int getHungerCooldown() const override { return WOLF_HUNGER_COOLDOWN; } 
        virtual const int getBreedCooldown() const override { return WOLF_BREED_COOLDOWN; } 
        virtual const int getMoveCooldown() const override { return WOLF_MOVE_COOLDOWN; } 

        virtual void putSelf(Grid* nextGrid, int x, int y) override;
        virtual void putClone(Grid* nextGrid, int x, int y) const override;

    public:
        Wolf(Board* board): 
            Animal(board, WOLF_HUNGER_COOLDOWN / 2, WOLF_BREED_COOLDOWN, WOLF_MOVE_COOLDOWN) {}
        Wolf(const Wolf& wolf):
            Animal(wolf.getBoard(), wolf.getHungerCounter(), wolf.getBreedCounter(), wolf.getMoveCounter()) {}

        virtual void eat(Grid* nextGrid) override;
        virtual void breed(Grid* nextGrid) override;
        virtual void move(Grid* nextGrid) override;

        virtual char toChar() const override { return 'W'; }
};

#endif // __WOLF_H__