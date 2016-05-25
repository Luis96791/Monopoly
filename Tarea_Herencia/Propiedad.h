#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <iostream>
#include "Carta.h"

using namespace std;

class Propiedad : public Carta
{
    public:
        Propiedad();
        void setNombreCarta(string nc);
        void setNombreDuenio(string nd);
        void setColorPropiedad(string c_p);
        void setRenta(int r);
        void setValorHipoteca(int v_h);
        void setValorPropiedad(int v_p);
        string getNombreCarta();
        string getNombreDuenio();
        string getColorPropiedad();
        int getRenta();
        int getValorHipoteca();
        int getValorPropiedad();
        virtual ~Propiedad();

    protected:
        string nombre_carta, nombre_duenio,color_propiedad;
        int renta,valor_hipoteca,valor_propiedad;
    private:
};

#endif // PROPIEDAD_H
