#include "JugarMonopoly.h"

JugarMonopoly::JugarMonopoly()
{
    //ctor
}

bool mensaje, msj_capital_insuf,msj_propiedad_comprada;

void JugarMonopoly::setPropiedades(Propiedad propiedad)
{
    propiedades.push_back(propiedad);
}

Propiedad JugarMonopoly::getPropiedades(int pos)
{
    return propiedades[pos];
}

void JugarMonopoly::llenarPropiedades()
{
    string archivo = "propiedades.txt";
    Propiedad temp;

    ifstream in(archivo.c_str());
    string np, nd, c;
    int v, r, vh;

    while(in>>np&&in>>nd&&in>>c&&in>>v&&in>>r&&in>>vh)
    {
        temp.setNombrePosesion(np);
        temp.setNombreDuenio(nd);
        temp.setColorPropiedad(c);
        temp.setValorPropiedad(v);
        temp.setRenta(r);
        temp.setValorHipoteca(vh);
        temp.setEstadoHipoteca(false);
        setPropiedades(temp);
    }
    in.close();
}

/**
    Esta funcion solo es para verificar el buen funcionamiento de los get's y set's del
    vector propiedades...
*/

void JugarMonopoly::mostrarPropiedades()
{
    for(unsigned int c =0;c < propiedades.size();c++)
    {
        cout<<getPropiedades(c).getNombrePosesion()<<" , "<<getPropiedades(c).getNombreDuenio()<<" , "<<
        getPropiedades(c).getColorPropiedad()<<" , "<<getPropiedades(c).getValorPropiedad()<<" , "<<
        getPropiedades(c).getRenta()<<" , "<<getPropiedades(c).getValorHipoteca()<<" , "<<
        getPropiedades(c).getValorHipoteca()<<" , "<<getPropiedades(c).getEstadoHipoteca()<<endl;
    }
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
    Esta funcion trabaja a partir de un sprite y la suma de los dados
    En el fondo hay un archivo de texto que recibe los parametros
    ficha->getPosition().x y ficha->getPosition().y Y luego se apoya de
    ficha->setPosition(int,int) y retorna esa posicion que es la que hace
    posible el movimiento en el tablero.
*/

sf::Sprite JugarMonopoly::movimiento(sf::Sprite* ficha,int suma_dados)
{
    int getPositionX, getPositionY, dado_file, setPositionX, setPositionY;

     ifstream out1("setPositions.txt");
        while(out1>>getPositionX&&out1>>getPositionY&&out1>>dado_file&&out1>>setPositionX&&out1>>setPositionY){
            if(ficha->getPosition().x==getPositionX&&ficha->getPosition().y==getPositionY&&suma_dados==dado_file){
                ficha->setPosition(setPositionX,setPositionY);
                return *ficha;
            }
        }
        out1.close();
        return *ficha;
}

/**
    Esta funcion da acceso a la funcion ventanaCompra() si en caso retorna verdadero
    si retorna FALSE despliega un mensaje en otra funcion informando que no se puede
    hacer una compra ya que la ficha no esta ubicada en una casilla de compras.

    FUNCIONES QUE UTILIZA:
        getPosition()->propiedad de SFML.
*/

bool JugarMonopoly::validarCompra(sf::Sprite* ficha)
{
    if(ficha->getPosition().x==640&&ficha->getPosition().y==640||ficha->getPosition().x==495&&ficha->getPosition().y==640
       ||ficha->getPosition().x==385&&ficha->getPosition().y==640||ficha->getPosition().x==215&&ficha->getPosition().y==640
       ||ficha->getPosition().x==20&&ficha->getPosition().y==640||ficha->getPosition().x==20&&ficha->getPosition().y==215
       ||ficha->getPosition().x==20&&ficha->getPosition().y==20||ficha->getPosition().x==160&&ficha->getPosition().y==20
       ||ficha->getPosition().x==640&&ficha->getPosition().y==20||ficha->getPosition().x==640&&ficha->getPosition().y==215
       ||ficha->getPosition().x==640&&ficha->getPosition().y==385||ficha->getPosition().x==640&&ficha->getPosition().y==495)
    {
        return false;
    }
    return true;
}

/**
    Esta funcion es la responsable de manejar el tablero con todas sus opcioes(compras,hipotecas,turnos,cartas de fortuna
    y arca, movimientos de fichas,dados,nombres de jugadores y capital disponible etc.)
    Esta funcion es capaz de llamar las ventanas y funciones logicas que sean necesarias para su funcionamiento.

    **Esta funcion se enfoca mas que todo en la parte visual del juego.

    UTILIZA LAS SIGUIENTES FUNCIOES:
        toString(int) Y clickSprite(Sprite,Vector2f)-->propiedad de la clase Utility
        llenarPropiedades();
        cargarJugadores();
        validarCompras();
        ventanaCompras();
        validarInfoCompra();
*/

void JugarMonopoly::ventanaTablero()
{
    sf::RenderWindow window;

    sf::Texture text_tablero,text_dado_1,text_dado_2,text_ficha_3,text_ficha_4,text_ficha_5,text_ficha_6,
        text_carta_arca, text_carta_fortuna, text_comprar, text_info, text_btnAceptar, text_derecha_tablero,text_capital_insuf,
        text_btnCapital_insuf,text_propiedad_comprada,text_btnPropiedad_comprada;
    sf::Texture ref_text_ficha_1,ref_text_ficha_2;
    sf::Texture *text_ficha_1, *text_ficha_2;

    sf::Sprite back_tablero,back_dado_1,back_dado_2,back_ficha_3,back_ficha_4,back_ficha_5,back_ficha_6,
        back_carta_arca, back_carta_fortuna, back_comprar,back_info, back_btnAceptar, back_derecha_tablero,
        back_btnCapital_insuf,back_propiedad_comprada,back_btnPropiedad_comprada;
    sf::Sprite ref_back_ficha_1,ref_back_ficha_2,back_capital_insuf;
    sf::Sprite *back_ficha_1, *back_ficha_2;

    sf::Vector2f mouse;
    sf::Font font;
    sf::Text txt_jugador_1, txt_jugador_2;
    int suma_dados,guardar_dado_1,guardar_dado_2,clicks=0;
    string nombre_jugador_1, nombre_jugador_2;
    int capital_jugador_1;

    nombre_archivo = "jugadores.txt";

    llenarPropiedades();
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
    txt_jugador_1.setPosition(1055,10);

    txt_jugador_2.setFont(font);
    txt_jugador_2.setCharacterSize(24);
    txt_jugador_2.setColor(sf::Color::Red);
    txt_jugador_2.setPosition(1055,40);

    text_tablero.loadFromFile("tablero.png");
    back_tablero.setTexture(text_tablero);
    text_dado_1.loadFromFile("dados/1.png");
    back_dado_1.setTexture(text_dado_1);
    text_dado_2.loadFromFile("dados/1.png");
    back_dado_2.setTexture(text_dado_2);
    text_carta_arca.loadFromFile("arca_comunal/17.png");
    back_carta_arca.setTexture(text_carta_arca);
    text_carta_fortuna.loadFromFile("fortuna/17.png");
    back_carta_fortuna.setTexture(text_carta_fortuna);
    text_comprar.loadFromFile("ventanas/comprar.png");
    back_comprar.setTexture(text_comprar);
    text_info.loadFromFile("ventanas/info.png");
    back_info.setTexture(text_info);
    text_btnAceptar.loadFromFile("ventanas/btn_aceptar.png");
    back_btnAceptar.setTexture(text_btnAceptar);
    text_derecha_tablero.loadFromFile("ventanas/derecha_tablero.png");
    back_derecha_tablero.setTexture(text_derecha_tablero);
    text_capital_insuf.loadFromFile("ventanas/capital_insuficiente.png");
    back_capital_insuf.setTexture(text_capital_insuf);
    text_btnCapital_insuf.loadFromFile("ventanas/btn_capital_insuficiente.png");
    back_btnCapital_insuf.setTexture(text_btnCapital_insuf);
    text_propiedad_comprada.loadFromFile("ventanas/propiedad_comprada.png");
    back_propiedad_comprada.setTexture(text_propiedad_comprada);
    text_btnPropiedad_comprada.loadFromFile("ventanas/btn_propiedad_comprada.png");
    back_btnPropiedad_comprada.setTexture(text_btnPropiedad_comprada);


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
    back_carta_arca.setPosition(691,2);
    back_carta_fortuna.setPosition(872,2);
    back_comprar.setPosition(800,150);
    back_info.setPosition(700,250);
    back_btnAceptar.setPosition(800,380);
    back_derecha_tablero.setPosition(690,0);
    back_capital_insuf.setPosition(700,250);
    back_btnCapital_insuf.setPosition(800,380);
    back_propiedad_comprada.setPosition(700,250);
    back_btnPropiedad_comprada.setPosition(800,380);


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
            }

            if(clicks%2==0){
                movimiento(back_ficha_1,suma_dados);
                suma_dados=0;
                if(validarCompra(back_ficha_1)&&utility.clickSprite(back_comprar,mouse)&&ventanaCompras(back_ficha_1,jugadores[0].nombre)){
                    validarInfoDeCompra(back_ficha_1, 0);
                }
            }else{
                movimiento(back_ficha_2,suma_dados);
                suma_dados=0;
                if(validarCompra(back_ficha_2)&&utility.clickSprite(back_comprar,mouse)&&ventanaCompras(back_ficha_2,jugadores[1].nombre)){
                    validarInfoDeCompra(back_ficha_2, 1);
                }
            }

            if(!validarCompra(back_ficha_1)){
                if(utility.clickSprite(back_comprar,mouse)){
                    mensaje = true;
                }
            }else if(!validarCompra(back_ficha_2)){
                if(utility.clickSprite(back_comprar,mouse)){
                    mensaje = true;
                }
            }

            //PROBANDO TABLERO
            if(utility.clickSprite(back_btnAceptar,mouse)){mensaje = false;}
            if(utility.clickSprite(back_btnCapital_insuf,mouse)){msj_capital_insuf = false;}
            if(utility.clickSprite(back_btnPropiedad_comprada,mouse)){msj_propiedad_comprada = false;}
        }
        txt_jugador_1.setString(jugadores[0].getNombre()+"\t\t\t"+utility.toString(jugadores[0].getCapital()));
        txt_jugador_2.setString(jugadores[1].getNombre()+"\t\t\t"+utility.toString(jugadores[1].getCapital()));

        window.draw(back_tablero);
        window.draw(back_derecha_tablero);
        window.draw(back_dado_1);
        window.draw(back_dado_2);
        window.draw(txt_jugador_1);
        window.draw(txt_jugador_2);
        window.draw(back_carta_arca);
        window.draw(back_carta_fortuna);
        window.draw(back_comprar);
        if(mensaje){window.draw(back_info);}
        if(mensaje){window.draw(back_btnAceptar);}
        if(msj_capital_insuf){window.draw(back_capital_insuf);}
        if(msj_capital_insuf){window.draw(back_btnCapital_insuf);}
        if(msj_propiedad_comprada){window.draw(back_propiedad_comprada);}
        if(msj_propiedad_comprada){window.draw(back_btnPropiedad_comprada);}

        if(ficha1){window.draw(*back_ficha_1);}
        if(ficha2){window.draw(*back_ficha_2);}
        if(ficha3){window.draw(back_ficha_3);}
        if(ficha4){window.draw(back_ficha_4);}
        if(ficha5){window.draw(back_ficha_5);}
        if(ficha6){window.draw(back_ficha_6);}

        window.display();
    }
}

