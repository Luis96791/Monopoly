#ifndef JUGARMONOPOLY_H
#define JUGARMONOPOLY_H

#include <iostream>
#include <vector>
#include "utility.h"
#include "CrearJugador.h"
#include "ManejoPropiedades.h"
#include "Mover.h"
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;

class JugarMonopoly
{
    public:
        string nombre_archivo;
        CrearJugador crearJugador();
        Utility utility;
        JugarMonopoly();
        vector<CrearJugador>jugadores;
        vector<CrearJugador>cargarJugadores();
        Mover mover();
        sf::Sprite movimiento(sf::Sprite* sprite,int suma_dados);
        bool validarCompra(sf::Sprite* sprite);
        void ventanaTablero();
        virtual ~JugarMonopoly();

    protected:

    private:
};

#endif // JUGARMONOPOLY_H
