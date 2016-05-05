#include "JugarMonopoly.h"

JugarMonopoly::JugarMonopoly()
{
    //ctor
}

vector<CrearJugador> JugarMonopoly::cargarJugadores()
{
    ifstream leer(nombre_archivo.c_str());
    string nombre, color;
    while(leer>>nombre&&leer>>color){
        cout<<nombre<<" , "<<color<<endl;
        jugadores.push_back(CrearJugador(nombre,color));
    }
    leer.close();
    return jugadores;
}


void JugarMonopoly::ventanaTablero()
{
    sf::RenderWindow window;
    sf::Texture text_tablero,text_dado_1,text_dado_2;
    sf::Sprite back_tablero,back_dado_1,back_dado_2;
    sf::Vector2f mouse;
    int suma_dados,guardar_dado_1,guardar_dado_2;

    window.create(sf::VideoMode(1360,690,32),"Monopoly",sf::Style::Default);
    window.setVerticalSyncEnabled(true);

    guardar_dado_1=utility.dadoUno();
    guardar_dado_2=utility.dadoDos();
    suma_dados=guardar_dado_1+guardar_dado_2;

    text_tablero.loadFromFile("tablero.png");
    back_tablero.setTexture(text_tablero);
    text_dado_1.loadFromFile("dados/"+utility.toString(guardar_dado_1)+".png");
    back_dado_1.setTexture(text_dado_1);
    text_dado_2.loadFromFile("dados/"+utility.toString(guardar_dado_2)+".png");
    back_dado_2.setTexture(text_dado_2);
    //cout<<suma_dados<<endl;

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
                guardar_dado_1=utility.dadoUno();
                guardar_dado_2=utility.dadoDos();
                suma_dados=guardar_dado_1+guardar_dado_2;

                text_dado_1.loadFromFile("dados/"+utility.toString(guardar_dado_1)+".png");
                back_dado_1.setTexture(text_dado_1);
                text_dado_2.loadFromFile("dados/"+utility.toString(guardar_dado_2)+".png");
                back_dado_2.setTexture(text_dado_2);
                //cout<<suma_dados<<endl;
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
