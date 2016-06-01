#ifndef SUMADOR_H
#define SUMADOR_H
#include "Padre.h"
#include <iostream>

using namespace std;

class Sumador:public Padre
{
    public:
        Sumador();
        int getPos(int pos);
        void setPosicion(int pos, int num);
        int suma();
        int mayor();
        virtual ~Sumador();

    protected:

    private:
};

#endif // SUMADOR_H
