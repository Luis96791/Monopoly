#ifndef PROPIEDAD_H
#define PROPIEDAD_H

#include <iostream>
#include "posesion.h"

using namespace std;

class Propiedad : public Posesion
{
    public:
        string color_propiedad;
        Propiedad(string np, string nd, int r, int v,string cp);
        string getColor();
        virtual ~Propiedad();

    protected:

    private:
};

#endif // PROPIEDAD_H
