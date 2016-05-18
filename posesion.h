#ifndef POSESION_H
#define POSESION_H

#include <iostream>

using namespace std;

class Posesion
{
    public:
        string nombre_posesion, nombre_duenio;
        int renta;
        bool estado_hipoteca;
        int valor_hipoteca;
        Posesion(string np, string nd, int r, int v);
        string getNombrePosesion();
        string getNombreDuenio();
        int getRenta();
        bool getEstadoHipoteca();
        int getValorHipoteca();
        void setNombreDuenio(string nd);
        void setEstadoHipoteca(bool eh);
        virtual ~Posesion();

    protected:

    private:
};

#endif // POSESION_H
