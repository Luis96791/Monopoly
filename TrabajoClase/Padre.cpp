#include "Padre.h"

Padre::Padre()
{
    //ctor
}

int Padre::getPos(int pos)
{
    return arreglo[pos];
}

void Padre::setPosicion(int pos, int num)
{
    arreglo[pos] = num;
}

Padre::~Padre()
{
    //dtor
}
