#include "Sumador.h"

Sumador::Sumador()
{
    //ctor
}

int Sumador::getPos(int pos)
{
    return arreglo[pos];
}

void Sumador::setPosicion(int pos, int num)
{
    arreglo[pos] = num;
}

int Sumador::suma()
{
    int ac=0;
    for(int c = 0; c < 10; c++){
        ac += arreglo[c];
    }
    return ac;
}

int Sumador::mayor()
{
    cout<<"No soporta la funcion..."<<endl;
    return 0;
}

Sumador::~Sumador()
{
    //dtor
}
