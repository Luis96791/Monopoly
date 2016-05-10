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
        string nombre_archivo = "jugadores.txt";
        Utility utility;
        int capital;
        string nombre, color;
        CrearJugador(string n, string c);
        vector<CrearJugador>jugadores;
        void nuevoJugador(string n,string c);
        void escribirArchivo();

        void ventanaCrearJugador();
        void removerJugadores();
        virtual ~CrearJugador();
    protected:

    private:
};

#endif // CREARJUGADOR_H
