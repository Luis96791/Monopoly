#include "JugarMonopoly.h"

JugarMonopoly::JugarMonopoly()
{
    //ctor
}

bool mensaje, msj_capital_insuf,msj_propiedad_comprada, cobrar_salida=false, is_close_all=false,
    msj_ejecutar_accion, carta_arca_activa, carta_fortuna_activa,
     cobrar_impuesto, pagar_renta,carcel_tres_turnos;
int aumentar_arca=0, aumentar_fortuna=0;

sf::Texture text_carta_arca, text_carta_fortuna, text_comprar,text_btnHipotecar;
sf::Sprite back_carta_arca, back_carta_fortuna, back_comprar,back_btnHipotecar;
sf::Text txt_turnos;

void JugarMonopoly::setPropiedades(Propiedad propiedad)
{
    propiedades.push_back(propiedad);
}

Propiedad JugarMonopoly::getPropiedades(int pos)
{
    return propiedades[pos];
}

/**
    Esta funcion llena el vector propiedades a partir de
    un archivo de texto con los valores por default
*/

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

vector<CrearJugador> JugarMonopoly::cargarJugadores()
{
    ifstream leer(nombre_archivo.c_str());
    int numero;
    string nombre, color;
    while(leer>>numero&&leer>>nombre&&leer>>color){
        jugadores.push_back(CrearJugador(numero,nombre,color));
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

    sf::Texture text_tablero,text_dado_1,text_dado_2, text_info, text_btnAceptar, text_derecha_tablero,text_capital_insuf,
        text_btnCapital_insuf,text_propiedad_comprada,text_btnPropiedad_comprada,text_msj_carta,
        text_btnMsj_carta,text_btnDeshipotecar,text_btnRetirarse,text_btnTerminar,text_Ganador,text_btnGanador/*,text_puntero*/;
    sf::Texture ref_text_ficha_1,ref_text_ficha_2,ref_text_ficha_3,ref_text_ficha_4,ref_text_ficha_5,ref_text_ficha_6;
    sf::Texture *text_ficha_1,*text_ficha_2,*text_ficha_3,*text_ficha_4,*text_ficha_5,*text_ficha_6;

    sf::Sprite back_tablero,back_dado_1,back_dado_2,back_info, back_btnAceptar, back_derecha_tablero,
        back_btnCapital_insuf,back_propiedad_comprada,back_btnPropiedad_comprada,back_msj_carta,back_capital_insuf,
        back_btnMsj_carta,back_btnDeshipotecar,back_btnRetirarse,back_btnTerminar,back_Ganador,back_btnGanador/*,back_puntero*/;
    sf::Sprite ref_back_ficha_1,ref_back_ficha_2,ref_back_ficha_3,ref_back_ficha_4,ref_back_ficha_5,ref_back_ficha_6;
    sf::Sprite *back_ficha_1,*back_ficha_2,*back_ficha_3,*back_ficha_4,*back_ficha_5,*back_ficha_6;

    sf::Vector2f mouse;
    sf::Font font;
//    sf::View view;
    sf::Text txt_jugador_1, txt_jugador_2, txt_jugador_3, txt_banco, txt_ganador;
    int suma_dados=0,guardar_dado_1,guardar_dado_2,clicks;
    string nombre_jugador_1, nombre_jugador_2;
    int capital_jugador_1;

    nombre_archivo = "jugadores.txt";

    llenarPropiedades();
    cargarJugadores();

    window.create(sf::VideoMode(1360,690,32),"Monopoly",sf::Style::Default);
    window.setPosition(sf::Vector2i(0,0));
    window.setVerticalSyncEnabled(true);

    text_ficha_1 = &ref_text_ficha_1;
    text_ficha_2 = &ref_text_ficha_2;
    text_ficha_3 = &ref_text_ficha_3;
    text_ficha_4 = &ref_text_ficha_4;
    text_ficha_5 = &ref_text_ficha_5;
    text_ficha_6 = &ref_text_ficha_6;

    back_ficha_1 = &ref_back_ficha_1;
    back_ficha_2 = &ref_back_ficha_2;
    back_ficha_3 = &ref_back_ficha_3;
    back_ficha_4 = &ref_back_ficha_4;
    back_ficha_5 = &ref_back_ficha_5;
    back_ficha_6 = &ref_back_ficha_6;

    if(!font.loadFromFile("arial.ttf")){}
    txt_jugador_1.setFont(font);
    txt_jugador_1.setCharacterSize(24);
    txt_jugador_1.setColor(sf::Color::Blue);
    txt_jugador_1.setPosition(1055,160);

    txt_jugador_2.setFont(font);
    txt_jugador_2.setCharacterSize(24);
    txt_jugador_2.setColor(sf::Color::Red);
    txt_jugador_2.setPosition(1055,190);

    txt_jugador_3.setFont(font);
    txt_jugador_3.setCharacterSize(24);
    txt_jugador_3.setColor(sf::Color::Green);
    txt_jugador_3.setPosition(1055,220);

    txt_banco.setFont(font);
    txt_banco.setCharacterSize(24);
    txt_banco.setColor(sf::Color::Black);
    txt_banco.setPosition(1055,260);

    txt_turnos.setFont(font);
    txt_turnos.setCharacterSize(24);
    txt_turnos.setColor(sf::Color::Black);
    txt_turnos.setPosition(1155,550);

    txt_ganador.setFont(font);
    txt_ganador.setCharacterSize(48);
    txt_ganador.setStyle(sf::Text::Bold);
    txt_ganador.setColor(sf::Color::White);
    txt_ganador.setPosition(550,350);

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
    text_btnHipotecar.loadFromFile("ventanas/hipotecar.png");
    back_btnHipotecar.setTexture(text_btnHipotecar);
    text_msj_carta.loadFromFile("ventanas/msj_cartas.png");
    back_msj_carta.setTexture(text_msj_carta);
    text_btnDeshipotecar.loadFromFile("ventanas/deshipotecar.png");
    back_btnDeshipotecar.setTexture(text_btnDeshipotecar);
    text_btnRetirarse.loadFromFile("ventanas/retirarse.png");
    back_btnRetirarse.setTexture(text_btnRetirarse);
    text_btnTerminar.loadFromFile("ventanas/terminar.png");
    back_btnTerminar.setTexture(text_btnTerminar);
    text_Ganador.loadFromFile("ventanas/msj_ganador.png");
    back_Ganador.setTexture(text_Ganador);
    text_btnGanador.loadFromFile("ventanas/btnAceptarSalida.png");
    back_btnGanador.setTexture(text_btnGanador);

    ifstream cargar("jugadores.txt");
    int num;
    string n, f;
    bool ficha1,ficha2,ficha3,ficha4,ficha5,ficha6, is_unico = false;
    while(cargar>>num&&cargar>>n&&cargar>>f){
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
            text_ficha_3->loadFromFile("fichas_tablero/ficha_verde.png");
            back_ficha_3->setTexture(*text_ficha_3);
            back_ficha_3->setPosition(640,640);
            ficha3=true;
        }
        if(f=="ficha_amarilla"){
            text_ficha_4->loadFromFile("fichas_tablero/ficha_amarilla.png");
            back_ficha_4->setTexture(*text_ficha_4);
            back_ficha_4->setPosition(640,640);
            ficha4=true;
        }
        if(f=="ficha_blanca"){
            text_ficha_5->loadFromFile("fichas_tablero/ficha_blanca.png");
            back_ficha_5->setTexture(*text_ficha_5);
            back_ficha_5->setPosition(640,640);
            ficha5=true;
        }
        if(f=="ficha_naranja"){
            text_ficha_6->loadFromFile("fichas_tablero/ficha_naranja.png");
            back_ficha_6->setTexture(*text_ficha_6);
            back_ficha_6->setPosition(640,640);
            ficha6=true;
        }
    }
    cargar.close();


    back_dado_1.setPosition(1140,580);
    back_dado_2.setPosition(1250,580);
    back_carta_arca.setPosition(691,2);
    back_carta_fortuna.setPosition(912,2);
    back_info.setPosition(700,250);
    back_btnAceptar.setPosition(800,380);
    back_derecha_tablero.setPosition(690,0);
    back_capital_insuf.setPosition(700,250);
    back_btnCapital_insuf.setPosition(800,380);
    back_propiedad_comprada.setPosition(700,250);
    back_btnPropiedad_comprada.setPosition(800,380);
    back_comprar.setPosition(700,150);
    back_btnHipotecar.setPosition(700,210);
    back_btnDeshipotecar.setPosition(700,270);
    back_btnRetirarse.setPosition(700,330);
    back_btnTerminar.setPosition(700,390);
    back_msj_carta.setPosition(700,250);
    back_Ganador.setPosition(400,350);
    back_btnGanador.setPosition(570,460);


     while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if(utility.clickSprite(back_dado_1,mouse)||utility.clickSprite(back_dado_2,mouse))
            {
                msj_ejecutar_accion = false;
                cobrar_impuesto = true;
                pagar_renta = true;
                carta_arca_activa = true;
                carta_fortuna_activa = true;
                clicks++;
                guardar_dado_1=utility.dadoUno();
                guardar_dado_2=utility.dadoDos();
                suma_dados=guardar_dado_1+guardar_dado_2;

                text_dado_1.loadFromFile("dados/"+utility.toString(guardar_dado_1)+".png");
                back_dado_1.setTexture(text_dado_1);
                text_dado_2.loadFromFile("dados/"+utility.toString(guardar_dado_2)+".png");
                back_dado_2.setTexture(text_dado_2);
            }

            if(ficha3 &&clicks%3==0){
                txt_turnos.setString("Turno de: "+jugadores[2].getNombre());

                if(mostrarCartaArca(back_ficha_3)&&carta_arca_activa){
                    carta_arca_activa = false;
                    text_carta_arca.loadFromFile("arca_comunal/"+utility.toString(aumentar_arca)+".png");
                    ejecutarCartaArca(back_ficha_3,2);
                }

                if(mostrarCartaFortuna(back_ficha_3)&&carta_fortuna_activa){
                    carta_fortuna_activa = false;
                    text_carta_fortuna.loadFromFile("fortuna/"+utility.toString(aumentar_fortuna)+".png");
                    ejecutarCartaFortuna(back_ficha_3,2,suma_dados);
                }

                if(utility.clickSprite(back_btnHipotecar,mouse)){
                    ventanaHipotecar(jugadores[2].getNombre(),2);
                }

                if(utility.clickSprite(back_btnDeshipotecar,mouse)){
                    ventanaDeshipotecar(jugadores[2].getNombre(),2);
                }

                if(validarCompra(back_ficha_3)&&utility.clickSprite(back_comprar,mouse)){
                    validarInfoDeCompra(back_ficha_3, 2);
                }

                if(!validarCompra(back_ficha_3)){
                    if(utility.clickSprite(back_comprar,mouse)){
                        mensaje = true;
                    }
                }

                if(utility.clickSprite(back_btnRetirarse, mouse)){
                    if(ventanaInventario(jugadores[2].getNombre(),2)){
                        ficha3 = false;
                    }
                }

                esperarTresTurnos(guardar_dado_1,guardar_dado_2,2);
                ejecutarFunciones(back_ficha_3,2,suma_dados);
                suma_dados=0;
            }
            else if(ficha1 && clicks%2==0){
                txt_turnos.setString("Turno de: "+jugadores[0].getNombre());

                if(mostrarCartaArca(back_ficha_1)&&carta_arca_activa){
                    carta_arca_activa = false;
                    text_carta_arca.loadFromFile("arca_comunal/"+utility.toString(aumentar_arca)+".png");
                    ejecutarCartaArca(back_ficha_1,0);
                }

                if(mostrarCartaFortuna(back_ficha_1)&&carta_fortuna_activa){
                    carta_fortuna_activa = false;
                    text_carta_fortuna.loadFromFile("fortuna/"+utility.toString(aumentar_fortuna)+".png");
                    ejecutarCartaFortuna(back_ficha_1,0,suma_dados);
                }

                if(utility.clickSprite(back_btnHipotecar,mouse)){
                    ventanaHipotecar(jugadores[0].getNombre(),0);
                }

                if(utility.clickSprite(back_btnDeshipotecar,mouse)){
                    ventanaDeshipotecar(jugadores[0].getNombre(),0);
                }

                if(validarCompra(back_ficha_1)&&utility.clickSprite(back_comprar,mouse)){
                    validarInfoDeCompra(back_ficha_1, 0);
                }

                if(!validarCompra(back_ficha_1)){
                    if(utility.clickSprite(back_comprar,mouse)){
                        mensaje = true;
                    }
                }

                if(utility.clickSprite(back_btnRetirarse, mouse)){
                    if(ventanaInventario(jugadores[0].getNombre(),0)){
                        ficha1 = false;
                    }
                }

                esperarTresTurnos(guardar_dado_1,guardar_dado_2,0);
                ejecutarFunciones(back_ficha_1,0,suma_dados);
                suma_dados=0;
            }else if(ficha2 && clicks%1==0){
                txt_turnos.setString("Turno de: "+jugadores[1].getNombre());

                if(utility.clickSprite(back_btnHipotecar,mouse)){
                    ventanaHipotecar(jugadores[1].getNombre(),1);
                }

                if(utility.clickSprite(back_btnDeshipotecar,mouse)){
                    ventanaDeshipotecar(jugadores[1].getNombre(),1);
                }

                if(mostrarCartaArca(back_ficha_2)&&carta_arca_activa){
                    carta_arca_activa = false;
                    text_carta_arca.loadFromFile("arca_comunal/"+utility.toString(aumentar_arca)+".png");
                    ejecutarCartaArca(back_ficha_2,1);
                }

                if(mostrarCartaFortuna(back_ficha_2)&&carta_fortuna_activa){
                    carta_fortuna_activa = false;
                    text_carta_fortuna.loadFromFile("fortuna/"+utility.toString(aumentar_fortuna)+".png");
                    ejecutarCartaFortuna(back_ficha_2,1,suma_dados);
                }

                if(validarCompra(back_ficha_2)&&utility.clickSprite(back_comprar,mouse)){
                    validarInfoDeCompra(back_ficha_2, 1);
                }
                if(!validarCompra(back_ficha_2)){
                    if(utility.clickSprite(back_comprar,mouse)){
                        mensaje = true;
                    }
                }

                if(utility.clickSprite(back_btnRetirarse, mouse)){
                    if(ventanaInventario(jugadores[1].getNombre(),1)){
                        ficha2 = false;
                    }
                }

                esperarTresTurnos(guardar_dado_1,guardar_dado_2,1);
                ejecutarFunciones(back_ficha_2,1,suma_dados);
                suma_dados=0;
            }

            if(utility.clickSprite(back_btnTerminar,mouse)){
                ventanaTerminarJuego();
            }

            if(ganadorPorDefault()!=-1){
                is_unico = true;
                txt_ganador.setString(jugadores[ganadorPorDefault()].getNombre());
            }

            if(utility.clickSprite(back_btnGanador,mouse)){
                is_close_all = true;
            }

            if(utility.clickSprite(back_btnAceptar,mouse)){mensaje = false;}
            if(utility.clickSprite(back_btnCapital_insuf,mouse)){msj_capital_insuf = false;}
            if(utility.clickSprite(back_btnPropiedad_comprada,mouse)){msj_propiedad_comprada = false;}

            if(is_close_all){
                window.close();
            }
        }

        txt_jugador_1.setString(jugadores[0].getNombre()+"\t"+utility.toString(jugadores[0].getCapital()));
        txt_jugador_2.setString(jugadores[1].getNombre()+"\t"+utility.toString(jugadores[1].getCapital()));
        txt_jugador_3.setString(jugadores[2].getNombre()+"\t"+utility.toString(jugadores[2].getCapital()));
        txt_banco.setString("Banco:\t"+utility.toString(banco.capital_bancario));

