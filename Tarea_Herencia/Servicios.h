#ifndef SERVICIOS_H
#define SERVICIOS_H

#include "Carta.h"
#include <iostream>

using namespace std;

class Servicios : Carta
{
    public:
        Servicios();
        void setNombreServicio(string ns);
        void setNombreDuenio(string nd);
        void setRenta(int r);
        void setValorHipoteca(int v_h);
        void setValorServicio(int v_s);
        string getNombreServicio();
        string getNombreDuenio();
        int getRenta();
        int getValorHipoteca();
        int getValorServicio();
        virtual ~Servicios();

    protected:
        string nombre_servicio, nombre_duenio;
        int renta, valor_hipoteca, valor_servicio;
    private:
};

#endif // SERVICIOS_H
