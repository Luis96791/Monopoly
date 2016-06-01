#ifndef MAYORISTA_H
#define MAYORISTA_H
#include "Padre.h"
#include <iostream>

using namespace std;

class Mayorista:public Padre
{
    public:
        Mayorista();
        int getPos(int pos);
        void setPosicion(int pos, int num);
        int suma();
        int mayor();
        virtual ~Mayorista();

    protected:

    private:
};

#endif // MAYORISTA_H