//        back_puntero.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

        window.draw(back_tablero);
        window.draw(back_derecha_tablero);
        window.draw(back_dado_1);
        window.draw(back_dado_2);
        window.draw(txt_banco);
        window.draw(txt_turnos);
        window.draw(back_carta_arca);
        window.draw(back_carta_fortuna);
        window.draw(back_comprar);
        window.draw(back_btnHipotecar);
        window.draw(back_btnDeshipotecar);
        window.draw(back_btnRetirarse);
        window.draw(back_btnTerminar);
        if(mensaje){window.draw(back_info);}
        if(mensaje){window.draw(back_btnAceptar);}
        if(msj_capital_insuf){window.draw(back_capital_insuf);}
        if(msj_capital_insuf){window.draw(back_btnCapital_insuf);}
        if(msj_propiedad_comprada){window.draw(back_propiedad_comprada);}
        if(msj_propiedad_comprada){window.draw(back_btnPropiedad_comprada);}

        if(ficha1){window.draw(*back_ficha_1); window.draw(txt_jugador_1);}
        if(ficha2){window.draw(*back_ficha_2); window.draw(txt_jugador_2);}
        if(ficha3){window.draw(*back_ficha_3); window.draw(txt_jugador_3);}
        if(ficha4){window.draw(*back_ficha_4);}
        if(ficha5){window.draw(*back_ficha_5);}
        if(ficha6){window.draw(*back_ficha_6);}
        if(is_unico){
            window.draw(back_Ganador);
            window.draw(back_btnGanador);
            window.draw(txt_ganador);
        }

        window.display();
    }
}

