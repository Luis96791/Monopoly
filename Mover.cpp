#include "Mover.h"

Mover::Mover(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Mover::getX()
{
    return x;
}

int Mover::getY()
{
    return y;
}

Mover::~Mover()
{
    //dtor
}
