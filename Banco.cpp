#include "Banco.h"

Banco::Banco()
{
    capital_bancario = 2000000;
}

void Banco::depositar(int cantidad)
{
    capital_bancario +=cantidad;
}

void Banco::retirar(int cantidad)
{
    capital_bancario-=cantidad;
}

Banco::~Banco()
{
    //dtor
}