void JugarMonopoly::ejecutarFunciones(sf::Sprite* sprite,int posJugador, int suma_dados)
{
        if(!jugadores[posJugador].getIsPreso()){
            movimiento(sprite,suma_dados);
        }

        if(sprite->getPosition().x==640&&sprite->getPosition().y==20){
            sprite->setPosition(20,640);
            jugadores[posJugador].setIsPreso(true);
            ventanaSalirCarcel(posJugador);
        }

        if(pagar_renta){
            cobrarRentaPropiedades(sprite,posJugador);
            rentaServicios(sprite,suma_dados,posJugador);
            pagar_renta = false;
        }

        if(cobrar_impuesto&&infoPropiedad(sprite)==-1){
            cobrarImpuestos(sprite,posJugador);
            cobrar_impuesto = false;
        }

        cobrarSalida(sprite,posJugador);
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
    window.setPosition(sf::Vector2i(180, 220));

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
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==495){
        text_titulo.loadFromFile("propiedades/compania_electricidad.png");
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
    else if(sprite->getPosition().x==495&&sprite->getPosition().y==20){
        text_titulo.loadFromFile("propiedades/compania_agua.png");
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
        return 8;
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
    else if(sprite->getPosition().x ==640&&sprite->getPosition().y==495){
        return -1;
    }
    else if(sprite->getPosition().x ==385&&sprite->getPosition().y==640){
        return -1;
    }
    else if(sprite->getPosition().x==20&&sprite->getPosition().y==495){
        return 7;
    }
    else if(sprite->getPosition().x==495&&sprite->getPosition().y==20){
        return 20;
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
    string nombre_propiedad;
    if(propiedades[infoPropiedad(sprite)].getNombreDuenio()=="banco"){
        if(jugadores[posJugador].capital > propiedades[infoPropiedad(sprite)].getValorPropiedad()){
            if(ventanaCompras(sprite,jugadores[posJugador].nombre)){
                jugadores[posJugador].retirar(propiedades[infoPropiedad(sprite)].getValorPropiedad());
                banco.depositar(propiedades[infoPropiedad(sprite)].getValorPropiedad());
                propiedades[infoPropiedad(sprite)].setNombreDuenio(jugadores[posJugador].nombre);
                nombre_propiedad=propiedades[infoPropiedad(sprite)].getNombrePosesion();
                jugadores[posJugador].nombre_propiedades.push_back(nombre_propiedad);
            }
        }else{
            msj_capital_insuf = true;
        }
    }else{
        msj_propiedad_comprada = true;
    }
}

void JugarMonopoly::cobrarImpuestos(sf::Sprite* sprite, int posJugador)
{
    if(sprite->getPosition().x ==640&&sprite->getPosition().y==495){
        jugadores[posJugador].retirar(100);
        banco.depositar(100);
    }

    if(sprite->getPosition().x ==385&&sprite->getPosition().y==640){
        jugadores[posJugador].retirar(200);
        banco.depositar(200);
    }
}

void JugarMonopoly::cobrarSalida(sf::Sprite* sprite,int posJugador)
{
    if(sprite->getPosition().x==640&&sprite->getPosition().y > 20&&sprite->getPosition().y < 640){
        cobrar_salida = true;
    }
    if(cobrar_salida&&sprite->getPosition().x>=20&&sprite->getPosition().y==640){
        jugadores[posJugador].depositar(200);
        banco.retirar(200);
        cobrar_salida = false;
    }
}

void JugarMonopoly::ventanaSalirCarcel(int posJugador)
{
    sf::RenderWindow window;
    sf::Vector2f mouse;
    sf::Texture texture, text_pagar, text_esperar, text_canjear,text_info_carta,text_btnOK;
    sf::Sprite background, back_pagar, back_esperar, back_canjear,back_info_carta,back_btnOK;
    bool no_carta;

    window.create(sf::VideoMode(500,500),"Salir de la Carcel",sf::Style::Close);
    window.setPosition(sf::Vector2i(100, 100));

    texture.loadFromFile("ventanas/info_carcel.png");
    background.setTexture(texture);
    text_pagar.loadFromFile("ventanas/btn_pagar.png");
    back_pagar.setTexture(text_pagar);
    text_esperar.loadFromFile("ventanas/btn_esperar.png");
    back_esperar.setTexture(text_esperar);
    text_canjear.loadFromFile("ventanas/btn_canjear.png");
    back_canjear.setTexture(text_canjear);
    text_info_carta.loadFromFile("ventanas/info_de_carta.png");
    back_info_carta.setTexture(text_info_carta);
    text_btnOK.loadFromFile("ventanas/btnOK.png");
    back_btnOK.setTexture(text_btnOK);

    back_esperar.setPosition(370,150);
    back_pagar.setPosition(370,230);
    back_canjear.setPosition(370,300);
    back_info_carta.setPosition(50,150);
    back_btnOK.setPosition(180,290);

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
        }

        if(utility.clickSprite(back_pagar,mouse)){
            jugadores[posJugador].setIsPreso(false);
            jugadores[posJugador].retirar(50);
            banco.depositar(50);
            window.close();
        }

        if(utility.clickSprite(back_esperar,mouse)){
            window.close();
        }

        if(utility.clickSprite(back_canjear,mouse)){

            if(propiedades[27].getNombreDuenio()==jugadores[posJugador].getNombre()){
                propiedades[27].setNombreDuenio("banco");
            }else{
                no_carta = true;
            }
            if(propiedades[28].getNombreDuenio()==jugadores[posJugador].getNombre()){
                propiedades[28].setNombreDuenio("banco");
            }else{
                no_carta = true;
            }
        }

        if(utility.clickSprite(back_btnOK,mouse)){no_carta = false;}

        window.draw(background);
        window.draw(back_esperar);
        window.draw(back_pagar);
        window.draw(back_canjear);
        if(no_carta){window.draw(back_info_carta);window.draw(back_btnOK);}
        window.display();
    }
}



 bool JugarMonopoly::esperarTresTurnos(int dado1, int dado2, int posJugador)
 {
    if(jugadores[posJugador].acumular_turnos > 0 && jugadores[posJugador].getIsPreso()){
        if(dado1==dado2){
            jugadores[posJugador].setIsPreso(false);
            jugadores[posJugador].acumular_turnos = 3;
            return true;
        }else{
            jugadores[posJugador].acumular_turnos--;
        }

        if(jugadores[posJugador].acumular_turnos == 1){
            if(dado1!=dado2){
                jugadores[posJugador].setIsPreso(false);
                jugadores[posJugador].acumular_turnos = 3;
                jugadores[posJugador].retirar(50);
                banco.depositar(50);
                return true;
            }
        }
    }
    return false;
 }

