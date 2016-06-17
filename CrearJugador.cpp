#include "CrearJugador.h"

CrearJugador::CrearJugador(string n, string c)
{
    nombre = n;
    color = c;
    capital = 1500;
    isPreso = false;
    acumular_turnos = 3;
    vector<string>nombre_propiedades;
}

string CrearJugador::getNombre()
{
    return nombre;
}

string CrearJugador::getColor()
{
    return color;
}

bool CrearJugador::getIsPreso(){
    return isPreso;
}

void CrearJugador::setIsPreso(bool p)
{
    isPreso = p;
}

void CrearJugador::setNombre(string n)
{
    nombre = n;
}

int CrearJugador::getCapital()
{
    return capital;
}

void CrearJugador::setCapital(int c)
{
    capital = c;
}

void CrearJugador::depositar(int cant)
{
    int c = getCapital();
    setCapital(c+cant);
}

int CrearJugador::retirar(int cant)
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
        out<<jugadores[i].getNombre()<<endl;
        out<<jugadores[i].getColor()<<endl;
    }
    out.close();
}

bool CrearJugador::ventanaCrearJugador(){
    sf::RenderWindow window;
    sf::View pointer;
    sf::Texture text_registrar,text_ficha_amarilla,text_ficha_azul,text_ficha_roja,text_ficha_verde,text_btnErase,
                text_seleccionador, text_warning,text_aceptar, text_jugar, text_pointer, text_btnSalir;
    sf::Sprite back_registrar,back_ficha_amarilla,back_ficha_azul,back_ficha_roja,back_ficha_verde,back_btnErase,
                back_seleccionador, back_warning,back_aceptar, back_jugar, back_pointer, back_btnSalir;
    sf::Font fuente;
    sf::String nombre_jugador;
    sf::Text txt_nombre_jugador;
    nombre_archivo= "jugadores.txt";


    int pos=0;
    bool mensaje = false;

    window.create(sf::VideoMode(650,500,32),"Registrar Jugadores",sf::Style::Close);
    window.setMouseCursorVisible(false);
    pointer = window.getView();

    sf::Vector2f mouse;

    text_pointer.loadFromFile("punteros/pointer.png");
    back_pointer.setTexture(text_pointer);
    text_seleccionador.loadFromFile("ventanas/1.png");
    back_seleccionador.setTexture(text_seleccionador);
    text_registrar.loadFromFile("ventanas/registro.png");
    back_registrar.setTexture(text_registrar);
    text_ficha_amarilla.loadFromFile("fichas/ficha_amarilla.png");
    back_ficha_amarilla.setTexture(text_ficha_amarilla);
    text_ficha_azul.loadFromFile("fichas/ficha_azul.png");
    back_ficha_azul.setTexture(text_ficha_azul);
    text_ficha_roja.loadFromFile("fichas/ficha_roja.png");
    back_ficha_roja.setTexture(text_ficha_roja);
    text_ficha_verde.loadFromFile("fichas/ficha_verde.png");
    back_ficha_verde.setTexture(text_ficha_verde);
    text_warning.loadFromFile("ventanas/warning.png");
    back_warning.setTexture(text_warning);
    text_aceptar.loadFromFile("ventanas/btn_aceptar.png");
    back_aceptar.setTexture(text_aceptar);
    text_jugar.loadFromFile("ventanas/jugar.png");
    back_jugar.setTexture(text_jugar);
    text_btnErase.loadFromFile("ventanas/backspace.png");
    back_btnErase.setTexture(text_btnErase);
    text_btnSalir.loadFromFile("ventanas/salir.png");
    back_btnSalir.setTexture(text_btnSalir);

    back_seleccionador.setPosition(40,285);
    back_ficha_amarilla.setPosition(44,290);
    back_ficha_azul.setPosition(125,290);
    back_ficha_roja.setPosition(44,370);
    back_ficha_verde.setPosition(125,370);
    back_warning.setPosition(150,200);
    back_aceptar.setPosition(250,320);
    back_jugar.setPosition(340,300);
    back_btnErase.setPosition(550,150);
    back_btnSalir.setPosition(340,370);

    fuente.loadFromFile("arial.ttf");

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
            if(utility.clickSprite(back_jugar,mouse)&&jugadores.size()<3)
            {
                mensaje = true;
            }

            if(utility.clickSprite(back_jugar,mouse)&&jugadores.size()==3){
                window.close();
            }

            if(utility.clickSprite(back_btnSalir,mouse)){
                window.close();
                return false;
            }

            if(event.type==sf::Event::TextEntered)
            {
                nombre_jugador.insert(nombre_jugador.getSize(),event.text.unicode);
                txt_nombre_jugador.setString(nombre_jugador);
            }

            if(utility.clickSprite(back_btnErase,mouse)){
                txt_nombre_jugador.setString("");
                nombre_jugador.clear();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                pos++;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                pos--;
            }

            if(pos>3){pos=3;}if(pos<0){pos=0;}

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

            if(event.type==sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&pos==0){
                    text_ficha_amarilla.loadFromFile("ventanas/enabled.png");
                    back_ficha_amarilla.setTexture(text_ficha_amarilla);
                    nuevoJugador(nombre_jugador,"ficha_amarilla");
                    txt_nombre_jugador.setString(nombre_jugador);
                    nombre_jugador.clear();
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&pos==1){
                    text_ficha_azul.loadFromFile("ventanas/enabled.png");
                    back_ficha_azul.setTexture(text_ficha_azul);
                    nuevoJugador(nombre_jugador,"ficha_azul");
                    txt_nombre_jugador.setString(nombre_jugador);
                    nombre_jugador.clear();
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&pos==2){
                    text_ficha_roja.loadFromFile("ventanas/enabled.png");
                    back_ficha_roja.setTexture(text_ficha_roja);
                    nuevoJugador(nombre_jugador,"ficha_roja");
                    txt_nombre_jugador.setString(nombre_jugador);
                    nombre_jugador.clear();
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&pos==3){
                    text_ficha_verde.loadFromFile("ventanas/enabled.png");
                    back_ficha_verde.setTexture(text_ficha_verde);
                    nuevoJugador(nombre_jugador,"ficha_verde");
                    txt_nombre_jugador.setString(nombre_jugador);
                    nombre_jugador.clear();
                }
            }
        }


        back_pointer.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
        if(utility.clickSprite(back_aceptar,mouse)){mensaje=false;}

        window.draw(back_registrar);
        window.draw(back_seleccionador);
        window.draw(txt_nombre_jugador);
        window.draw(back_ficha_amarilla);
        window.draw(back_ficha_azul);
        window.draw(back_ficha_roja);
        window.draw(back_ficha_verde);
        window.draw(back_jugar);
        window.draw(back_btnSalir);
        if(mensaje){window.draw(back_warning);}
        if(mensaje){window.draw(back_aceptar);}
        window.draw(back_btnErase);
        window.setView(pointer);
        window.draw(back_pointer);
        window.display();
    }
    return true;
}

void CrearJugador::removerJugadores()
{

}

CrearJugador::~CrearJugador()
{

}
