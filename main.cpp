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
    CrearJugador crearJugador(0,"","");
    JugarMonopoly jugar;
    if(crearJugador.ventanaCrearJugador()){
        jugar.ventanaTablero();
    }
    return 0;
}