/**
    Esta funcion se manda a llamar desde la funcion ventanaTablero() y desde validarCompra()
    siempre que estas funciones cumplan con sus validaciones se abrira esta ventana.
    Especificamente esta funcion lo que hace es evaluar la posicion de la sprite en el tablero
    y a partir de esas coordenadas cargar una imagen de la propiedad que se quiere comprar.
    Tiene botones COMPRAR Y SALIR.

    FUNCIONES QUE UTILIZA:
        getPosition() setPosition()
        mapPixelToCoords(sf::Mouse::getPosition(sf::Window w) a partir de un Vector2f

    **Estas funciones son propiedad de SFML
*/

bool JugarMonopoly::ventanaCompras(sf::Sprite* sprite, string nombre)
{
    sf::RenderWindow window;
    sf::Vector2f mouse;
    sf::Texture texture, text_titulo, text_btnComprar, text_btnSalir;
    sf::Sprite background, back_titulo, back_btnComprar, back_btnSalir;

    window.create(sf::VideoMode(400,250),"Comprar Propiedades");

    texture.loadFromFile("verde.png");
    background.setTexture(texture);
    text_btnComprar.loadFromFile("ventanas/boton_comprar.png");
    back_btnComprar.setTexture(text_btnComprar);
    text_btnSalir.loadFromFile("ventanas/boton_salir.png");
    back_btnSalir.setTexture(text_btnSalir);

    back_btnComprar.setPosition(230,70);
    back_btnSalir.setPosition(230,140);

    if(sprite->getPosition().x==555&&sprite->getPosition().y==640){
        text_titulo.loadFromFile("propiedades/avenida_lempira.png");
    }
    else if(sprite->getPosition().x==440&&sprite->getPosition().y==640){
        text_titulo.loadFromFile("propiedades/nova_prisa.png");
    }
    else if(sprite->getPosition().x==270&&sprite->getPosition().y==640){
        text_titulo.loadFromFile("propiedades/avenida_juan_pablo_2.png");
    }
    else if(sprite->getPosition().x==160&&sprite->getPosition().y==640){
        text_titulo.loadFromFile("propiedades/tercera_avenida.png");
    }
    else if(sprite->getPosition().x==105&&sprite->getPosition().y==640){
        text_titulo.loadFromFile("propiedades/bulevar_morazan.png");
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==555){
        text_titulo.loadFromFile("propiedades/avenida_circunvalacion.png");
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==440){
        text_titulo.loadFromFile("propiedades/105_brigada.png");
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==385){
        text_titulo.loadFromFile("propiedades/metro_plaza.png");
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==270){
        text_titulo.loadFromFile("propiedades/expo_centro.png");
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==160){
        text_titulo.loadFromFile("propiedades/segundo_anillo_periferico.png");
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==105){
        text_titulo.loadFromFile("propiedades/bulevar_los_proceres.png");
    }
    else if(sprite->getPosition().x==105&&sprite->getPosition().y==20){
        text_titulo.loadFromFile("propiedades/pasaje_valle.png");
    }
    else if(sprite->getPosition().x==215&&sprite->getPosition().y==20){
        text_titulo.loadFromFile("propiedades/maheco.png");
    }
    else if(sprite->getPosition().x==270&&sprite->getPosition().y==20){
        text_titulo.loadFromFile("propiedades/monumento_a_la_madre.png");
    }
    else if(sprite->getPosition().x==385&&sprite->getPosition().y==20){
        text_titulo.loadFromFile("propiedades/avenida_new_orleans.png");
    }
    else if(sprite->getPosition().x==440&&sprite->getPosition().y==20){
        text_titulo.loadFromFile("propiedades/mercado_el_rapido.png");
    }
    else if(sprite->getPosition().x==555&&sprite->getPosition().y==20){
        text_titulo.loadFromFile("propiedades/bulevar_del_norte.png");
    }
    else if(sprite->getPosition().x==640&&sprite->getPosition().y==105){
        text_titulo.loadFromFile("propiedades/avenida_junior.png");
    }
    else if(sprite->getPosition().x==640&&sprite->getPosition().y==160){
        text_titulo.loadFromFile("propiedades/molino_harinero_de_sula.png");
    }
    else if(sprite->getPosition().x==640&&sprite->getPosition().y==270){
        text_titulo.loadFromFile("propiedades/campo_agas.png");
    }
    else if(sprite->getPosition().x==640&&sprite->getPosition().y==440){
        text_titulo.loadFromFile("propiedades/parque_central.png");
    }
    else if(sprite->getPosition().x==640&&sprite->getPosition().y==555){
        text_titulo.loadFromFile("propiedades/estadio_olimpico.png");
    }
    else if(sprite->getPosition().x==325&&sprite->getPosition().y==640){
        text_titulo.loadFromFile("propiedades/ferrocarril_sur.png");
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==325){
        text_titulo.loadFromFile("propiedades/ferrocarril_oeste.png");
    }
    else if(sprite->getPosition().x==325&&sprite->getPosition().y==20){
        text_titulo.loadFromFile("propiedades/ferrocarril_norte.png");
    }
    else if(sprite->getPosition().x==640&&sprite->getPosition().y==325){
        text_titulo.loadFromFile("propiedades/ferrocarril_este.png");
    }

    back_titulo.setTexture(text_titulo);

    while(window.isOpen())
    {
        mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
                window.close();
                return true;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                window.close();
                return false;
            }

            if(utility.clickSprite(back_btnComprar,mouse)){
                window.close();
                return true;
            }

            if(utility.clickSprite(back_btnSalir,mouse)){
                window.close();
                return false;
            }

        }

        window.draw(background);
        window.draw(back_titulo);
        window.draw(back_btnComprar);
        window.draw(back_btnSalir);
        window.display();
    }
}

