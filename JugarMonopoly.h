#ifndef JUGARMONOPOLY_H
#define JUGARMONOPOLY_H

#include <iostream>
#include <vector>
#include "utility.h"
#include "CrearJugador.h"
#include <SFML/Graphics.hpp>
#include <fstream>

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
        sf::Sprite moverFichaPorDados(sf::Sprite sprite,int suma_dados);
        void ventanaTablero();
        virtual ~JugarMonopoly();

    protected:

    private:
};

#endif // JUGARMONOPOLY_H
