#ifndef CREARJUGADOR_H
#define CREARJUGADOR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "utility.h"

using namespace std;

class CrearJugador
{
    public:
        Utility utility;
        string nombre,color;
        int capital;
        CrearJugador(string n,string c);
        void nuevoJugador(string n,string c);
        vector <CrearJugador>jugadores_ingresados;
        void ventanaCrearJugador();
        void removerJugadores();
        virtual ~CrearJugador();
    protected:

    private:
};

#endif // CREARJUGADOR_H
