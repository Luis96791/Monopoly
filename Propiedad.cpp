#include "Propiedad.h"

Propiedad::Propiedad(string np, string nd, int r, int v,string cp)
{
    np = nombre_posesion;
    nd = nombre_duenio;
    r = renta;
    v = valor_hipoteca;
    cp = color_propiedad;
    estado_hipoteca = false;
}

string Propiedad::getNombrePosesion()
{
    return nombre_posesion;
}

string Propiedad::getNombreDuenio()
{
    return nombre_duenio;
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

string Propiedad::getColorPropiedad(){
    return color_propiedad;
}

void Propiedad::setNombreDuenio(string nd)
{
    nombre_duenio = nd;
}

void Propiedad::setEstadoHipoteca(bool eh)
{
    estado_hipoteca = eh;
}

void Propiedad::print(){
    cout<<nombre_posesion<<" , "<<nombre_duenio<<" , "<<renta<<endl;
}

Propiedad::~Propiedad()
{
    //dtor
}