bool JugarMonopoly::cobrarRentaPropiedades(sf::Sprite* sprite, int posJugador)
{
    if(sprite->getPosition().x !=640&&sprite->getPosition().y!=495){
        if(sprite->getPosition().x !=385&&sprite->getPosition().y!=640){
            Propiedad propiedad = propiedades[infoPropiedad(sprite)];
            if(propiedad.getNombreDuenio()!=jugadores[posJugador].getNombre()&&propiedad.getNombreDuenio()!="banco"){
                if(!propiedad.getEstadoHipoteca()){
                    if(rentaPorColor(propiedad.getNombreDuenio(),propiedad.getColorPropiedad())){
                        jugadores[posJugador].retirar(propiedad.getRenta()*numeroDePropiedadesPorColor(propiedad.getColorPropiedad()));
                        jugadores[buscarJugador(propiedad.getNombreDuenio())].depositar(propiedad.getRenta()*numeroDePropiedadesPorColor(propiedad.getColorPropiedad()));
                        return true;
                    }
                    jugadores[posJugador].retirar(propiedad.getRenta());
                    jugadores[buscarJugador(propiedad.getNombreDuenio())].depositar(propiedad.getRenta());
                    return true;
                }
            }
        }
    }
}

void JugarMonopoly::rentaServicios(sf::Sprite* sprite, int dados,int posJugador)
{
    if(infoPropiedad(sprite)==20||infoPropiedad(sprite)==7){
        Propiedad propiedad = propiedades[infoPropiedad(sprite)];
        if(propiedad.getNombreDuenio()!=jugadores[posJugador].getNombre()&&propiedad.getNombreDuenio()!="banco"){
            if(!propiedad.getEstadoHipoteca()){
                jugadores[posJugador].retirar(dados*4);
                jugadores[buscarJugador(propiedad.getNombreDuenio())].depositar(dados*4);
            }
        }
    }
}

bool JugarMonopoly::rentaPorColor(string duenio, string color)
{
    for(int c = 0; c < propiedades.size(); c++){
        if(propiedades[c].getColorPropiedad()==color&&
           propiedades[c].getNombreDuenio()==duenio){
            return true;
           }
    }
    return false;
}

int JugarMonopoly::numeroDePropiedadesPorColor(string color)
{
    if(color =="marron"||color=="azul"){
        return 2;
    }else if(color =="azulclaro"||color=="rosado"||color=="naranja"||
     color=="rojo"||color=="amarillo"||color=="verde"){
        return 3;
    }
}

int JugarMonopoly::buscarJugador(string nombre)
{
    for(int c = 0;c < jugadores.size();c++)
    {
        if(jugadores[c].getNombre() == nombre){
            return c;
        }
    }
    return -1;
}

