#include "Propiedad.h"

Propiedad::Propiedad()
{
    //ctor
}

string Propiedad::getNombrePosesion()
{
    return nombre_posesion;
}

string Propiedad::getNombreDuenio()
{
    return nombre_duenio;
}

string Propiedad::getColorPropiedad(){
    return color_propiedad;
}

int Propiedad::getValorPropiedad()
{
    return valor_propiedad;
}

int Propiedad::getRenta()
{
    return renta;
}

int Propiedad::getValorHipoteca()
{
    return valor_hipoteca;
}

bool Propiedad::getEstadoHipoteca()
{
    return estado_hipoteca;
}

void Propiedad::setNombrePosesion(string np)
{
    nombre_posesion = np;
}

void Propiedad::setNombreDuenio(string nd)
{
    nombre_duenio = nd;
}

void Propiedad::setColorPropiedad(string c)
{
    color_propiedad = c;
}

void Propiedad::setValorPropiedad(int v)
{
    valor_propiedad = v;
}

void Propiedad::setRenta(int r)
{
    renta = r;
}

void Propiedad::setValorHipoteca(int vh)
{
    valor_hipoteca = vh;
}

void Propiedad::setEstadoHipoteca(bool eh)
{
    estado_hipoteca = eh;
}

Propiedad::~Propiedad()
{
    //dtor
}
