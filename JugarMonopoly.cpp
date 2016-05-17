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

/**
*   Esta es una Prueba en busca de optimizar la funcion movimiento :|
*/

sf::Sprite JugarMonopoly::movimiento(sf::Sprite* ficha,int suma_dados)
{
    int getPositionX, getPositionY, dado_file, setPositionX, setPositionY;

     ifstream out1("setPositions.txt");
        while(out1>>getPositionX&&out1>>getPositionY&&out1>>dado_file&&out1>>setPositionX&&out1>>setPositionY){
            if(ficha->getPosition().x==getPositionX&&ficha->getPosition().y==getPositionY&&suma_dados==dado_file){
                cout<<"entrando..."<<endl;
                ficha->setPosition(setPositionX,setPositionY);
                return *ficha;
            }
        }
        out1.close();
        return *ficha;
}
/**
*   Esta es una Prueba en busca de optimizar la funcion movimiento ;)
*/

void JugarMonopoly::ventanaTablero()
{
    sf::RenderWindow window;

    sf::Texture text_tablero,text_dado_1,text_dado_2,text_ficha_3,text_ficha_4,text_ficha_5,text_ficha_6;
    sf::Texture ref_text_ficha_1,ref_text_ficha_2;
    sf::Texture *text_ficha_1, *text_ficha_2;

    sf::Sprite back_tablero,back_dado_1,back_dado_2,back_ficha_3,back_ficha_4,back_ficha_5,back_ficha_6;
    sf::Sprite ref_back_ficha_1,ref_back_ficha_2;
    sf::Sprite *back_ficha_1, *back_ficha_2;

    sf::Vector2f mouse;
    sf::Font font;
    sf::Text txt_jugador_1, txt_jugador_2;
    int suma_dados,guardar_dado_1,guardar_dado_2,clicks=0;
    string nombre_jugador_1, nombre_jugador_2;
    int capital_jugador_1;

    nombre_archivo = "jugadores.txt";

    cargarJugadores();

    window.create(sf::VideoMode(1360,690,32),"Monopoly",sf::Style::Default);
    window.setVerticalSyncEnabled(true);

    text_ficha_1 = &ref_text_ficha_1;
    text_ficha_2 = &ref_text_ficha_2;

    back_ficha_1 = &ref_back_ficha_1;
    back_ficha_2 = &ref_back_ficha_2;

    if(!font.loadFromFile("arial.ttf")){}
    txt_jugador_1.setFont(font);
    txt_jugador_1.setCharacterSize(24);
    txt_jugador_1.setColor(sf::Color::Blue);
    txt_jugador_1.setPosition(1000,10);

    txt_jugador_2.setFont(font);
    txt_jugador_2.setCharacterSize(24);
    txt_jugador_2.setColor(sf::Color::Red);
    txt_jugador_2.setPosition(1000,40);

    text_tablero.loadFromFile("tablero.png");
    back_tablero.setTexture(text_tablero);
    text_dado_1.loadFromFile("dados/1.png");
    back_dado_1.setTexture(text_dado_1);
    text_dado_2.loadFromFile("dados/1.png");
    back_dado_2.setTexture(text_dado_2);

    ifstream cargar("jugadores.txt");
    string n, f;
    bool ficha1,ficha2,ficha3,ficha4,ficha5,ficha6;
    while(cargar>>n&&cargar>>f){
            cout<<f<<endl;
        if(f=="ficha_azul"){
            text_ficha_1->loadFromFile("fichas_tablero/ficha_azul.png");
            back_ficha_1->setTexture(*text_ficha_1);
            back_ficha_1->setPosition(640,640);
            ficha1=true;
        }
        if(f=="ficha_roja"){
            text_ficha_2->loadFromFile("fichas_tablero/ficha_roja.png");
            back_ficha_2->setTexture(*text_ficha_2);
            back_ficha_2->setPosition(640,640);
            ficha2=true;
        }
        if(f=="ficha_verde"){
            text_ficha_3.loadFromFile("fichas_tablero/ficha_verde.png");
            back_ficha_3.setTexture(text_ficha_3);
            back_ficha_3.setPosition(640,640);
            ficha3=true;
        }
        if(f=="ficha_amarilla"){
            text_ficha_4.loadFromFile("fichas_tablero/ficha_amarilla.png");
            back_ficha_4.setTexture(text_ficha_4);
            back_ficha_4.setPosition(640,640);
            ficha4=true;
        }
        if(f=="ficha_blanca"){
            text_ficha_5.loadFromFile("fichas_tablero/ficha_blanca.png");
            back_ficha_5.setTexture(text_ficha_5);
            back_ficha_5.setPosition(640,640);
            ficha5=true;
        }
        if(f=="ficha_naranja"){
            text_ficha_6.loadFromFile("fichas_tablero/ficha_naranja.png");
            back_ficha_6.setTexture(text_ficha_6);
            back_ficha_6.setPosition(640,640);
            ficha6=true;
        }
    }
    cargar.close();

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
                cout<<clicks++<<endl;
                guardar_dado_1=utility.dadoUno();
                guardar_dado_2=utility.dadoDos();
                suma_dados=guardar_dado_1+guardar_dado_2;

                text_dado_1.loadFromFile("dados/"+utility.toString(guardar_dado_1)+".png");
                back_dado_1.setTexture(text_dado_1);
                text_dado_2.loadFromFile("dados/"+utility.toString(guardar_dado_2)+".png");
                back_dado_2.setTexture(text_dado_2);
                cout<<suma_dados<<endl;

                //cout<<suma_dados<<endl;
            }

            //PROBANDO TABLERO
        }
        txt_jugador_1.setString(jugadores[0].getNombre()+"     "+utility.toString(jugadores[0].getCapital()));
        txt_jugador_2.setString(jugadores[1].getNombre()+"     "+utility.toString(jugadores[1].getCapital()));
//        nombre_jugador_1 = jugadores[0].getNombre();
//        capital_jugador_1 = jugadores[0].getCapital();
//        cout<<nombre_jugador_1<<endl;
//        cout<<capital_jugador_1<<endl;

        if(clicks%2==0){
            movimiento(back_ficha_1,suma_dados);
            suma_dados=0;
        }else{
            movimiento(back_ficha_2,suma_dados);
            suma_dados=0;
        }

        window.draw(back_tablero);
        window.draw(back_dado_1);
        window.draw(back_dado_2);
        window.draw(txt_jugador_1);
        window.draw(txt_jugador_2);

        if(ficha1){window.draw(*back_ficha_1);}
        if(ficha2){window.draw(*back_ficha_2);}
        if(ficha3){window.draw(back_ficha_3);}
        if(ficha4){window.draw(back_ficha_4);}
        if(ficha5){window.draw(back_ficha_5);}
        if(ficha6){window.draw(back_ficha_6);}
        window.display();
    }
}

JugarMonopoly::~JugarMonopoly()
{
    remove(nombre_archivo.c_str());
}
