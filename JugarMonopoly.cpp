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

bool JugarMonopoly::mover(sf::Sprite ficha,int suma_dados)
{
    if(ficha.getPosition().y==640){
        if(suma_dados>0){
            return mover(ficha,suma_dados-1);
        }
    }
}

void JugarMonopoly::ventanaTablero()
{
    sf::RenderWindow window;
    sf::Texture text_tablero,text_dado_1,text_dado_2,text_ficha_1,text_ficha_2,text_ficha_3,text_ficha_4,text_ficha_5,text_ficha_6;
    sf::Sprite back_tablero,back_dado_1,back_dado_2,back_ficha_1,back_ficha_2,back_ficha_3,back_ficha_4,back_ficha_5,back_ficha_6;
    sf::Vector2f mouse;
    sf::Mouse mouse_position;
    int suma_dados,guardar_dado_1,guardar_dado_2,dado_prueba,m;

    int getPositionX, getPositionY, dado_file, setPositionX, setPositionY;

    cargarJugadores();

    window.create(sf::VideoMode(1360,690,32),"Monopoly",sf::Style::Default);
    window.setVerticalSyncEnabled(true);

    text_tablero.loadFromFile("tablero.png");
    back_tablero.setTexture(text_tablero);
    text_dado_1.loadFromFile("dados/1.png");
    back_dado_1.setTexture(text_dado_1);
    text_dado_2.loadFromFile("dados/1.png");
    back_dado_2.setTexture(text_dado_2);

    text_ficha_1.loadFromFile("fichas_tablero/ficha_azul.png");
    back_ficha_1.setTexture(text_ficha_1);
    back_ficha_1.setPosition(270,20);

    text_ficha_2.loadFromFile("fichas_tablero/ficha_roja.png");
    back_ficha_2.setTexture(text_ficha_2);
    back_ficha_2.setPosition(640,640);
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

            //PROBANDO TABLERO

            ifstream out("setPositions.txt");
            while(out>>getPositionX&&out>>getPositionY&&out>>dado_file&&out>>setPositionX&&out>>setPositionY){
                if(back_ficha_1.getPosition().x==getPositionX&&back_ficha_1.getPosition().y==getPositionY&&suma_dados==dado_file){
                    cout<<"entrando..."<<endl;
                    cout<<suma_dados<<endl;
                    back_ficha_1.setPosition(setPositionX,setPositionY);
                    suma_dados=0;
                }
            }
            out.close();
        }

//        if(mover(back_ficha_2,5)){
//            m=back_ficha_2.getPosition().x;
//            back_ficha_2.setPosition(m-85,640);
//            cout<<back_ficha_2.getPosition().x<<endl;
//        }

        window.draw(back_tablero);
        window.draw(back_dado_1);
        window.draw(back_dado_2);
        window.draw(back_ficha_1);
        window.draw(back_ficha_2);
        window.display();
    }
}

JugarMonopoly::~JugarMonopoly()
{
//    remove(nombre_archivo.c_str());
}
