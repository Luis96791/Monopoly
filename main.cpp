#include <SFML/Graphics.hpp>
#include <iostream>
#include "utility.h"

using namespace std;

int main()
{
    Utility utils;

    sf::RenderWindow window;
    sf::Texture text_dado1,text_dado2,text_tablero;
    sf::Sprite back_dado1,back_dado2,back_tablero;

    window.create(sf::VideoMode(1360,690,32),"Monopoly",sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    text_tablero.loadFromFile("tablero.png");
    back_tablero.setTexture(text_tablero);

    back_tablero.setPosition(0,0);
    back_dado1.setPosition(300,200);
    back_dado2.setPosition(500,200);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                text_dado1.loadFromFile("dados/"+utils.toString(utils.dadoUno())+".png");
                back_dado1.setTexture(text_dado1);
                text_dado2.loadFromFile("dados/"+utils.toString(utils.dadoDos())+".png");
                back_dado2.setTexture(text_dado2);
            }
        }
        window.draw(back_tablero);
        window.draw(back_dado1);
        window.draw(back_dado2);

        window.display();
    }
    return 0;
}
