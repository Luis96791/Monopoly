#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <iostream>

using namespace std;

class Propiedad
{
    public:
        Propiedad();
        string getNombrePosesion();
        string getNombreDuenio();
        string getColorPropiedad();
        int getValorPropiedad();
        int getRenta();
        int getValorHipoteca();
        bool getEstadoHipoteca();
        void setNombrePosesion(string n);
        void setNombreDuenio(string nd);
        void setColorPropiedad(string c);
        void setValorPropiedad(int v);
        void setRenta(int r);
        void setValorHipoteca(int vh);
        void setEstadoHipoteca(bool eh);

        virtual ~Propiedad();

    protected:

    private:
        string nombre_posesion, nombre_duenio, color_propiedad;
        int  valor_propiedad, valor_hipoteca, renta;
        bool estado_hipoteca;
};

#endif // PROPIEDAD_H
