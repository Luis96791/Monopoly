#include <iostream>

#include "Carta.h"
#include "Propiedad.h"
#include "Estaciones.h"
#include "Servicios.h"

using namespace std;

void print(Carta carta)
{
    cout<<carta.getTipoCarta()<<" , "<<carta.getTraspaso()<<endl;
}

void print(Propiedad propiedad)
{
    cout<<propiedad.getTipoCarta()<<" , "<<propiedad.getNombreCarta()
    <<" , "<<propiedad.getValorPropiedad()<<endl;
}

void print(Estaciones estacion)
{
    cout<<estacion.getTipoCarta()<<" , "<<estacion.getNombreDuenio()
    <<" , "<<estacion.getNombreEstacion()<<endl;
}

int operator+(Servicios s1, Servicios s2){
    return s1.getRenta()+s2.getRenta();
}

int operator-(Servicios s1, Servicios s2){
    return s1.getRenta()-s2.getRenta();
}


int main()
{
    Carta carta;
    carta.setTipoCarta("fortuna");
    carta.setTraspaso(true);
    print(carta);

    cout<<"\n";

    Propiedad propiedad;
    propiedad.setTipoCarta("propiedad");
    propiedad.setTraspaso(true);
    propiedad.setNombreCarta("avenida circunvalacion");
    propiedad.setNombreDuenio("luis");
    propiedad.setColorPropiedad("rojo");
    propiedad.setRenta(20);
    propiedad.setValorHipoteca(100);
    propiedad.setValorPropiedad(200);
    print(propiedad);

    cout<<"\n";

    Estaciones estacion;
    estacion.setTipoCarta("propiedad");
    estacion.setNombreDuenio("luis 1");
    estacion.setNombreEstacion("ferrocarril norte");
    print(estacion);

    Servicios op1, op2, op3;

    op1.setRenta(20);
    op2.setRenta(30);
    op3.setRenta(60);
    cout<<"op1 + op2: "<<op1+op2<<endl;
    cout<<"op3 - op1: "<<op3-op2<<endl;


    return 0;
}
