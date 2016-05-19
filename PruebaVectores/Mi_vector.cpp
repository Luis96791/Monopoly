#include "Mi_vector.h"

Mi_vector::Mi_vector()
{
    //ctor
}

void Mi_vector::setNombre(string n)
{
    nombre = n;
}

void Mi_vector::setEdad(int e)
{
    edad = e;
}

string Mi_vector::getNombre()
{
    return nombre;
}

int Mi_vector::getEdad()
{
    return edad;
}

Mi_vector::~Mi_vector()
{
    //dtor
}
