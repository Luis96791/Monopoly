#include "Carta.h"

Carta::Carta()
{
    //ctor
}

void Carta::setTipoCarta(string tc)
{
    tipo_carta = tc;
}

void Carta::setTraspaso(bool t)
{
    traspaso = t;
}

bool Carta::getTraspaso()
{
    return traspaso;
}

string Carta::getTipoCarta()
{
    return tipo_carta;
}

Carta::~Carta()
{
    //dtor
}
