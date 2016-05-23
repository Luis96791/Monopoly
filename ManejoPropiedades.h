#ifndef MANEJOPROPIEDADES_H
#define MANEJOPROPIEDADES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include "Propiedad.h"
#include "CrearJugador.h"
#include "utility.h"

using namespace std;

class ManejoPropiedades
{
    public:
        Utility utility;
        ManejoPropiedades();
        void setPropiedades(Propiedad propiedad);
        bool ventanaCompras(string nombre, sf::Sprite* sprite);
        Propiedad getPropiedades(int pos);
        void setPrecio(int p);
        int getPrecio();
        void setDuenio(string duenio);
        string getDuenio();
        void llenarPropiedades();
        void mostrarPropiedades();
        virtual ~ManejoPropiedades();

    protected:
    private:
        vector<Propiedad>propiedades;
        int precio;
        string duenio;
};

#endif // MANEJOPROPIEDADES_H
