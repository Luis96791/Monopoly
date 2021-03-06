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
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
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
        void cobrarImpuestos(sf::Sprite* sprite, int posJugador);
        bool ventanaCompras(sf::Sprite* sprite, string nombre);
        bool aLaCarcel(sf::Sprite* sprite,int posJugador);
        bool esperarTresTurnos(int dado1, int dado2, int posJugador);
        bool cobrarRentaPropiedades(sf::Sprite* sprite,int posJugador);
        bool rentaPorColor(string duenio, string color);
        int numeroDePropiedadesPorColor(string color);
        void rentaServicios(sf::Sprite* sprite, int dados, int posJugador);
        void ventanaHipotecar(string nombre,int posJugador);
        void ventanaDeshipotecar(string nombre, int posJugador);
        bool ventanaInventario(string nombre, int posJugador);
        void ventanaTerminarJuego();
        void cobrarSalida(sf::Sprite* sprite, int posJugador);
        int infoPropiedad(sf::Sprite* sprite);
        int buscarJugador(string nombre);
        bool mostrarCartaArca(sf::Sprite* sprite);
        bool mostrarCartaFortuna(sf::Sprite* sprite);
        void ejecutarCartaArca(sf::Sprite* sprite, int posJugador);
        void ejecutarCartaFortuna(sf::Sprite* sprite, int posJugador, int dados);
        void ejecutarFunciones(sf::Sprite* sprite,int posJugador,int suma_dados);
        bool hipotecar(sf::String nombre_propiedad,int posJugador);
        bool deshipotecar(sf::String nombre_propiedad,int posJugador);
        bool propiedadExiste(sf::String nombre_propiedad);
        int inventario(int posJugador);
        int ganador();
        int ganadorPorDefault();
        bool empate();
        virtual ~JugarMonopoly();

    protected:

    private:
};

#endif // JUGARMONOPOLY_H
