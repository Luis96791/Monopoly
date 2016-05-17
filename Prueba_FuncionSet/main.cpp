#include <SFML/Graphics.hpp>

#include <fstream>
#include <iostream>

using namespace std;

class Ventana{
public:
    sf::Texture texture;
    sf::Texture* texture1;
    sf::Sprite sprite;
    sf::Sprite* sprite1;
    void miVentana(){

        sf::RenderWindow window(sf::VideoMode(600,600), "SFML works!");

        texture1 = &texture;
        sprite1 = &sprite;

        texture1->loadFromFile("ficha_azul.png");
        sprite1->setTexture(*texture1);
        int dados;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }


            cout<<sprite1->getPosition().x<<endl;
            cout<<sprite1->getPosition().y<<endl;


            sprite1->setPosition(20,100);
            movimiento(sprite1);

            window.draw(*sprite1);
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
