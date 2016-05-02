#include "CrearJugador.h"

CrearJugador::CrearJugador(string n)
{
    nombre = n;
    capital = 1500;
    string extension = "titulos de propiedad/"+n+".txt";
    //jugadores_ingresados.push_back(extension);
    ofstream out(extension.c_str());
}

void CrearJugador::nuevoJugador(string n){
    jugadores_ingresados.push_back(CrearJugador(n));
}



void CrearJugador::ventanaCrearJugador(){
    sf::RenderWindow window;

    window.create(sf::VideoMode(300,300,32),"Monopoly",sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
            }
        }
        window.display();
    }
}

void CrearJugador::removerJugadores()
{
    for(unsigned int c=0;c<jugadores_ingresados.size();c++)
    {
        string k ="titulos de propiedad/"+jugadores_ingresados[c].nombre+".txt";
        remove(k.c_str());
    }
}

CrearJugador::~CrearJugador()
{
    removerJugadores();
}
