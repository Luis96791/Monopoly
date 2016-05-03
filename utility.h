#ifndef UTILITY_H
#define UTILITY_H
#include <stdlib.h>
#include <iostream>

#include <SFML/Graphics.hpp>

using namespace std;

class Utility
{
    public:
        string toString(int number);
        int dadoUno();
        int dadoDos();
        bool clickSprite(sf::Sprite s, sf::Vector2f mouse);
};

#endif // UTILITY_H
