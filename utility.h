#ifndef UTILITY_H
#define UTILITY_H
#include <stdlib.h>
#include <iostream>
#include <conio.h>

#include <SFML/Graphics.hpp>

using namespace std;

class Utility
{
    public:
        string toString(int number);
        int dadoUno();
        int dadoDos();
        bool clickSprite(sf::Sprite s, sf::Vector2f mouse);
        bool clickText(sf::Text s, sf::Vector2f mouse);
        int pressedDel(char tecla);
};

#endif // UTILITY_H
