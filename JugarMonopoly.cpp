#include "JugarMonopoly.h"

JugarMonopoly::JugarMonopoly()
{
    //ctor
}

void JugarMonopoly::ventanaTablero()
{
    sf::RenderWindow window;
    sf::Texture text_tablero,text_dado_1,text_dado_2;
    sf::Sprite back_tablero,back_dado_1,back_dado_2;
    sf::Vector2f mouse;


    window.create(sf::VideoMode(1360,690,32),"Monopoly",sf::Style::Default);
    window.setVerticalSyncEnabled(true);

    text_tablero.loadFromFile("tablero.png");
    back_tablero.setTexture(text_tablero);
    text_dado_1.loadFromFile("dados/"+utility.toString(utility.dadoUno())+".png");
    back_dado_1.setTexture(text_dado_1);
    text_dado_2.loadFromFile("dados/"+utility.toString(utility.dadoDos())+".png");
    back_dado_2.setTexture(text_dado_2);

    back_dado_1.setPosition(1140,580);
    back_dado_2.setPosition(1250,580);

     while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if(utility.clickSprite(back_dado_1,mouse)||utility.clickSprite(back_dado_2,mouse))
            {
                text_dado_1.loadFromFile("dados/"+utility.toString(utility.dadoUno())+".png");
                back_dado_1.setTexture(text_dado_1);
                text_dado_2.loadFromFile("dados/"+utility.toString(utility.dadoDos())+".png");
                back_dado_2.setTexture(text_dado_2);
            }
        }

        window.draw(back_tablero);
        window.draw(back_dado_1);
        window.draw(back_dado_2);
        window.display();
    }
}

JugarMonopoly::~JugarMonopoly()
{
    //dtor
}
