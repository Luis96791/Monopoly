#include <iostream>
#include "Padre.h"
#include "Mayorista.h"
#include "Sumador.h"

using namespace std;

int main()
{
    Sumador sumador;
    Mayorista mayorista;

    for(int c = 0; c < 10; c++){
        sumador.setPosicion(c,0);
        mayorista.setPosicion(c,0);
    }

    cout<<"\nsumador"<<endl;
    sumador.setPosicion(0,10);
    sumador.setPosicion(1,20);

    mayorista.setPosicion(0,20);
    mayorista.setPosicion(1,30);
    mayorista.setPosicion(0,40);
    mayorista.setPosicion(1,80);

    cout<<sumador.getPos(0)<<endl;
    cout<<sumador.mayor()<<endl;
    cout<<sumador.suma()<<endl;


    cout<<"\nmayorista"<<endl;
    cout<<mayorista.getPos(0)<<endl;
    cout<<mayorista.suma()<<endl;
    cout<<mayorista.mayor()<<endl;

    cout << "Hello world!" << endl;
    return 0;
}
