#include <SFML/Graphics.hpp>
#include "utility.h"
#include "CrearJugador.h"
#include "JugarMonopoly.h"
#include "Propiedad.h"
#include <iostream>
#include <vector>

using namespace std;


int main()
{
//    Utility utils;
//
//    sf::RenderWindow window;
//    sf::Texture text_dado1,text_dado2,text_tablero, text_name,text_arca, text_fortuna,text_carta_arca,text1;
//    sf::Sprite back_dado1,back_dado2,back_tablero, back_name, back_arca, back_fortuna,back_carta_arca,back1;
//    sf::Font name;
//    sf::Text texto_name;
//    string nombre = "Luis";
//
//    window.create(sf::VideoMode(1360,690,32),"Monopoly",sf::Style::Default);
//    window.setVerticalSyncEnabled(true);
//
//    if(!name.loadFromFile("arial.ttf")){}
//
//    text_tablero.loadFromFile("tablero.png");
//    back_tablero.setTexture(text_tablero);
//    text_arca.loadFromFile("mazo_arca.png");
//    back_arca.setTexture(text_arca);
//    text_fortuna.loadFromFile("mazo_fortuna.png");
//    back_fortuna.setTexture(text_fortuna);
//    text_carta_arca.loadFromFile("arca_comunal/1.png");
//    back_carta_arca.setTexture(text_carta_arca);
//    text1.loadFromFile("arca_comunal/2.png");
//    back1.setTexture(text1);
//
//    back_tablero.setPosition(0,0);
//    back_dado1.setPosition(1140,580);
//    back_dado2.setPosition(1250,580);
//    back_arca.setPosition(115,115);
//    back_fortuna.setPosition(460,400);
//    back_carta_arca.setPosition(700,10);
//    back1.setPosition(900,10);
//
//    texto_name.setFont(name);
//    texto_name.setCharacterSize(72);
//    texto_name.setColor(sf::Color::Green);
//    texto_name.setPosition(20,0);
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed)
//            {
//                window.close();
//            }
//            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
//                text_dado1.loadFromFile("dados/"+utils.toString(utils.dadoUno())+".png");
//                back_dado1.setTexture(text_dado1);
//                text_dado2.loadFromFile("dados/"+utils.toString(utils.dadoDos())+".png");
//                back_dado2.setTexture(text_dado2);
//            }
//        }
//
//        texto_name.setString("nombre");
//
//        window.draw(back_tablero);
//        window.draw(back_dado1);
//        window.draw(back_dado2);
//        window.draw(back_arca);
//        window.draw(back_fortuna);
//        window.draw(texto_name);
//        window.draw(back_carta_arca);
//        window.draw(back1);
//
//        window.display();
//    }

/**
    AQUI SE HACEN LAS PRUEBAS (CLASES, FUNCIONES Y VENTANAS)
*/

//    vector<Propiedad*>propiedad;
//    propiedad.push_back(new Propiedad("Avenida Ventor","Banco",20,200,"amarillo"));
//    propiedad.push_back(new Propiedad("Avenida Connecticut","Banco",50,250,"amarillo"));
//
//    for(int c = 0;c < propiedad.size();c++){
//       propiedad[c]->print();
//    }

    CrearJugador crearJugador("","");
    crearJugador.ventanaCrearJugador();
//
    JugarMonopoly jugar;
    jugar.ventanaTablero();
//    CrearJugador crearJugador("","");
//   JugarMonopoly jugarMonopoly;
//    crearJugador.ventanaCrearJugador();
//   jugarMonopoly.ventanaTablero();

/**
    AQUI SE HACEN LAS PRUEBAS (CLASES, FUNCIONES Y VENTANAS)
*/

    return 0;
}
