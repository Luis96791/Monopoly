#include "Estaciones.h"

Estaciones::Estaciones()
{
    //ctor
}

void Estaciones::setNombreEstacion(string ne)
{
    nombre_estacion = ne;
}

void Estaciones::setNombreDuenio(string nd)
{
    nombre_duenio = nd;
}

void Estaciones::setRenta(int r)
{
    renta = r;
}

void Estaciones::setValorHipoteca(int v_h)
{
    valor_hipoteca = v_h;
}

void Estaciones::setValorEstacion(int v_e)
{
    valor_estacion = v_e;
}

string Estaciones::getNombreEstacion()
{
    return nombre_estacion;
}

string Estaciones::getNombreDuenio()
{
    return nombre_duenio;
}

int Estaciones::getRenta()
{
    return renta;
}

int Estaciones::getValorHipoteca()
{
    return valor_hipoteca;
}

int Estaciones::getValorEstacion()
{
    return valor_estacion;
}

Estaciones::~Estaciones()
{
    //dtor
}
