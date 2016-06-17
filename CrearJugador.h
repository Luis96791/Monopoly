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
        string nombre_archivo;
        Utility utility;
        int capital, acumular_turnos;
        string nombre, color;
        bool isPreso;
        CrearJugador(string n, string c);
        vector<CrearJugador>jugadores;
        vector<string>nombre_propiedades;
        void nuevoJugador(string n,string c);
        string getNombre();
        string getColor();
        bool getIsPreso();
        void setIsPreso(bool p);
        int getCapital();
        void setCapital(int c);
        void setNombre(string n);
        void depositar(int cant);
        int retirar(int cant);
        void escribirArchivo();

        bool ventanaCrearJugador();
        void removerJugadores();
        virtual ~CrearJugador();
    protected:

    private:
};

#endif // CREARJUGADOR_H
