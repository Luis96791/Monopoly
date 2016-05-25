#ifndef ESTACIONES_H
#define ESTACIONES_H

#include "Carta.h"
#include <iostream>

using namespace std;

class Estaciones : public Carta
{
    public:
        Estaciones();
        void setNombreEstacion(string ne);
        void setNombreDuenio(string nd);
        void setRenta(int r);
        void setValorHipoteca(int v_h);
        void setValorEstacion(int v_e);
        string getNombreEstacion();
        string getNombreDuenio();
        int getRenta();
        int getValorHipoteca();
        int getValorEstacion();
        virtual ~Estaciones();

    protected:
        string nombre_estacion, nombre_duenio;
        int renta, valor_hipoteca, valor_estacion;
    private:
};

#endif // ESTACIONES_H