void JugarMonopoly::ventanaHipotecar(string nombre, int posJugador)
{
    sf::RenderWindow window;
    sf::View view;
    sf::Texture texture, text_pointer,text_btnVer,text_btnErase,text_btnHipotecar,text_btnHipotecarInact,text_btnSalir;
    sf::Sprite background, back_pointer,back_btnVer,back_info,back_btnClose, back_btnErase,back_btnHipotecar,back_btnHipotecarInact,back_btnSalir;
    sf::Font font;
    sf::Vector2f mouse;
    sf::Text txt1,txt_nombre,txt_ingreso,txt_nombre_propiedad;
    sf::String nombre_propiedad;

    bool is_disabled = true;

    window.create(sf::VideoMode(500,450),"Hipotecas",sf::Style::Close);
    window.setPosition(sf::Vector2i(130, 120));
    window.setMouseCursorVisible(false);
    view = window.getView();

    font.loadFromFile("arial.ttf");

    text_pointer.loadFromFile("punteros/puntero_venta.png");
    back_pointer.setTexture(text_pointer);
    texture.loadFromFile("ventanas/back_hipoteca.png");
    background.setTexture(texture);
    text_btnVer.loadFromFile("ventanas/btnVer.png");
    back_btnVer.setTexture(text_btnVer);
    text_btnErase.loadFromFile("ventanas/backspace.png");
    back_btnErase.setTexture(text_btnErase);
    text_btnHipotecar.loadFromFile("botones/hipotecar.png");
    back_btnHipotecar.setTexture(text_btnHipotecar);
    text_btnHipotecarInact.loadFromFile("botones/hipotecar_inactivo.png");
    back_btnHipotecarInact.setTexture(text_btnHipotecarInact);
    text_btnSalir.loadFromFile("botones/salir.png");
    back_btnSalir.setTexture(text_btnSalir);

    txt_nombre.setFont(font);txt_nombre.setCharacterSize(24);txt_nombre.setColor(sf::Color::Red);
    txt1.setFont(font);txt1.setCharacterSize(16);txt1.setColor(sf::Color::Blue);txt1.setPosition(10,80);
    txt_ingreso.setFont(font);txt_ingreso.setCharacterSize(20);txt_ingreso.setColor(sf::Color::Black);txt_ingreso.setPosition(10,300);
    back_btnVer.setPosition(360,40);
    txt_nombre_propiedad.setFont(font);txt_nombre_propiedad.setCharacterSize(20);
    txt_nombre_propiedad.setColor(sf::Color::Black);txt_nombre_propiedad.setPosition(10,330);

    back_info.setPosition(50,100);
    back_btnClose.setPosition(365,100);
    back_btnErase.setPosition(380,330);
    back_btnHipotecarInact.setPosition(10,380);
    back_btnSalir.setPosition(150,380);

    while(window.isOpen())
    {
        sf::Event event;
        mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::TextEntered)
            {
                nombre_propiedad.insert(nombre_propiedad.getSize(),event.text.unicode);
                txt_nombre_propiedad.setString(nombre_propiedad);
            }

            if(propiedadExiste(nombre_propiedad)){
                is_disabled = false;
                back_btnHipotecar.setPosition(10,380);
            }else{
                is_disabled =true;
            }
        }

        if(utility.clickSprite(back_btnSalir,mouse))
        {
            window.close();
        }

        if(utility.clickSprite(back_btnHipotecar,mouse)){
            hipotecar(nombre_propiedad,posJugador);
            txt_nombre_propiedad.setString("");
            is_disabled = true;
            nombre_propiedad.clear();
        }

        if(utility.clickSprite(back_btnErase,mouse)){
            txt_nombre_propiedad.setString("");
            is_disabled = true;
            nombre_propiedad.clear();
        }

        string ac_nombres="";

        txt_ingreso.setString("Ingrese Nombre Propiedad: ");

        back_pointer.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

        window.draw(background);
        txt_nombre.setString("Propietario: "+nombre);
        if(utility.clickSprite(back_btnVer,mouse)){
            for(int c = 0;c < propiedades.size();c++){
                if(propiedades[c].getNombreDuenio()==nombre&&!propiedades[c].getEstadoHipoteca()){
                    ac_nombres += "Propiedad: "+propiedades[c].getNombrePosesion()+"\tValor Hipoteca: "
                    +utility.toString(propiedades[c].getValorHipoteca())+'\n';
                }
            }

            txt1.setString(ac_nombres);
            if(ac_nombres==""){
                txt1.setCharacterSize(20);
                txt1.setColor(sf::Color::Red);
                txt1.setString("\t\tNo posees ninguna propiedad");
            }
        }

        txt_nombre.setPosition(20,20);

        window.draw(txt_nombre);
        window.draw(txt1);
        window.draw(txt_ingreso);
        window.draw(txt_nombre_propiedad);
        window.draw(back_btnVer);
        window.setView(view);
        window.draw(back_btnErase);
        if(is_disabled){
            window.draw(back_btnHipotecarInact);
        }else{
            window.draw(back_btnHipotecar);
        }
        window.draw(back_btnSalir);
        window.draw(back_pointer);
        window.display();
    }
}

bool JugarMonopoly::hipotecar(sf::String nombre_propiedad,int posJugador)
{
    for(int n = 0; n < propiedades.size(); n++){
        if(nombre_propiedad==propiedades[n].getNombrePosesion()){
            propiedades[n].setEstadoHipoteca(true);
            jugadores[posJugador].depositar(propiedades[n].getValorHipoteca());
            banco.retirar(propiedades[n].getValorHipoteca());
            return true;
        }
    }
    return false;
}

void JugarMonopoly::ventanaDeshipotecar(string nombre, int posJugador){
    sf::RenderWindow window;
    sf::View view;
    sf::Texture texture, text_pointer,text_btnVer,text_btnErase,text_btnDeshipotecar,text_btnDeshipotecarIncat,text_btnSalir;
    sf::Sprite background, back_pointer,back_btnVer,back_btnErase,back_btnDeshipotecar,back_btnDeshipotecarIncat,back_btnSalir;
    sf::Font font;
    sf::Vector2f mouse;
    sf::Text txt1,txt_nombre,txt_ingreso,txt_nombre_propiedad;
    sf::String nombre_propiedad;

    bool is_disabled = true;

    window.create(sf::VideoMode(500,450),"Deshipotecar",sf::Style::Close);
    window.setPosition(sf::Vector2i(130, 120));
    window.setMouseCursorVisible(false);
    view = window.getView();

    font.loadFromFile("arial.ttf");

    text_pointer.loadFromFile("punteros/puntero_compra.png");
    back_pointer.setTexture(text_pointer);
    texture.loadFromFile("ventanas/back_hipoteca.png");
    background.setTexture(texture);
    text_btnVer.loadFromFile("ventanas/btnVer.png");
    back_btnVer.setTexture(text_btnVer);
    text_btnErase.loadFromFile("ventanas/backspace.png");
    back_btnErase.setTexture(text_btnErase);
    text_btnDeshipotecar.loadFromFile("botones/deshipotecar.png");
    back_btnDeshipotecar.setTexture(text_btnDeshipotecar);
    text_btnDeshipotecarIncat.loadFromFile("botones/deshipotecar_inactivo.png");
    back_btnDeshipotecarIncat.setTexture(text_btnDeshipotecarIncat);
    text_btnSalir.loadFromFile("botones/salir.png");
    back_btnSalir.setTexture(text_btnSalir);


    txt_nombre.setFont(font);txt_nombre.setCharacterSize(24);txt_nombre.setColor(sf::Color::Blue);
    txt1.setFont(font);txt1.setCharacterSize(16);txt1.setColor(sf::Color::Blue);txt1.setPosition(10,80);
    txt_ingreso.setFont(font);txt_ingreso.setCharacterSize(20);txt_ingreso.setColor(sf::Color::Black);txt_ingreso.setPosition(10,300);
    back_btnVer.setPosition(360,40);
    txt_nombre_propiedad.setFont(font);txt_nombre_propiedad.setCharacterSize(20);
    txt_nombre_propiedad.setColor(sf::Color::Black);txt_nombre_propiedad.setPosition(10,330);

    back_btnErase.setPosition(380,330);
    back_btnSalir.setPosition(150,380);
    back_btnDeshipotecarIncat.setPosition(10,380);

    while(window.isOpen())
    {
        sf::Event event;
        mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::TextEntered)
            {
                nombre_propiedad.insert(nombre_propiedad.getSize(),event.text.unicode);
                txt_nombre_propiedad.setString(nombre_propiedad);
            }

            if(propiedadExiste(nombre_propiedad)){
                is_disabled = false;
                back_btnDeshipotecar.setPosition(10,380);
            }else{
                is_disabled =true;
            }
        }

         if(utility.clickSprite(back_btnSalir,mouse))
         {
            window.close();
         }

         if(utility.clickSprite(back_btnDeshipotecar,mouse)){
            if(deshipotecar(nombre_propiedad,posJugador)){
                txt_nombre_propiedad.setString("");
                is_disabled = true;
                nombre_propiedad.clear();
            }
         }

        if(utility.clickSprite(back_btnErase,mouse)){
            txt_nombre_propiedad.setString("");
            is_disabled = true;
            nombre_propiedad.clear();
        }

        string ac_nombres="";
        txt_ingreso.setString("Ingrese Nombre Propiedad: ");
        back_pointer.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

        window.draw(background);
        txt_nombre.setString("Propietario: "+nombre);
        if(utility.clickSprite(back_btnVer,mouse)){
            for(int c = 0;c < propiedades.size();c++){
                if(propiedades[c].getNombreDuenio()==nombre&&propiedades[c].getEstadoHipoteca()){
                    ac_nombres += "Propiedad: "+propiedades[c].getNombrePosesion()+"\tValor Deshipoteca: "
                    +utility.toString(propiedades[c].getValorHipoteca()+(propiedades[c].getValorHipoteca()*0.10))+'\n';
                }
            }

            txt1.setString(ac_nombres);
            if(ac_nombres==""){
                txt1.setCharacterSize(20);
                txt1.setColor(sf::Color::Red);
                txt1.setString("\t\tNo tienes propiedades Hipotecadas");
            }
        }

        txt_nombre.setPosition(20,20);

        window.draw(txt_nombre);
        window.draw(txt1);
        window.draw(txt_ingreso);
        window.draw(txt_nombre_propiedad);
        window.draw(back_btnVer);
        window.setView(view);
        window.draw(back_btnErase);
        if(is_disabled){
            window.draw(back_btnDeshipotecarIncat);
        }else{
            window.draw(back_btnDeshipotecar);
        }
        window.draw(back_btnSalir);
        window.draw(back_pointer);
        window.display();
    }
}

