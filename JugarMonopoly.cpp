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

sf::Sprite JugarMonopoly::moverFichaPorDados(sf::Sprite back_ficha_1,int suma_dados)
{
//    if(suma_dados==2){
//        back_ficha_1.setPosition(495,640);
//        return back_ficha_1;
//    }
//    if(suma_dados==3){
//        back_ficha_1.setPosition(440,640);
//        return back_ficha_1;
//    }
//    if(suma_dados==4){
//        back_ficha_1.setPosition(385,640);
//        return back_ficha_1;
//    }
//    if(suma_dados==5){
//        back_ficha_1.setPosition(325,640);
//        return back_ficha_1;
//    }
//    if(suma_dados==6){
//        back_ficha_1.setPosition(270,640);
//        cout<<"Validado..."<<endl;
//        return back_ficha_1;
//    }
}

void JugarMonopoly::ventanaTablero()
{
    sf::RenderWindow window;
    sf::Texture text_tablero,text_dado_1,text_dado_2,text_ficha_1,text_ficha_2,text_ficha_3,text_ficha_4,text_ficha_5,text_ficha_6;
    sf::Sprite back_tablero,back_dado_1,back_dado_2,back_ficha_1,back_ficha_2,back_ficha_3,back_ficha_4,back_ficha_5,back_ficha_6;
    sf::Vector2f mouse;
    sf::Mouse mouse_position;
    int suma_dados,guardar_dado_1,guardar_dado_2;

    cargarJugadores();

    window.create(sf::VideoMode(1360,690,32),"Monopoly",sf::Style::Default);
    window.setVerticalSyncEnabled(true);

    guardar_dado_1=utility.dadoUno();
    guardar_dado_2=utility.dadoDos();
    suma_dados=guardar_dado_1+guardar_dado_2;

    text_tablero.loadFromFile("tablero.png");
    back_tablero.setTexture(text_tablero);
    text_dado_1.loadFromFile("dados/1.png");
    back_dado_1.setTexture(text_dado_1);
    text_dado_2.loadFromFile("dados/1.png");
    back_dado_2.setTexture(text_dado_2);

    text_ficha_1.loadFromFile("fichas_tablero/ficha_azul.png");
    back_ficha_1.setTexture(text_ficha_1);
    back_ficha_1.setPosition(640,640);
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

            if(back_ficha_1.getPosition().x==640&&back_ficha_1.getPosition().y==640)
            {
                if(suma_dados==2){back_ficha_1.setPosition(495,640);}
                if(suma_dados==3){back_ficha_1.setPosition(440,640);}
                if(suma_dados==4){back_ficha_1.setPosition(385,640);}
                if(suma_dados==5){back_ficha_1.setPosition(325,640);}
                if(suma_dados==6){back_ficha_1.setPosition(270,640);}
                if(suma_dados==7){back_ficha_1.setPosition(215,640);}
                if(suma_dados==8){back_ficha_1.setPosition(160,640);}
                if(suma_dados==9){back_ficha_1.setPosition(105,640);}
                if(suma_dados==10){back_ficha_1.setPosition(20,640);}
                if(suma_dados==11){back_ficha_1.setPosition(20,555);}
                if(suma_dados==12){back_ficha_1.setPosition(20,495);}
            }
            if(back_ficha_1.getPosition().x==555&&back_ficha_1.getPosition().y==640)
            {
                if(suma_dados==2){back_ficha_1.setPosition(440,640);}
                if(suma_dados==3){back_ficha_1.setPosition(385,640);}
                if(suma_dados==4){back_ficha_1.setPosition(325,640);}
                if(suma_dados==5){back_ficha_1.setPosition(270,640);}
                if(suma_dados==6){back_ficha_1.setPosition(215,640);}
                if(suma_dados==7){back_ficha_1.setPosition(160,640);}
                if(suma_dados==8){back_ficha_1.setPosition(105,640);}
                if(suma_dados==9){back_ficha_1.setPosition(20,640);}
                if(suma_dados==10){back_ficha_1.setPosition(555,20);}
                if(suma_dados==11){back_ficha_1.setPosition(495,20);}
                if(suma_dados==12){back_ficha_1.setPosition(440,20);}
            }
            if(back_ficha_1.getPosition().x==495&&back_ficha_1.getPosition().y==640)
            {
                if(suma_dados==2){back_ficha_1.setPosition(385,640);}
                if(suma_dados==3){back_ficha_1.setPosition(325,640);}
                if(suma_dados==4){back_ficha_1.setPosition(270,640);}
                if(suma_dados==5){back_ficha_1.setPosition(215,640);}
                if(suma_dados==6){back_ficha_1.setPosition(160,640);}
                if(suma_dados==7){back_ficha_1.setPosition(105,640);}
                if(suma_dados==8){back_ficha_1.setPosition(20,640);}
                if(suma_dados==9){back_ficha_1.setPosition(555,20);}
                if(suma_dados==10){back_ficha_1.setPosition(495,20);}
                if(suma_dados==11){back_ficha_1.setPosition(440,20);}
                if(suma_dados==12){back_ficha_1.setPosition(385,20);}
            }
            if(back_ficha_1.getPosition().x==440&&back_ficha_1.getPosition().y==640)
            {
                if(suma_dados==2){back_ficha_1.setPosition(325,640);}
                if(suma_dados==3){back_ficha_1.setPosition(270,640);}
                if(suma_dados==4){back_ficha_1.setPosition(215,640);}
                if(suma_dados==5){back_ficha_1.setPosition(160,640);}
                if(suma_dados==6){back_ficha_1.setPosition(105,640);}
                if(suma_dados==7){back_ficha_1.setPosition(20,640);}
                if(suma_dados==8){back_ficha_1.setPosition(555,20);}
                if(suma_dados==9){back_ficha_1.setPosition(495,20);}
                if(suma_dados==10){back_ficha_1.setPosition(440,20);}
                if(suma_dados==11){back_ficha_1.setPosition(385,20);}
                if(suma_dados==12){back_ficha_1.setPosition(325,20);}
            }
            if(back_ficha_1.getPosition().x==385&&back_ficha_1.getPosition().y==640)
            {
                if(suma_dados==2){back_ficha_1.setPosition(270,640);}
                if(suma_dados==3){back_ficha_1.setPosition(215,640);}
                if(suma_dados==4){back_ficha_1.setPosition(160,640);}
                if(suma_dados==5){back_ficha_1.setPosition(105,640);}
                if(suma_dados==6){back_ficha_1.setPosition(20,640);}
                if(suma_dados==7){back_ficha_1.setPosition(555,20);}
                if(suma_dados==8){back_ficha_1.setPosition(495,20);}
                if(suma_dados==9){back_ficha_1.setPosition(440,20);}
                if(suma_dados==10){back_ficha_1.setPosition(385,20);}
                if(suma_dados==11){back_ficha_1.setPosition(325,20);}
                if(suma_dados==12){back_ficha_1.setPosition(270,20);}
            }
            if(back_ficha_1.getPosition().x==325&&back_ficha_1.getPosition().y==640)
            {
                if(suma_dados==2){back_ficha_1.setPosition(215,640);}
                if(suma_dados==3){back_ficha_1.setPosition(160,640);}
                if(suma_dados==4){back_ficha_1.setPosition(105,640);}
                if(suma_dados==5){back_ficha_1.setPosition(20,640);}
                if(suma_dados==6){back_ficha_1.setPosition(555,20);}
                if(suma_dados==7){back_ficha_1.setPosition(495,20);}
                if(suma_dados==8){back_ficha_1.setPosition(440,20);}
                if(suma_dados==9){back_ficha_1.setPosition(385,20);}
                if(suma_dados==10){back_ficha_1.setPosition(325,20);}
                if(suma_dados==11){back_ficha_1.setPosition(270,20);}
                if(suma_dados==12){back_ficha_1.setPosition(215,20);}
            }
            if(back_ficha_1.getPosition().x==270&&back_ficha_1.getPosition().y==640)
            {
                if(suma_dados==2){back_ficha_1.setPosition(160,640);}
                if(suma_dados==3){back_ficha_1.setPosition(105,640);}
                if(suma_dados==4){back_ficha_1.setPosition(20,640);}
                if(suma_dados==5){back_ficha_1.setPosition(555,20);}
                if(suma_dados==6){back_ficha_1.setPosition(495,20);}
                if(suma_dados==7){back_ficha_1.setPosition(440,20);}
                if(suma_dados==8){back_ficha_1.setPosition(385,20);}
                if(suma_dados==9){back_ficha_1.setPosition(325,20);}
                if(suma_dados==10){back_ficha_1.setPosition(270,20);}
                if(suma_dados==11){back_ficha_1.setPosition(215,20);}
                if(suma_dados==12){back_ficha_1.setPosition(160,20);}
            }
            if(back_ficha_1.getPosition().x==215&&back_ficha_1.getPosition().y==640)
            {
                if(suma_dados==2){back_ficha_1.setPosition(105,640);}
                if(suma_dados==3){back_ficha_1.setPosition(20,640);}
                if(suma_dados==4){back_ficha_1.setPosition(555,20);}
                if(suma_dados==5){back_ficha_1.setPosition(495,20);}
                if(suma_dados==6){back_ficha_1.setPosition(440,20);}
                if(suma_dados==7){back_ficha_1.setPosition(385,20);}
                if(suma_dados==8){back_ficha_1.setPosition(325,20);}
                if(suma_dados==9){back_ficha_1.setPosition(270,20);}
                if(suma_dados==10){back_ficha_1.setPosition(215,20);}
                if(suma_dados==11){back_ficha_1.setPosition(160,20);}
                if(suma_dados==12){back_ficha_1.setPosition(105,20);}
            }
            if(back_ficha_1.getPosition().x==160&&back_ficha_1.getPosition().y==640)
            {
                if(suma_dados==2){back_ficha_1.setPosition(20,640);}
                if(suma_dados==3){back_ficha_1.setPosition(555,20);}
                if(suma_dados==4){back_ficha_1.setPosition(495,20);}
                if(suma_dados==5){back_ficha_1.setPosition(440,20);}
                if(suma_dados==6){back_ficha_1.setPosition(385,20);}
                if(suma_dados==7){back_ficha_1.setPosition(325,20);}
                if(suma_dados==8){back_ficha_1.setPosition(270,20);}
                if(suma_dados==9){back_ficha_1.setPosition(215,20);}
                if(suma_dados==10){back_ficha_1.setPosition(160,20);}
                if(suma_dados==11){back_ficha_1.setPosition(105,20);}
                if(suma_dados==12){back_ficha_1.setPosition(20,20);}
            }
            if(back_ficha_1.getPosition().x==105&&back_ficha_1.getPosition().y==640)
            {
                if(suma_dados==2){back_ficha_1.setPosition(555,20);}
                if(suma_dados==3){back_ficha_1.setPosition(495,20);}
                if(suma_dados==4){back_ficha_1.setPosition(440,20);}
                if(suma_dados==5){back_ficha_1.setPosition(385,20);}
                if(suma_dados==6){back_ficha_1.setPosition(325,20);}
                if(suma_dados==7){back_ficha_1.setPosition(270,20);}
                if(suma_dados==8){back_ficha_1.setPosition(215,20);}
                if(suma_dados==9){back_ficha_1.setPosition(160,20);}
                if(suma_dados==10){back_ficha_1.setPosition(105,20);}
                if(suma_dados==11){back_ficha_1.setPosition(20,20);}
                if(suma_dados==12){back_ficha_1.setPosition(20,105);}
            }
            if(back_ficha_1.getPosition().x==20&&back_ficha_1.getPosition().y==640)
            {
                if(suma_dados==2){back_ficha_1.setPosition(495,20);}
                if(suma_dados==3){back_ficha_1.setPosition(440,20);}
                if(suma_dados==4){back_ficha_1.setPosition(385,20);}
                if(suma_dados==5){back_ficha_1.setPosition(325,20);}
                if(suma_dados==6){back_ficha_1.setPosition(270,20);}
                if(suma_dados==7){back_ficha_1.setPosition(215,20);}
                if(suma_dados==8){back_ficha_1.setPosition(160,20);}
                if(suma_dados==9){back_ficha_1.setPosition(105,20);}
                if(suma_dados==10){back_ficha_1.setPosition(20,20);}
                if(suma_dados==11){back_ficha_1.setPosition(20,105);}
                if(suma_dados==12){back_ficha_1.setPosition(20,160);}
            }
            if(back_ficha_1.getPosition().x==20&&back_ficha_1.getPosition().y==555)
            {
                if(suma_dados==2){back_ficha_1.setPosition(440,20);}
                if(suma_dados==3){back_ficha_1.setPosition(385,20);}
                if(suma_dados==4){back_ficha_1.setPosition(325,20);}
                if(suma_dados==5){back_ficha_1.setPosition(270,20);}
                if(suma_dados==6){back_ficha_1.setPosition(215,20);}
                if(suma_dados==7){back_ficha_1.setPosition(160,20);}
                if(suma_dados==8){back_ficha_1.setPosition(105,20);}
                if(suma_dados==9){back_ficha_1.setPosition(20,20);}
                if(suma_dados==10){back_ficha_1.setPosition(20,105);}
                if(suma_dados==11){back_ficha_1.setPosition(20,160);}
                if(suma_dados==12){back_ficha_1.setPosition(20,215);}
            }
            if(back_ficha_1.getPosition().x==20&&back_ficha_1.getPosition().y==495)
            {
                if(suma_dados==2){back_ficha_1.setPosition(385,20);}
                if(suma_dados==3){back_ficha_1.setPosition(325,20);}
                if(suma_dados==4){back_ficha_1.setPosition(270,20);}
                if(suma_dados==5){back_ficha_1.setPosition(215,20);}
                if(suma_dados==6){back_ficha_1.setPosition(160,20);}
                if(suma_dados==7){back_ficha_1.setPosition(105,20);}
                if(suma_dados==8){back_ficha_1.setPosition(20,20);}
                if(suma_dados==9){back_ficha_1.setPosition(20,105);}
                if(suma_dados==10){back_ficha_1.setPosition(20,160);}
                if(suma_dados==11){back_ficha_1.setPosition(20,215);}
                if(suma_dados==12){back_ficha_1.setPosition(20,270);}
            }
            if(back_ficha_1.getPosition().x==20&&back_ficha_1.getPosition().y==440)
            {
                if(suma_dados==2){back_ficha_1.setPosition(325,20);}
                if(suma_dados==3){back_ficha_1.setPosition(270,20);}
                if(suma_dados==4){back_ficha_1.setPosition(215,20);}
                if(suma_dados==5){back_ficha_1.setPosition(160,20);}
                if(suma_dados==6){back_ficha_1.setPosition(105,20);}
                if(suma_dados==7){back_ficha_1.setPosition(20,20);}
                if(suma_dados==8){back_ficha_1.setPosition(20,105);}
                if(suma_dados==9){back_ficha_1.setPosition(20,160);}
                if(suma_dados==10){back_ficha_1.setPosition(20,215);}
                if(suma_dados==11){back_ficha_1.setPosition(20,270);}
                if(suma_dados==12){back_ficha_1.setPosition(20,325);}
            }
            if(back_ficha_1.getPosition().x==20&&back_ficha_1.getPosition().y==385)
            {
                if(suma_dados==2){back_ficha_1.setPosition(270,20);}
                if(suma_dados==3){back_ficha_1.setPosition(215,20);}
                if(suma_dados==4){back_ficha_1.setPosition(160,20);}
                if(suma_dados==5){back_ficha_1.setPosition(105,20);}
                if(suma_dados==6){back_ficha_1.setPosition(20,20);}
                if(suma_dados==7){back_ficha_1.setPosition(20,105);}
                if(suma_dados==8){back_ficha_1.setPosition(20,160);}
                if(suma_dados==9){back_ficha_1.setPosition(20,215);}
                if(suma_dados==10){back_ficha_1.setPosition(20,270);}
                if(suma_dados==11){back_ficha_1.setPosition(20,325);}
                if(suma_dados==12){back_ficha_1.setPosition(20,385);}
            }
            if(back_ficha_1.getPosition().x==20&&back_ficha_1.getPosition().y==325)
            {
                if(suma_dados==2){back_ficha_1.setPosition(215,20);}
                if(suma_dados==3){back_ficha_1.setPosition(160,20);}
                if(suma_dados==4){back_ficha_1.setPosition(105,20);}
                if(suma_dados==5){back_ficha_1.setPosition(20,20);}
                if(suma_dados==6){back_ficha_1.setPosition(20,105);}
                if(suma_dados==7){back_ficha_1.setPosition(20,160);}
                if(suma_dados==8){back_ficha_1.setPosition(20,215);}
                if(suma_dados==9){back_ficha_1.setPosition(20,270);}
                if(suma_dados==10){back_ficha_1.setPosition(20,325);}
                if(suma_dados==11){back_ficha_1.setPosition(20,385);}
                if(suma_dados==12){back_ficha_1.setPosition(20,440);}
            }
            if(back_ficha_1.getPosition().x==20&&back_ficha_1.getPosition().y==270)
            {
                if(suma_dados==2){back_ficha_1.setPosition(160,20);}
                if(suma_dados==3){back_ficha_1.setPosition(105,20);}
                if(suma_dados==4){back_ficha_1.setPosition(20,20);}
                if(suma_dados==5){back_ficha_1.setPosition(20,105);}
                if(suma_dados==6){back_ficha_1.setPosition(20,160);}
                if(suma_dados==7){back_ficha_1.setPosition(20,215);}
                if(suma_dados==8){back_ficha_1.setPosition(20,270);}
                if(suma_dados==9){back_ficha_1.setPosition(20,325);}
                if(suma_dados==10){back_ficha_1.setPosition(20,385);}
                if(suma_dados==11){back_ficha_1.setPosition(20,440);}
                if(suma_dados==12){back_ficha_1.setPosition(20,495);}
            }
            if(back_ficha_1.getPosition().x==20&&back_ficha_1.getPosition().y==215)
            {
                if(suma_dados==2){back_ficha_1.setPosition(105,20);}
                if(suma_dados==3){back_ficha_1.setPosition(20,20);}
                if(suma_dados==4){back_ficha_1.setPosition(20,105);}
                if(suma_dados==5){back_ficha_1.setPosition(20,160);}
                if(suma_dados==6){back_ficha_1.setPosition(20,215);}
                if(suma_dados==7){back_ficha_1.setPosition(20,270);}
                if(suma_dados==8){back_ficha_1.setPosition(20,325);}
                if(suma_dados==9){back_ficha_1.setPosition(20,385);}
                if(suma_dados==10){back_ficha_1.setPosition(20,440);}
                if(suma_dados==11){back_ficha_1.setPosition(20,495);}
                if(suma_dados==12){back_ficha_1.setPosition(20,555);}
            }
            if(back_ficha_1.getPosition().x==20&&back_ficha_1.getPosition().y==160)
            {
                if(suma_dados==2){back_ficha_1.setPosition(20,20);}
                if(suma_dados==3){back_ficha_1.setPosition(20,105);}
                if(suma_dados==4){back_ficha_1.setPosition(20,160);}
                if(suma_dados==5){back_ficha_1.setPosition(20,215);}
                if(suma_dados==6){back_ficha_1.setPosition(20,270);}
                if(suma_dados==7){back_ficha_1.setPosition(20,325);}
                if(suma_dados==8){back_ficha_1.setPosition(20,385);}
                if(suma_dados==9){back_ficha_1.setPosition(20,440);}
                if(suma_dados==10){back_ficha_1.setPosition(20,495);}
                if(suma_dados==11){back_ficha_1.setPosition(20,555);}
                if(suma_dados==12){back_ficha_1.setPosition(20,640);}
            }
            if(back_ficha_1.getPosition().x==20&&back_ficha_1.getPosition().y==105)
            {
                if(suma_dados==2){back_ficha_1.setPosition(20,105);}
                if(suma_dados==3){back_ficha_1.setPosition(20,160);}
                if(suma_dados==4){back_ficha_1.setPosition(20,215);}
                if(suma_dados==5){back_ficha_1.setPosition(20,270);}
                if(suma_dados==6){back_ficha_1.setPosition(20,325);}
                if(suma_dados==7){back_ficha_1.setPosition(20,385);}
                if(suma_dados==8){back_ficha_1.setPosition(20,440);}
                if(suma_dados==9){back_ficha_1.setPosition(20,495);}
                if(suma_dados==10){back_ficha_1.setPosition(20,555);}
                if(suma_dados==11){back_ficha_1.setPosition(20,640);}
                if(suma_dados==12){back_ficha_1.setPosition(105,640);}
            }
            if(back_ficha_1.getPosition().x==20&&back_ficha_1.getPosition().y==20)
            {
                if(suma_dados==2){back_ficha_1.setPosition(20,160);}
                if(suma_dados==3){back_ficha_1.setPosition(20,215);}
                if(suma_dados==4){back_ficha_1.setPosition(20,270);}
                if(suma_dados==5){back_ficha_1.setPosition(20,325);}
                if(suma_dados==6){back_ficha_1.setPosition(20,385);}
                if(suma_dados==7){back_ficha_1.setPosition(20,440);}
                if(suma_dados==8){back_ficha_1.setPosition(20,495);}
                if(suma_dados==9){back_ficha_1.setPosition(20,555);}
                if(suma_dados==10){back_ficha_1.setPosition(20,640);}
                if(suma_dados==11){back_ficha_1.setPosition(105,640);}
                if(suma_dados==12){back_ficha_1.setPosition(160,640);}
            }

        }



        window.draw(back_tablero);
        window.draw(back_dado_1);
        window.draw(back_dado_2);
        window.draw(back_ficha_1);
        window.display();
    }
}

JugarMonopoly::~JugarMonopoly()
{
//    remove(nombre_archivo.c_str());
}