/**
    Esta funcion me retorna la posicion a la que debo acceder en mi vector
    propiedades a partir de la posicion de la sprite en el tablero.
    Su uso es necesario para sacar la informacion de un registro en especifico
    en el vector propiedades
    UTLIZA LAS SIGUIENTES FUNCIONES  A PARTIR DE UN SPRITE:
        getPosition().x
        getPosition().y

    **Estas funciones son propiedad de SFML.
*/

int JugarMonopoly::infoPropiedad(sf::Sprite* sprite)
{
    if(sprite->getPosition().x==555&&sprite->getPosition().y==640){
        return 0;
    }
    else if(sprite->getPosition().x==440&&sprite->getPosition().y==640){
        return 1;
    }
    else if(sprite->getPosition().x==270&&sprite->getPosition().y==640){
        return 3;
    }
    else if(sprite->getPosition().x==160&&sprite->getPosition().y==640){
        return 4;
    }
    else if(sprite->getPosition().x==105&&sprite->getPosition().y==640){
        return 5;
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==555){
        return 6;
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==440){
        return 7;
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==385){
        return 9;
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==270){
        return 11;
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==160){
        return 12;
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==105){
        return 13;
    }
    else if(sprite->getPosition().x==105&&sprite->getPosition().y==20){
        return 14;
    }
    else if(sprite->getPosition().x==215&&sprite->getPosition().y==20){
        return 15;
    }
    else if(sprite->getPosition().x==270&&sprite->getPosition().y==20){
        return 16;
    }
    else if(sprite->getPosition().x==385&&sprite->getPosition().y==20){
        return 18;
    }
    else if(sprite->getPosition().x==440&&sprite->getPosition().y==20){
        return 19;
    }
    else if(sprite->getPosition().x==555&&sprite->getPosition().y==20){
        return 21;
    }
    else if(sprite->getPosition().x==640&&sprite->getPosition().y==105){
        return 22;
    }
    else if(sprite->getPosition().x==640&&sprite->getPosition().y==160){
        return 23;
    }
    else if(sprite->getPosition().x==640&&sprite->getPosition().y==270){
        return 24;
    }
    else if(sprite->getPosition().x==640&&sprite->getPosition().y==440){
        return 26;
    }
    else if(sprite->getPosition().x==640&&sprite->getPosition().y==555){
        return 27;
    }
    else if(sprite->getPosition().x==325&&sprite->getPosition().y==640){
        return 2;
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==325){
        return 10;
    }
    else if(sprite->getPosition().x==325&&sprite->getPosition().y==20){
        return 17;
    }
    else if(sprite->getPosition().x==640&&sprite->getPosition().y==325){
        return 25;
    }
}

