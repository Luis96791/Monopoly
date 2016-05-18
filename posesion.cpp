#include "Posesion.h"

Posesion::Posesion(string np, string nd, int r, int v)
{
    np = nombre_posesion;
    nd = nombre_duenio;
    r = renta;
    v = valor_hipoteca;
    estado_hipoteca = false;
}

string Posesion::getNombrePosesion()
{
    return nombre_posesion;
}

string Posesion::getNombreDuenio()
{
    return nombre_duenio;
}

int Posesion::getRenta()
{
    return renta;
}

bool Posesion::getEstadoHipoteca()
{
    return estado_hipoteca;
}

int Posesion::getValorHipoteca()
{
    return valor_hipoteca;
}

//        void setNombreDuenio(string nd);
//        void setEstadoHipoteca(string eh);

void Posesion::setNombreDuenio(string nd)
{
    nombre_duenio = nd;
}

void Posesion::setEstadoHipoteca(bool eh)
{
    estado_hipoteca = eh;
}

Posesion::~Posesion()
{
    //dtor
}