bool JugarMonopoly::propiedadExiste(sf::String nombre_propiedad)
{
    for(int i = 0; i < propiedades.size(); i++){
        if(nombre_propiedad==propiedades[i].getNombrePosesion()){
            return true;
        }
    }
    return false;
}

bool JugarMonopoly::deshipotecar(sf::String nombre_propiedad, int posJugador)
{
    int monto = 0;
    for(int i = 0; i < propiedades.size(); i++){
        if(nombre_propiedad==propiedades[i].getNombrePosesion()){
            propiedades[i].setEstadoHipoteca(false);
            monto = propiedades[i].getValorHipoteca()+(propiedades[i].getValorHipoteca()*0.10);
            jugadores[posJugador].retirar(monto);
            banco.retirar(monto);
            return true;
        }
    }
    return false;
}

bool JugarMonopoly::ventanaInventario(string nombre, int posJugador)
{
    sf::RenderWindow window;
    sf::Texture texture, text_pointer, text_btnVer, text_btnRetiro,text_btnRetiroInact,text_btnSalir;
    sf::Sprite background, back_pointer, back_btnVer, back_btnRetiro,back_btnRetiroInact,back_btnSalir;
    sf::View view;
    sf::Text txt_nombre, txt_inventario;
    sf::Font font;
    sf::Vector2f mouse;

    int mi_capital = 0, mis_propiedades = 0, inv = 0;
    bool is_disabled = true;

    window.create(sf::VideoMode(500,350),"Inventario",sf::Style::Close);
    window.setPosition(sf::Vector2i(130, 120));
    window.setMouseCursorVisible(false);
    view = window.getView();

    font.loadFromFile("arial.ttf");

    txt_inventario.setFont(font);
    txt_inventario.setCharacterSize(24);
    txt_inventario.setColor(sf::Color::Black);
    txt_inventario.setPosition(50,100);

    txt_nombre.setFont(font);
    txt_nombre.setCharacterSize(24);
    txt_nombre.setColor(sf::Color::Red);
    txt_nombre.setPosition(50,40);

    texture.loadFromFile("ventanas/back_hipoteca.png");
    background.setTexture(texture);
    text_pointer.loadFromFile("punteros/puntero2.png");
    back_pointer.setTexture(text_pointer);
    text_btnVer.loadFromFile("ventanas/btnVer.png");
    back_btnVer.setTexture(text_btnVer);
    text_btnRetiro.loadFromFile("botones/retiro.png");
    back_btnRetiro.setTexture(text_btnRetiro);
    text_btnRetiroInact.loadFromFile("botones/retiro_inactivo.png");
    back_btnRetiroInact.setTexture(text_btnRetiroInact);
    text_btnSalir.loadFromFile("botones/salir.png");
    back_btnSalir.setTexture(text_btnSalir);

    back_btnVer.setPosition(360,40);
    back_btnRetiroInact.setPosition(50,290);
    back_btnSalir.setPosition(250,290);

    while(window.isOpen())
    {
        sf::Event event;
        mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        while(window.pollEvent(event))
        {

        }
        if(utility.clickSprite(back_btnVer,mouse)){
            back_btnRetiro.setPosition(50,290);
            is_disabled = false;
            mi_capital = jugadores[posJugador].getCapital();
            mis_propiedades = inventario(posJugador);
            inv = mi_capital+mis_propiedades;
            txt_inventario.setString("Efectivo: "+utility.toString(mi_capital)+'\n'+
                                     "Inversión en Propiedades: "+utility.toString(mis_propiedades)+'\n'+
                                     "Mi Capital: "+utility.toString(inv));
        }

        txt_nombre.setString("Jugador: "+jugadores[posJugador].getNombre());

        if(utility.clickSprite(back_btnRetiro,mouse)){
            jugadores[posJugador].retirar(mi_capital);
            jugadores[posJugador].setNombre("retirado");
            banco.depositar(inv);
            for(int t = 0; t < propiedades.size(); t++){
                if(propiedades[t].getNombreDuenio()==jugadores[posJugador].getNombre()){
                    propiedades[t].setNombreDuenio("banco");
                    if(propiedades[t].getEstadoHipoteca()){
                        propiedades[t].setEstadoHipoteca(false);
                    }
                }
            }
            return true;
        }

        if(utility.clickSprite(back_btnSalir,mouse)){
            window.close();
        }

        back_pointer.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

        window.draw(background);
        window.setView(view);
        window.draw(txt_inventario);
        window.draw(txt_nombre);
        window.draw(back_btnVer);
        if(is_disabled){
            window.draw(back_btnRetiroInact);
        }else{
            window.draw(back_btnRetiro);
        }
        window.draw(back_btnSalir);
        window.draw(back_pointer);
        window.display();
    }
    return false;
}

int JugarMonopoly::inventario(int posJugador)
{
    int acumular = 0;
    for(int c = 0;c < propiedades.size(); c++){
        if(propiedades[c].getNombreDuenio()==jugadores[posJugador].getNombre()&&!propiedades[c].getEstadoHipoteca()){
            acumular += propiedades[c].getValorHipoteca();
        }
    }
    return acumular;
}

