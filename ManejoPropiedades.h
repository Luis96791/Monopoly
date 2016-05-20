#ifndef MANEJOPROPIEDADES_H
#define MANEJOPROPIEDADES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "Propiedad.h"

using namespace std;

class ManejoPropiedades
{
    public:
        ManejoPropiedades();
        void setPropiedades(Propiedad propiedad);
        void ventanaCompras();
        Propiedad getPropiedades(int pos);
        void llenarPropiedades();
        void mostrarPropiedades();
        virtual ~ManejoPropiedades();

    protected:
    private:
        vector<Propiedad>propiedades;
};

#endif // MANEJOPROPIEDADES_H
