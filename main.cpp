#include <SFML/Graphics.hpp>
#include "utility.h"
#include "CrearJugador.h"
#include "JugarMonopoly.h"
#include "ManejoPropiedades.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
/**
    AQUI SE HACEN LAS PRUEBAS (CLASES, FUNCIONES Y VENTANAS)
*/

    CrearJugador crearJugador("","");
////
    JugarMonopoly jugar;
    if(crearJugador.ventanaCrearJugador()){
        jugar.ventanaTablero();
    }
//    CrearJugador crearJugador("","");
//   JugarMonopoly jugarMonopoly;
//    crearJugador.ventanaCrearJugador();
//   jugarMonopoly.ventanaTablero();

/**
    AQUI SE HACEN LAS PRUEBAS (CLASES, FUNCIONES Y VENTANAS)
*/
    return 0;
}
