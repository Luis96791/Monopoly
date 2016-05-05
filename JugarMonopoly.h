#ifndef JUGARMONOPOLY_H
#define JUGARMONOPOLY_H

#include <iostream>
#include <vector>
#include "utility.h"
#include "CrearJugador.h"
#include <SFML/Graphics.hpp>

using namespace std;

class JugarMonopoly
{
    public:
        string nombre_archivo = "jugadores.txt";
        CrearJugador crearJugador();
        Utility utility;
        JugarMonopoly();
        vector<CrearJugador>jugadores;
        vector<CrearJugador>cargarJugadores();
        void ventanaTablero();
        virtual ~JugarMonopoly();

    protected:

    private:
};

#endif // JUGARMONOPOLY_H
