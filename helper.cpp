#include "helper.h"
#include "stdlib.h"

bool countdown(int& counter, const int MAX_COUNT) {
    --counter;
    if (counter <= 0) {
        counter = MAX_COUNT;
        return true;
    }
    return false;
}

unsigned int next_num = 1; 
unsigned int pseudo_rand()
{
    next_num = next_num * 1103515245 + 2011;
    return static_cast<unsigned int>(next_num / 65536) % 32768;
}

int getAdjX(const int index) { return index / 3 - 1; }
int getAdjY(const int index) { return index % 3 - 1; }