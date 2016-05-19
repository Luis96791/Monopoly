#include <iostream>
#include "Prueba.h"
#include "Mi_vector.h"
#include <list>

using namespace std;

int main()
{
    Prueba prueba;
    Mi_vector v;

//    v.setNombre("luis");
//    v.setEdad(20);
//    prueba.setMiVector(v);
//
//    v.setNombre("luis1");
//    v.setEdad(40);
//    prueba.setMiVector(v);
//
//    v.setNombre("luis2");
//    v.setEdad(50);
//    prueba.setMiVector(v);
//
//    v.setNombre("luis3");
//    v.setEdad(60);
//    prueba.setMiVector(v);
//
//    v.setNombre("luis4");
//    v.setEdad(30);
//    prueba.setMiVector(v);

    prueba.llenarMiVector();
    prueba.mostrarMiVector();
    return 0;
}
