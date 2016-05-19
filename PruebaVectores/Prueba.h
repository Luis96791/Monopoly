#ifndef PRUEBA_H
#define PRUEBA_H

#include <vector>
#include "Mi_vector.h"
#include <iostream>
#include <fstream>

using namespace std;

class Prueba
{
    public:
        Prueba();
        void setMiVector(Mi_vector vec);
        Mi_vector getMiVector(int pos);
        void llenarMiVector();
        void mostrarMiVector();
        virtual ~Prueba();

    protected:

    private:
        vector<Mi_vector>mi_vector;
};

#endif // PRUEBA_H
