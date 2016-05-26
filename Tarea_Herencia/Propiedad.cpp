#include "Propiedad.h"

Propiedad::Propiedad()
{
    //ctor
}

void Propiedad::setNombreDuenio(string nd)
{
    nombre_duenio = nd;
}

void Propiedad::setNombreCarta(string nc)
{
    nombre_carta = nc;
}

void Propiedad::setColorPropiedad(string c_p)
{
    color_propiedad = c_p;
}

void Propiedad::setRenta(int r)
{
    renta = r;
}

void Propiedad::setValorHipoteca(int v_h)
{
    valor_hipoteca = v_h;
}

void Propiedad::setValorPropiedad(int v_p)
{
    valor_propiedad = v_p;
}

string Propiedad::getNombreCarta()
{
    return nombre_carta;
}

string Propiedad::getNombreDuenio()
{
    return nombre_duenio;
}

string Propiedad::getColorPropiedad()
{
    return color_propiedad;
}

int Propiedad::getRenta()
{
    return renta;
}

int Propiedad::getValorHipoteca()
{
    return valor_hipoteca;
}

int Propiedad::getValorPropiedad()
{
    return valor_propiedad;
}

Propiedad::~Propiedad()
{
    //dtor
}
