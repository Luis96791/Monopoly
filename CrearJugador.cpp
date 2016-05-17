#include "CrearJugador.h"

CrearJugador::CrearJugador(string n, string c)
{
    nombre = n;
    color = c;
    capital = 1500;
}

string CrearJugador::getNombre()
{
    return nombre;
}

string CrearJugador::getColor()
{
    return color;
}

int CrearJugador::getCapital()
{
    return capital;
}

void CrearJugador::setCapital(int c)
{
    capital = c;
}

void CrearJugador::deposito(int cant)
{
    int c = getCapital();
    setCapital(c+cant);
}

int CrearJugador::retiro(int cant)
{
    int c= getCapital();
    if(getCapital()>cant)
    {
        setCapital(c-cant);
        return cant;
    }
    return 0;
}

void CrearJugador::nuevoJugador(string n,string color)
{
    jugadores.push_back(CrearJugador(n,color));
    escribirArchivo();
}

void CrearJugador::escribirArchivo()
{
    ofstream out(nombre_archivo.c_str());
    for(unsigned int i =0;i< jugadores.size();i++){
        out<<jugadores[i].nombre<<endl;
        out<<jugadores[i].color<<endl;
    }
    out.close();
}

void CrearJugador::ventanaCrearJugador(){
    sf::RenderWindow window;
    sf::Texture text_registrar,text_ficha_amarilla,text_ficha_azul,text_ficha_blanca,
                text_ficha_naranja,text_ficha_roja,text_ficha_verde, text_nuevo_jugador,
                text_seleccionador;
    sf::Sprite back_registrar,back_ficha_amarilla,back_ficha_azul,back_ficha_blanca,
                back_ficha_naranja,back_ficha_roja,back_ficha_verde, back_nuevo_jugador,
                back_seleccionador;
    sf::Font fuente;
    sf::String nombre_jugador;
    sf::Text txt_nombre_jugador;
    nombre_archivo= "jugadores.txt";


    int pos=0;

    window.create(sf::VideoMode(650,500,32),"Registrar Jugadores",sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    sf::Vector2f mouse;

    text_seleccionador.loadFromFile("ventanas/1.png");
    back_seleccionador.setTexture(text_seleccionador);

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

    text_nuevo_jugador.loadFromFile("ventanas/nuevo_jugador.png");
    back_nuevo_jugador.setTexture(text_nuevo_jugador);

    back_seleccionador.setPosition(40,285);
    back_ficha_amarilla.setPosition(44,290);
    back_ficha_azul.setPosition(125,290);
    back_ficha_blanca.setPosition(205,290);
    back_ficha_naranja.setPosition(44,370);
    back_ficha_roja.setPosition(125,370);
    back_ficha_verde.setPosition(205,370);
    back_nuevo_jugador.setPosition(400,400);

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

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                pos++;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                pos--;
            }

            if(pos>5){pos=5;}if(pos<0){pos=0;}

            mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if(pos==0){
            text_seleccionador.loadFromFile("ventanas/1.png");
        }
        if(pos==1){
            text_seleccionador.loadFromFile("ventanas/2.png");
        }
        if(pos==2){
            text_seleccionador.loadFromFile("ventanas/3.png");
        }
        if(pos==3){
            text_seleccionador.loadFromFile("ventanas/4.png");
        }
        if(pos==4){
            text_seleccionador.loadFromFile("ventanas/5.png");
        }
        if(pos==5){
            text_seleccionador.loadFromFile("ventanas/6.png");
        }

            if(event.type==sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&pos==0){
                    text_ficha_amarilla.loadFromFile("ventanas/enabled.png");
                    back_ficha_amarilla.setTexture(text_ficha_amarilla);
                    nuevoJugador(nombre_jugador,"ficha_amarilla");
                    nombre_jugador ="";
                    txt_nombre_jugador.setString(nombre_jugador);
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&pos==1){
                    text_ficha_azul.loadFromFile("ventanas/enabled.png");
                    back_ficha_azul.setTexture(text_ficha_azul);
                    nuevoJugador(nombre_jugador,"ficha_azul");
                    nombre_jugador ="";
                    txt_nombre_jugador.setString(nombre_jugador);
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&pos==2){
                    text_ficha_blanca.loadFromFile("ventanas/enabled.png");
                    back_ficha_blanca.setTexture(text_ficha_blanca);
                    nuevoJugador(nombre_jugador,"ficha_blanca");
                    txt_nombre_jugador.setString(nombre_jugador);
                    nombre_jugador ="";
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&pos==3){
                    text_ficha_naranja.loadFromFile("ventanas/enabled.png");
                    back_ficha_naranja.setTexture(text_ficha_naranja);
                    nuevoJugador(nombre_jugador,"ficha_naranja");
                    txt_nombre_jugador.setString(nombre_jugador);
                    nombre_jugador ="";
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&pos==4){
                    text_ficha_roja.loadFromFile("ventanas/enabled.png");
                    back_ficha_roja.setTexture(text_ficha_roja);
                    nuevoJugador(nombre_jugador,"ficha_roja");
                    txt_nombre_jugador.setString(nombre_jugador);
                    nombre_jugador ="";
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&pos==5){
                    !sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
                    text_ficha_verde.loadFromFile("ventanas/enabled.png");
                    back_ficha_verde.setTexture(text_ficha_verde);
                    nuevoJugador(nombre_jugador,"ficha_verde");
                    txt_nombre_jugador.setString(nombre_jugador);
                    nombre_jugador ="";
                }
            }
        }

        window.draw(back_registrar);
        window.draw(back_seleccionador);
        window.draw(txt_nombre_jugador);
        window.draw(back_ficha_amarilla);
        window.draw(back_ficha_azul);
        window.draw(back_ficha_blanca);
        window.draw(back_ficha_naranja);
        window.draw(back_ficha_roja);
        window.draw(back_ficha_verde);
        window.draw(back_nuevo_jugador);
        window.display();
    }
}

void CrearJugador::removerJugadores()
{

}

CrearJugador::~CrearJugador()
{

}
