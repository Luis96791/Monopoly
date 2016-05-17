#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>

using namespace std;

class Ventana{
public:
    sf::Texture texture;
    sf::Texture* texture1;
    sf::Sprite* sprite1;
    sf::Sprite sprite2;
    void miVentana(){

        sf::RenderWindow window(sf::VideoMode(600,600), "SFML works!");

        texture1->loadFromFile("ficha_azul.png");
        sprite1->setTexture(*texture1);
        texture.loadFromFile("ficha_naranja.png");
        sprite2.setTexture(texture);
        int dados;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }


            sprite1->setPosition(20,100);
            movimiento(sprite1);

            window.draw(*sprite1);
            window.draw(sprite2);
            window.display();
        }
    }

    void movimiento(sf::Sprite* sprite){
        if(sprite->getPosition().x==20&&sprite->getPosition().y==100){
            sprite->setPosition(100,100);
        }
    }
};



int main()
{
    Ventana v;
    v.miVentana();
    return 0;
}
