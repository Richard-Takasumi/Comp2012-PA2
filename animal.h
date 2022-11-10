#ifndef __ANIMAL_H__
#define __ANIMAL_H__

#include "entity.h"

class Animal: public Entity {
    private:
        int hungerCounter;
        int breedCounter;
        int moveCounter;

    protected:
        virtual const int getHungerCooldown() const = 0;
        virtual const int getBreedCooldown() const = 0;
        virtual const int getMoveCooldown() const = 0;

        bool putAnimal(Animal* animal, Grid* nextGrid, int x, int y) const;

        void setHungerCounter(const int hungerCounter) { this->hungerCounter = hungerCounter; }
        void setBreedCounter(const int breedCounter) { this->breedCounter = breedCounter; }

        int getRandomMovementIndex(Grid* nextGrid) const;

    public:
        Animal(Board* board, int hungerCounter, int breedCounter, int moveCounter): 
            Entity(board), hungerCounter(hungerCounter), breedCounter(breedCounter), moveCounter(moveCounter) {}

        int getHungerCounter() const { return hungerCounter; }
        int getBreedCounter() const { return breedCounter; }
        int getMoveCounter() const { return moveCounter; }

        virtual void update(Grid* nextGrid) override;

        virtual void eat(Grid* nextGrid) = 0;
        virtual void breed(Grid* nextGrid) = 0;
        virtual void move(Grid* nextGrid) = 0;
};

#endif // __ANIMAL_H__