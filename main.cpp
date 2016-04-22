#include <SFML/Graphics.hpp>
#include <iostream>
#include "utility.h"

using namespace std;

int main()
{
    Utility utils;

    sf::RenderWindow window;
    sf::Texture text_dado1,text_dado2;
    sf::Sprite back_dado1,back_dado2;

    window.create(sf::VideoMode(840,620,32),"Monopoly",sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    back_dado1.setPosition(0,0);
    back_dado2.setPosition(150,0);

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
        window.draw(back_dado1);
        window.draw(back_dado2);

        window.display();
    }


    return 0;
}
