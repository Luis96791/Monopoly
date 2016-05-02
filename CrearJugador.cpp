#include "CrearJugador.h"

CrearJugador::CrearJugador(string n)
{
    nombre = n;
    capital = 1500;
}

void CrearJugador::nuevoJugador(string n){
    jugadores_ingresados.push_back(CrearJugador(n));
    string extension = "titulos_de_propiedad/"+n+".txt";
    jugadores_ingresados.push_back(n);
    ofstream out(extension.c_str());
}



void CrearJugador::ventanaCrearJugador(){
    sf::RenderWindow window;
    sf::Texture text_registrar,text_ficha_amarilla,text_ficha_azul,text_ficha_blanca,
    text_ficha_naranja,text_ficha_roja,text_ficha_verde;
    sf::Sprite back_registrar,back_ficha_amarilla,back_ficha_azul,back_ficha_blanca,
    back_ficha_naranja,back_ficha_roja,back_ficha_verde;
    sf::Font fuente;
    sf::String nombre_jugador;
    sf::Text txt_nombre_jugador;

    window.create(sf::VideoMode(650,650,32),"Registrar Jugadores",sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::Vector2f mouse;

    text_registrar.loadFromFile("ventanas/registro.png");
    back_registrar.setTexture(text_registrar);

    text_ficha_amarilla.loadFromFile("fichas/ficha_amarilla.png");
    back_ficha_amarilla.setTexture(text_ficha_amarilla);

    text_ficha_azul.loadFromFile("fichas/ficha_azul.png");
    back_ficha_azul.setTexture(text_ficha_azul);

    text_ficha_blanca.loadFromFile("fichas/ficha_blanca.png");
    back_ficha_blanca.setTexture(text_ficha_blanca);

    text_ficha_naranja.loadFromFile("fichas/ficha_naranja.png");
    back_ficha_naranja.setTexture(text_ficha_naranja);

    text_ficha_roja.loadFromFile("fichas/ficha_roja.png");
    back_ficha_roja.setTexture(text_ficha_roja);

    text_ficha_verde.loadFromFile("fichas/ficha_verde.png");
    back_ficha_verde.setTexture(text_ficha_verde);

    back_ficha_amarilla.setPosition(44,285);
    back_ficha_azul.setPosition(125,285);
    back_ficha_blanca.setPosition(205,285);
    back_ficha_naranja.setPosition(44,370);
    back_ficha_roja.setPosition(125,370);
    back_ficha_verde.setPosition(205,370);

    if(!fuente.loadFromFile("arial.ttf")){}

    //cargar y mostrar archivo ttf
    txt_nombre_jugador.setFont(fuente);
    txt_nombre_jugador.setCharacterSize(72);
    txt_nombre_jugador.setColor(sf::Color::White);
    txt_nombre_jugador.setPosition(250,115);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
            }

            if(event.type==sf::Event::TextEntered)
            {
                nombre_jugador.insert(nombre_jugador.getSize(),event.text.unicode);
                txt_nombre_jugador.setString(nombre_jugador);
            }
        }

        mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if(utility.clickSprite(back_ficha_amarilla,mouse)){
            text_ficha_amarilla.loadFromFile("ventanas/enabled.png");
            back_ficha_amarilla.setTexture(text_ficha_amarilla);
        }

        if(utility.clickSprite(back_ficha_azul,mouse)){
            text_ficha_azul.loadFromFile("ventanas/enabled.png");
            back_ficha_azul.setTexture(text_ficha_azul);
        }

        if(utility.clickSprite(back_ficha_blanca,mouse)){
            text_ficha_blanca.loadFromFile("ventanas/enabled.png");
            back_ficha_blanca.setTexture(text_ficha_blanca);
        }

        if(utility.clickSprite(back_ficha_naranja,mouse)){
            text_ficha_naranja.loadFromFile("ventanas/enabled.png");
            back_ficha_naranja.setTexture(text_ficha_naranja);
        }

        if(utility.clickSprite(back_ficha_roja,mouse)){
            text_ficha_roja.loadFromFile("ventanas/enabled.png");
            back_ficha_roja.setTexture(text_ficha_roja);
        }

        if(utility.clickSprite(back_ficha_verde,mouse)){
            text_ficha_verde.loadFromFile("ventanas/enabled.png");
            back_ficha_verde.setTexture(text_ficha_verde);
        }


        window.draw(back_registrar);
        window.draw(txt_nombre_jugador);
        window.draw(back_ficha_amarilla);
        window.draw(back_ficha_azul);
        window.draw(back_ficha_blanca);
        window.draw(back_ficha_naranja);
        window.draw(back_ficha_roja);
        window.draw(back_ficha_verde);
        window.display();
    }
}

void CrearJugador::removerJugadores()
{

    for(unsigned int c=0;c<jugadores_ingresados.size();c++)
    {
        string k ="titulos_de_propiedad/"+jugadores_ingresados.at(c).nombre+".txt";
        remove(k.c_str());
    }
}

CrearJugador::~CrearJugador()
{
    removerJugadores();
}
