#ifndef JUGARMONOPOLY_H
#define JUGARMONOPOLY_H

#include <iostream>
#include <vector>
#include "utility.h"
#include "CrearJugador.h"
#include "Propiedad.h"
#include "Banco.h"
#include "Mover.h"
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;

class JugarMonopoly
{
    public:
        vector<Propiedad>propiedades;
        string nombre_archivo;
        CrearJugador crearJugador();
        Utility utility;
        Banco banco;
        JugarMonopoly();
        vector<CrearJugador>jugadores;
        vector<CrearJugador>cargarJugadores();
        Mover mover();
        sf::Sprite movimiento(sf::Sprite* sprite,int suma_dados);
        bool validarCompra(sf::Sprite* sprite);
        void validarInfoDeCompra(sf::Sprite* sprite, int posJugador);
        void ventanaTablero();
        void ventanaSalirCarcel(int posJugador);
        Propiedad getPropiedades(int pos);
        void setPropiedades(Propiedad propiedad);
        void llenarPropiedades();
        void mostrarPropiedades();
        void cobrarImpuestos(sf::Sprite* sprite, int posJugador);
        bool ventanaCompras(sf::Sprite* sprite, string nombre);
        bool verificarSalida(sf::Sprite* sprite, int dados);
        bool aLaCarcel(sf::Sprite* sprite);
        bool esperarTresTurnos(int acum, int dado1, int dado2, int posJugador);
        void cobrarSalida(int posJugador);
        int infoPropiedad(sf::Sprite* sprite);
        virtual ~JugarMonopoly();

    protected:

    private:
};

#endif // JUGARMONOPOLY_H