void JugarMonopoly::ventanaTerminarJuego(){

    sf::RenderWindow window;
    sf::Texture texture, text_btnVer, text_msjGanador, text_btnTerminar,text_btnDisabled, text_btnAceptar, text_msjEmpate, text_btnEmpate, text_btnSalir,text_btnSalirInact;
    sf::Sprite background, back_btnVer, back_msjGanador, back_btnTerminar,back_btnDisabled, back_btnAceptar, back_msjEmpate, back_btnEmpate, back_btnSalir,back_btnSalirInact;
    sf::Font font;
    sf::Text txt_todos, txt_ganador, txt_tituloVenatana;
    sf::Vector2f mouse;
    string acInforme;
    int mayor = 0;
    bool is_ganador = false, is_empate = false, is_visto = false, is_terminado = false;

    window.create(sf::VideoMode(500, 450), "Terminar Juego", sf::Style::Close);
    window.setPosition(sf::Vector2i(130, 120));
    window.setVerticalSyncEnabled(true);

    texture.loadFromFile("ventanas/back_hipoteca.png");
    background.setTexture(texture);
    text_btnVer.loadFromFile("botones/ver_ganador.png");
    back_btnVer.setTexture(text_btnVer);
    text_msjGanador.loadFromFile("ventanas/msj_ganador.png");
    back_msjGanador.setTexture(text_msjGanador);
    text_btnTerminar.loadFromFile("botones/terminar.png");
    back_btnTerminar.setTexture(text_btnTerminar);
    text_btnAceptar.loadFromFile("ventanas/btnAceptarSalida.png");
    back_btnAceptar.setTexture(text_btnAceptar);
    text_msjEmpate.loadFromFile("ventanas/msj_empate.png");
    back_msjEmpate.setTexture(text_msjEmpate);
    text_btnEmpate.loadFromFile("botones/terminar_en_empate.png");
    back_btnEmpate.setTexture(text_btnEmpate);
    text_btnSalir.loadFromFile("botones/salir.png");
    back_btnSalir.setTexture(text_btnSalir);
    text_btnDisabled.loadFromFile("botones/btn_terminar_inactivo.png");
    back_btnDisabled.setTexture(text_btnDisabled);
    text_btnSalirInact.loadFromFile("botones/salir_inactivo.png");
    back_btnSalirInact.setTexture(text_btnSalirInact);


    font.loadFromFile("arial.ttf");

    txt_todos.setFont(font);
    txt_todos.setCharacterSize(22);
    txt_todos.setColor(sf::Color::Blue);
    txt_todos.setPosition(50,100);

    txt_ganador.setFont(font);
    txt_ganador.setCharacterSize(48);
    txt_ganador.setStyle(sf::Text::Bold);
    txt_ganador.setColor(sf::Color::White);
    txt_ganador.setPosition(190,240);

    txt_tituloVenatana.setFont(font);
    txt_tituloVenatana.setCharacterSize(30);
    txt_tituloVenatana.setStyle(sf::Text::Underlined);
    txt_tituloVenatana.setColor(sf::Color::Red);
    txt_tituloVenatana.setPosition(100,50);

    back_btnVer.setPosition(360,40);
    back_msjGanador.setPosition(20,230);
    back_btnSalirInact.setPosition(280,390);
    back_btnAceptar.setPosition(195,340);
    back_btnEmpate.setPosition(160,340);
    back_msjEmpate.setPosition(20,230);
    back_btnDisabled.setPosition(100,390);

    while (window.isOpen())
    {
        sf::Event event;
        mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        while (window.pollEvent(event))
        {

        }

        if(utility.clickSprite(back_btnVer,mouse)){
            is_visto = true;
            back_btnTerminar.setPosition(100,390);
            txt_tituloVenatana.setString("JUGADORES");
            acInforme = "";
            for(int c = 0; c < jugadores.size(); c++){
                if(jugadores[c].getNombre()!="retirado"){
                     acInforme += "Nombre: "+jugadores[c].getNombre()+'\t'+
                                "Capital: "+utility.toString(jugadores[c].getCapital()+inventario(c))+'\n';
                }
            }
            txt_todos.setString(acInforme);
        }

        if(utility.clickSprite(back_btnTerminar,mouse)){
            if(empate()){
                is_empate = true;
            }else{
                is_terminado = true;
                is_ganador = true;
            }
        }

        if(utility.clickSprite(back_btnAceptar,mouse)||utility.clickSprite(back_btnEmpate,mouse)){
            window.close();
            is_close_all = true;
        }

        if(utility.clickSprite(back_btnSalir,mouse)){
            window.close();
        }

        txt_ganador.setString(jugadores[ganador()].getNombre());

        window.draw(background);
        window.draw(back_btnVer);
        if(is_visto){
            window.draw(txt_tituloVenatana);
            window.draw(back_btnTerminar);
        }else{
            window.draw(back_btnDisabled);
        }
        if(is_ganador){
            window.draw(back_msjGanador);
            window.draw(txt_ganador);
            window.draw(back_btnAceptar);
        }
        if(is_empate){
            window.draw(back_msjEmpate);
            window.draw(back_btnEmpate);
        }
        window.draw(back_btnSalirInact);
        if(!is_terminado){
            back_btnSalir.setPosition(280,390);
            window.draw(back_btnSalir);
        }else{
            back_btnSalir.setPosition(-100,-100);
        }
        window.draw(txt_todos);
        window.display();
    }
}

int JugarMonopoly::ganadorPorDefault()
{
    int contador = 0;
    for(int x = 0; x < jugadores.size(); x++){
        if(jugadores[x].getNombre()=="retirado"){
            contador++;
            if(contador==jugadores.size()-1){
                for(int s = 0; s < jugadores.size(); s++){
                    if(jugadores[s].getNombre()!="retirado"){
                        return s;
                    }
                }
            }
        }
    }
    return -1;
}

int JugarMonopoly::ganador()
{
    int mayor = 0, cap_mas_inv = 0;
    int save_pos = 0;

    for(int w = 0; w < jugadores.size(); w++){
        cap_mas_inv = jugadores[w].getCapital()+inventario(w);
        if(cap_mas_inv > mayor){
            mayor = cap_mas_inv;
            save_pos = w;
        }
    }
    return save_pos;
}

bool JugarMonopoly::empate()
{
    int cap_mas_inv = 0,cont_empates=0;
    int save_pos;

    for(int s = 0; s < jugadores.size(); s++){
        cap_mas_inv = jugadores[s].getCapital()+inventario(s);
        if(cap_mas_inv==(jugadores[ganador()].getCapital()+inventario(ganador()))){
            cont_empates++;
        }
    }

    if(cont_empates>1){
        return true;
    }else
        return false;
}

bool JugarMonopoly::mostrarCartaArca(sf::Sprite* sprite)
{
    if(sprite->getPosition().x==495&&sprite->getPosition().y==640
       ||sprite->getPosition().x==20&&sprite->getPosition().y==215
       ||sprite->getPosition().x==640&&sprite->getPosition().y==215)
    {
        if(aumentar_arca==17){
            aumentar_arca = 1;
        }
        aumentar_arca++;
        return true;
    }
    return false;
}

