#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window;

    window.create(sf::VideoMode(840,620,32),"Monopoly",sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.draw(shape);
        window.display();
    }

    return 0;
}
