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
        Utility utility;
        JugarMonopoly();
        void ventanaTablero();
        virtual ~JugarMonopoly();

    protected:

    private:
};

#endif // JUGARMONOPOLY_H