bool JugarMonopoly::mostrarCartaFortuna(sf::Sprite* sprite)
{
    if(sprite->getPosition().x==215&&sprite->getPosition().y==640
       ||sprite->getPosition().x==160&&sprite->getPosition().y==20
       ||sprite->getPosition().x==640&&sprite->getPosition().y==385)
    {
        if(aumentar_fortuna==17){
            aumentar_fortuna = 1;
        }
        aumentar_fortuna++;
        return true;
    }
    return false;
}

void JugarMonopoly::ejecutarCartaArca(sf::Sprite* sprite, int posJugador)
{
    if(aumentar_arca==2){
        jugadores[posJugador].depositar(100);
        banco.retirar(100);
    }
    if(aumentar_arca==3){
        for(int c=0;c<jugadores.size();c++){
            if(jugadores[c].getNombre()!=jugadores[posJugador].getNombre()){
                jugadores[c].retirar(100);
                jugadores[posJugador].depositar(100);
            }
        }
    }
    if(aumentar_arca==4){
        jugadores[posJugador].depositar(100);
        banco.retirar(100);
    }
    if(aumentar_arca==5){
        jugadores[posJugador].depositar(20);
        banco.retirar(20);
    }
    if(aumentar_arca==6){
        jugadores[posJugador].depositar(200);
        banco.retirar(200);
    }
    if(aumentar_arca==7){
        jugadores[posJugador].depositar(25);
        banco.retirar(25);
    }
    if(aumentar_arca==8){
        jugadores[posJugador].depositar(50);
        banco.retirar(50);
    }
    if(aumentar_arca==9){
        jugadores[posJugador].retirar(50);
        banco.depositar(50);
    }
    if(aumentar_arca==10){
        jugadores[posJugador].retirar(50);
        banco.depositar(50);
    }
    if(aumentar_arca==11){
        jugadores[posJugador].retirar(100);
        banco.depositar(100);
    }
    if(aumentar_arca==12){
        sprite->setPosition(20,640);
    }
    if(aumentar_arca==13){
        jugadores[posJugador].depositar(100);
        banco.retirar(100);
    }
    if(aumentar_arca==14){
        jugadores[posJugador].depositar(200);
        banco.retirar(200);
        sprite->setPosition(640,640);
    }
    if(aumentar_arca==15){
        jugadores[posJugador].depositar(10);
        banco.retirar(10);
    }
    if(aumentar_arca==16){
        propiedades[27].setNombreDuenio(jugadores[posJugador].getNombre());
    }
}

void JugarMonopoly::ejecutarCartaFortuna(sf::Sprite* sprite, int posJugador, int dados)
{
    if(aumentar_fortuna==1||aumentar_fortuna==12){
        Propiedad prop;
        int pos;
        if(sprite->getPosition().x==215&&sprite->getPosition().y==640){
            prop = propiedades[2];
            if(prop.getNombreDuenio()!="banco"){
                pos = buscarJugador(prop.getNombreDuenio());
                jugadores[posJugador].retirar(prop.getRenta()*2);
                jugadores[pos].depositar(prop.getRenta()*2);
            }
            sprite->setPosition(325,640);
        }
        if(sprite->getPosition().x==160&&sprite->getPosition().y==20){
            prop = propiedades[17];
            if(prop.getNombreDuenio()!="banco"){
                pos = buscarJugador(prop.getNombreDuenio());
                jugadores[posJugador].retirar(prop.getRenta()*2);
                jugadores[pos].depositar(prop.getRenta()*2);
            }
            sprite->setPosition(325,20);
        }
        if(sprite->getPosition().x==640&&sprite->getPosition().y==385){
            prop = propiedades[25];
            if(prop.getNombreDuenio()!="banco"){
                pos = buscarJugador(prop.getNombreDuenio());
                jugadores[posJugador].retirar(prop.getRenta()*2);
                jugadores[pos].depositar(prop.getRenta()*2);
            }
            sprite->setPosition(640,325);
        }
    }
    if(aumentar_fortuna==2){
        if(sprite->getPosition().x==20&&sprite->getPosition().y < 270
       ||sprite->getPosition().y==20||sprite->getPosition().x==640&&
       sprite->getPosition().y<640)
       {
            jugadores[posJugador].depositar(200);
            banco.retirar(200);
       }
       sprite->setPosition(20,270);
    }
    if(aumentar_fortuna==3){
        int pos;
        Propiedad prop;
        if(sprite->getPosition().x==215&&sprite->getPosition().y==640){
            sprite->setPosition(20,495);
            prop = propiedades[7];
        }
        if(sprite->getPosition().x==160&&sprite->getPosition().y==20
           ||sprite->getPosition().x==640&&sprite->getPosition().y==385){
            sprite->setPosition(495,20);
            prop = propiedades[20];
        }

        if(prop.getNombreDuenio()!= "banco"){
            pos = buscarJugador(prop.getNombreDuenio());
            jugadores[posJugador].retirar((dados*2)*4);
            jugadores[pos].depositar((dados*2)*4);
        }
    }
    if(aumentar_fortuna==4){
        sprite->setPosition(640,640);
        jugadores[posJugador].depositar(200);
        banco.retirar(200);
    }
    if(aumentar_fortuna==5){
        sprite->setPosition(640,555);
    }
    if(aumentar_fortuna==6){
        jugadores[posJugador].retirar(15);
        banco.depositar(15);
    }
    if(aumentar_fortuna==7){
        if(sprite->getPosition().x<=270||sprite->getPosition().x==20
        ||sprite->getPosition().y==20||sprite->getPosition().x==640&&
        sprite->getPosition().y<640)
        {
            jugadores[posJugador].depositar(200);
            banco.retirar(200);
        }
        sprite->setPosition(325,640);
    }
    if(aumentar_fortuna==9){
        for(unsigned int s=0;s<jugadores.size();s++){
            if(jugadores[s].getNombre()!=jugadores[posJugador].getNombre()){
                jugadores[posJugador].retirar(50);
                jugadores[s].depositar(50);
            }
        }
    }
    if(aumentar_fortuna==10){
        if(sprite->getPosition().x>270&&sprite->getPosition().y ==20
        ||sprite->getPosition().x==640&&sprite->getPosition().y<640)
        {
            jugadores[posJugador].depositar(200);
            banco.retirar(200);
        }
        sprite->setPosition(270,20);
    }
    if(aumentar_fortuna==11){
        if(sprite->getPosition().x==215&&sprite->getPosition().y==640){
            sprite->setPosition(385,640);
        }
        if(sprite->getPosition().x==160&&sprite->getPosition().y==20){
            sprite->setPosition(20,105);
        }
        if(sprite->getPosition().x==640&&sprite->getPosition().y==385){
            sprite->setPosition(640,215);
        }
    }
    if(aumentar_fortuna==13){
        propiedades[28].setNombreDuenio(jugadores[posJugador].getNombre());
    }

    if(aumentar_fortuna==14){
        jugadores[posJugador].depositar(150);
        banco.retirar(150);
    }
    if(aumentar_fortuna==15){
        sprite->setPosition(20,640);
    }
    if(aumentar_fortuna==16){
        jugadores[posJugador].depositar(50);
        banco.retirar(50);
    }
}

JugarMonopoly::~JugarMonopoly()
{
    remove(nombre_archivo.c_str());
}
