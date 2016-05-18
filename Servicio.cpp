#include "Servicio.h"

Servicio::Servicio(string np, string nd, int r, int v, string t) : Posesion(np, nd, r, v)
{
    np = nombre_posesion;
    nd = nombre_duenio;
    r = renta;
    v = valor_hipoteca;
    estado_hipoteca = false;
    t = tipo_servicio;
}

string Servicio::getNombrePosesion()
{
    return nombre_posesion;
}

string Servicio::getNombreDuenio()
{
    return nombre_duenio;
}

int Servicio::getRenta()
{
    return renta;
}

int Servicio::getValorHipoteca()
{
    return valor_hipoteca;
}

bool Servicio::getEstadoHipoteca()
{
    return estado_hipoteca;
}

string Servicio::getTipo()
{
    return tipo_servicio;
}

void Servicio::setNombreDuenio(string nd)
{
    nombre_duenio = nd;
}

void Servicio::setEstadoHipoteca(bool eh)
{
    estado_hipoteca = eh;
}


Servicio::~Servicio()
{
    //dtor
}
