#ifndef __GRASS_H__
#define __GRASS_H__

#include "entity.h"

const int SPREAD_COOLDOWN = 5;

class Grass: public Entity {
    private:
        int spreadCounter;

    protected:
        const int getSpreadCooldown() const { return SPREAD_COOLDOWN; }

        virtual void putSelf(Grid* nextGrid, int x, int y) override;
        virtual void putClone(Grid* nextGrid, int x, int y) const override;

    public:
        Grass(Board* board): Entity(board), spreadCounter(SPREAD_COOLDOWN) {}
        Grass(const Grass& grass): Entity(grass.getBoard()), spreadCounter(grass.spreadCounter) {}

        virtual void update(Grid* nextGrid) override;
        virtual char toChar() const override { return '.'; }
};

#endif // __GRASS_H__