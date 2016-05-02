#ifndef CREARJUGADOR_H
#define CREARJUGADOR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class CrearJugador
{
    public:
        string nombre;
        int capital;
        CrearJugador(string n);
        vector <CrearJugador>jugadores_ingresados;
        void nuevoJugador(string n);
        void ventanaCrearJugador();
        void removerJugadores();
        virtual ~CrearJugador();
    protected:

    private:
};

#endif // CREARJUGADOR_H