/**
    Esta funcion contiene las validaciones necesarias para hacer posible una compra
    valida que la prpiedad pertenezca al banco si no pertenece al banco despliega un
    mensaje que la propiedad ya tiene duenio
    Valida que el capital del jugador sea mayor al precio de la prpiedad de lo contrario
    despliega un mensaje dinero insuficiente
    LLAMADAS A LAS SIGUIENTES FUNCIONES:
        infoPropiedad(sf::Sprite* sprite);
        ventanaCompras(sf::Sprite* sprite, string nombreJugador);
        y a los get's y set's de el vector jugadores y propiedades
*/

void JugarMonopoly::validarInfoDeCompra(sf::Sprite* sprite, int posJugador)
{
    cout<<posJugador<<endl;
    if(propiedades[infoPropiedad(sprite)].getNombreDuenio()=="banco"){
        if(jugadores[posJugador].capital > propiedades[infoPropiedad(sprite)].getValorPropiedad()){
            ventanaCompras(sprite,jugadores[posJugador].nombre);
            jugadores[posJugador].capital -= propiedades[infoPropiedad(sprite)].getValorPropiedad();
            propiedades[infoPropiedad(sprite)].setNombreDuenio(jugadores[posJugador].nombre);
        }else{
            msj_capital_insuf = true;
        }
    }else{
        msj_propiedad_comprada = true;
    }
}

JugarMonopoly::~JugarMonopoly()
{
    remove(nombre_archivo.c_str());
}
