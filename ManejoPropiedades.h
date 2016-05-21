#ifndef MANEJOPROPIEDADES_H
#define MANEJOPROPIEDADES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "Propiedad.h"
#include "utility.h"

using namespace std;

class ManejoPropiedades
{
    public:
        Utility utility;
        ManejoPropiedades();
        void setPropiedades(Propiedad propiedad);
        void ventanaCompras(sf::Sprite* sprite);
        Propiedad getPropiedades(int pos);
        void llenarPropiedades();
        void mostrarPropiedades();
        virtual ~ManejoPropiedades();

    protected:
    private:
        vector<Propiedad>propiedades;
};

#endif // MANEJOPROPIEDADES_H
