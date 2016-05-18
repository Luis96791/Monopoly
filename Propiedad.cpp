#include "Propiedad.h"

Propiedad::Propiedad(string np, string nd, int r, int v,string cp)
{
    np = nombre_posesion;
    nd = nombre_duenio;
    r = renta;
    v = valor_hipoteca;
    estado_hipoteca = false;
    cp = color_propiedad;
}

Propiedad::~Propiedad()
{
    //dtor
}
