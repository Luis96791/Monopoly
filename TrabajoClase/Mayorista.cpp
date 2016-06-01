#include "Mayorista.h"

Mayorista::Mayorista()
{
    //ctor
}

int Mayorista::getPos(int pos)
{
    return arreglo[pos];
}

void Mayorista::setPosicion(int pos, int num)
{
    arreglo[pos] = num;
}

int Mayorista::suma()
{
    cout<<"No soporta la funcion..."<<endl;
    return 0;
}

int Mayorista::mayor()
{
    int mayor = -1000;
    for(int c = 0; c < 10; c++)
    {
        if(arreglo[c]>mayor){
            mayor = arreglo[c];
        }
    }
    return mayor;
}

Mayorista::~Mayorista()
{
    //dtor
}
