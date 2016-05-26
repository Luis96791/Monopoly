#include "Servicios.h"

Servicios::Servicios()
{
    //ctor
}

void Servicios::setNombreServicio(string ns)
{
    nombre_servicio = ns;
}

void Servicios::setNombreDuenio(string nd)
{
    nombre_duenio = nd;
}

void Servicios::setRenta(int r)
{
    renta = r;
}

void Servicios::setValorHipoteca(int v_h)
{
    valor_hipoteca = v_h;
}

void Servicios::setValorServicio(int v_s)
{
    valor_servicio = v_s;
}

string Servicios::getNombreServicio()
{
    return nombre_servicio;
}

string Servicios::getNombreDuenio()
{
    return nombre_duenio;
}

int Servicios::getRenta()
{
    return renta;
}

int Servicios::getValorHipoteca()
{
    return valor_hipoteca;
}

int Servicios::getValorServicio()
{
    return valor_servicio;
}

Servicios::~Servicios()
{
    //dtor
}
