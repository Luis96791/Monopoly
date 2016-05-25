#ifndef CARTA_H
#define CARTA_H

#include <iostream>

using namespace std;

class Carta
{
    public:
        Carta();
        string getTipoCarta();
        void setTipoCarta(string tc);
        bool getTraspaso();
        void setTraspaso(bool t);
        virtual ~Carta();

    protected:
        string tipo_carta;
        bool traspaso;
    private:
};

#endif // CARTA_H
