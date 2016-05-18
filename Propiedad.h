#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <iostream>

using namespace std;

class Propiedad
{
    public:
        string nombre_posesion, nombre_duenio, color_propiedad;
        int valor_hipoteca, renta;
        bool estado_hipoteca;
        Propiedad(string np, string nd, int r, int v,string cp);
        string getNombrePosesion();
        string getNombreDuenio();
        int getRenta();
        bool getEstadoHipoteca();
        int getValorHipoteca();
        string getColorPropiedad();
        void setNombreDuenio(string nd);
        void setEstadoHipoteca(bool eh);
        void print();
        virtual ~Propiedad();

    protected:

    private:
};

#endif // PROPIEDAD_H
