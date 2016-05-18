#ifndef SERVICIO_H
#define SERVICIO_H

#include "posesion.h"
#include <iostream>

using namespace std;

class Servicio : public Posesion
{
    public:
        string tipo_servicio;
        Servicio(string np, string nd, int r, int v, string t);
        string getNombrePosesion();
        string getNombreDuenio();
        int getRenta();
        bool getEstadoHipoteca();
        int getValorHipoteca();
        string getTipo();
        void setNombreDuenio(string nd);
        void setEstadoHipoteca(bool eh);
        virtual ~Servicio();

    protected:

    private:
};

#endif // SERVICIO_H
