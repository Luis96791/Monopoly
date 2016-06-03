#include "JugarMonopoly.h"

JugarMonopoly::JugarMonopoly()
{
    //ctor
}

bool mensaje, msj_capital_insuf,msj_propiedad_comprada, cobrar_salida=false,
    msj_ejecutar_accion,msj_mostrar_accion, carta_arca_activa, carta_fortuna_activa,
     cobrar_impuesto, pagar_renta;
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

    sf::Texture text_tablero,text_dado_1,text_dado_2, text_info, text_btnAceptar, text_derecha_tablero,text_capital_insuf,
        text_btnCapital_insuf,text_propiedad_comprada,text_btnPropiedad_comprada,text_msj_carta,
        text_btnMsj_carta,text_ejecutar_accion,text_btnEjecutar_accion/*,text_puntero*/;
    sf::Texture ref_text_ficha_1,ref_text_ficha_2,ref_text_ficha_3,ref_text_ficha_4,ref_text_ficha_5,ref_text_ficha_6;
    sf::Texture *text_ficha_1, *text_ficha_2,*text_ficha_3,*text_ficha_4,*text_ficha_5,*text_ficha_6;

    sf::Sprite back_tablero,back_dado_1,back_dado_2,back_info, back_btnAceptar, back_derecha_tablero,
        back_btnCapital_insuf,back_propiedad_comprada,back_btnPropiedad_comprada,back_msj_carta,
        back_btnMsj_carta,back_ejecutar_accion,back_btnEjecutar_accion/*,back_puntero*/;
    sf::Sprite ref_back_ficha_1,ref_back_ficha_2,ref_back_ficha_3,ref_back_ficha_4,ref_back_ficha_5,ref_back_ficha_6,back_capital_insuf;
    sf::Sprite *back_ficha_1, *back_ficha_2, *back_ficha_3,*back_ficha_4,*back_ficha_5,*back_ficha_6;

    sf::Vector2f mouse;
    sf::Font font;
//    sf::View view;
    sf::Text txt_jugador_1, txt_jugador_2, txt_banco;
    int suma_dados,guardar_dado_1,guardar_dado_2,clicks=0;
    string nombre_jugador_1, nombre_jugador_2;
    int capital_jugador_1;
    int cant_jugadores;

    nombre_archivo = "jugadores.txt";

    llenarPropiedades();
    cargarJugadores();

    window.create(sf::VideoMode(1360,690,32),"Monopoly",sf::Style::Default);
    window.setVerticalSyncEnabled(true);
//    window.setMouseCursorVisible(false);

//    view = window.getView();

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

    txt_banco.setFont(font);
    txt_banco.setCharacterSize(24);
    txt_banco.setColor(sf::Color::Black);
    txt_banco.setPosition(1055,260);

    txt_turnos.setFont(font);
    txt_turnos.setCharacterSize(24);
    txt_turnos.setColor(sf::Color::Black);
    txt_turnos.setPosition(1155,550);

//    text_puntero.loadFromFile("puntero.png");
//    back_puntero.setTexture(text_puntero);
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
    text_ejecutar_accion.loadFromFile("ventanas/ejecutar_accion.png");
    back_ejecutar_accion.setTexture(text_ejecutar_accion);
    text_btnEjecutar_accion.loadFromFile("ventanas/btnEjecutar_accion.png");
    back_btnEjecutar_accion.setTexture(text_btnEjecutar_accion);


    ifstream cargar("jugadores.txt");
    string n, f;
    bool ficha1,ficha2,ficha3,ficha4,ficha5,ficha6,turno;
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

    cant_jugadores = jugadores.size();

    back_dado_1.setPosition(1140,580);
    back_dado_2.setPosition(1250,580);
    back_carta_arca.setPosition(691,2);
    back_carta_fortuna.setPosition(912,2);
    back_comprar.setPosition(800,150);
    back_info.setPosition(700,250);
    back_btnAceptar.setPosition(800,380);
    back_derecha_tablero.setPosition(690,0);
    back_capital_insuf.setPosition(700,250);
    back_btnCapital_insuf.setPosition(800,380);
    back_propiedad_comprada.setPosition(700,250);
    back_btnPropiedad_comprada.setPosition(800,380);
    back_btnHipotecar.setPosition(800,250);
    back_msj_carta.setPosition(700,250);
    back_ejecutar_accion.setPosition(700,250);
    back_btnEjecutar_accion.setPosition(800,380);


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
                msj_ejecutar_accion = false;
                turno=true;
                cobrar_impuesto = true;
                pagar_renta = true;
                carta_arca_activa = true;
                carta_fortuna_activa = true;
//                cout<<clicks++<<endl;
                guardar_dado_1=utility.dadoUno();
                guardar_dado_2=utility.dadoDos();
                suma_dados=guardar_dado_1+guardar_dado_2;

                text_dado_1.loadFromFile("dados/"+utility.toString(guardar_dado_1)+".png");
                back_dado_1.setTexture(text_dado_1);
                text_dado_2.loadFromFile("dados/"+utility.toString(guardar_dado_2)+".png");
                back_dado_2.setTexture(text_dado_2);
            }

//            if(turno){
//                if(clicks%2==0){
//                    ejecutarFunciones(back_ficha_1,0,suma_dados,mouse);
//                }
//                else if(clicks%1==0){
//                    ejecutarFunciones(back_ficha_2,0,suma_dados,mouse);
//                }
//                turno = false;
//            }

            //CONSTRUYENDO TURNOS

//            if(turno){
//                turno = false;
//                cout<<"entrando al turno"<<endl;
//                if(jugadores.size()%cant_jugadores==3||jugadores.size()%cant_jugadores==2||
//                   jugadores.size()%cant_jugadores==1||jugadores.size()%cant_jugadores==0){
//                    if(cant_jugadores==6){
//                        ejecutarFunciones(back_ficha_6,cant_jugadores-1,suma_dados,mouse);
//                    }else
//                    if(cant_jugadores==5){
//                        ejecutarFunciones(back_ficha_5,cant_jugadores-1,suma_dados,mouse);
//                    }else
//                    if(cant_jugadores==4){
//                        ejecutarFunciones(back_ficha_4,cant_jugadores-1,suma_dados,mouse);
//                    }else
//                    if(cant_jugadores==3){
//                        ejecutarFunciones(back_ficha_3,cant_jugadores-1,suma_dados,mouse);
//                    }else
//                    if(cant_jugadores==2){
//                        ejecutarFunciones(back_ficha_2,cant_jugadores-1,suma_dados,mouse);
//                    }else
//                    if(cant_jugadores==1){
//                        ejecutarFunciones(back_ficha_1,cant_jugadores-1,suma_dados,mouse);
//                    }
//                    cout<<"entrando al residuo"<<endl;
//                    cout<<cant_jugadores<<endl;
//                    cant_jugadores--;
//                }
//                if(cant_jugadores==0){
//                    cant_jugadores = jugadores.size();
//                }
//            }

            if(clicks%2==0){
                movimiento(back_ficha_1,suma_dados);
                cout<<"funcion movimiento ejecutada"<<endl;


                if(mostrarCartaArca(back_ficha_1)&&carta_arca_activa){
                    carta_arca_activa = false;
                    cout<<"aumentar Arca: "<<aumentar_arca<<endl;
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

                if(pagar_renta){
                    cobrarRentaPropiedades(back_ficha_1,0);
                    rentaServicios(back_ficha_1,suma_dados,0);
                    pagar_renta = false;
                }

                cout<<"funcion cobrar renta ejecutada"<<endl;
                if(back_ficha_1->getPosition().x==640&&back_ficha_1->getPosition().y==20){
                    msj_mostrar_accion = true;
                    aLaCarcel(back_ficha_1,0);
                }

                cout<<"a la carcel ejecutada"<<endl;

                if(validarCompra(back_ficha_1)&&utility.clickSprite(back_comprar,mouse)){
                    validarInfoDeCompra(back_ficha_1, 0);
                }
                cout<<"funcion validdar info de compra ejecutada"<<endl;
                if(!validarCompra(back_ficha_1)){
                    if(utility.clickSprite(back_comprar,mouse)){
                        mensaje = true;
                    }
                }
                if(cobrar_impuesto&&infoPropiedad(back_ficha_1)==-1){
                    cobrarImpuestos(back_ficha_1,0);
                    cobrar_impuesto = false;
                }
                cout<<"funcion cobrar impuesto ejecutada"<<endl;

                cobrarSalida(back_ficha_1,0);

                txt_turnos.setString("Turno de: "+jugadores[0].getNombre());
                suma_dados=0;
            }else if(clicks%1==0){
                movimiento(back_ficha_2,suma_dados);

                if(utility.clickSprite(back_btnHipotecar,mouse)){
                    ventanaHipotecar(jugadores[1].getNombre(),1);
                }

                if(mostrarCartaArca(back_ficha_2)&&carta_arca_activa){
                    carta_arca_activa = false;
                    cout<<"aumentar Arca: "<<aumentar_arca<<endl;
                    text_carta_arca.loadFromFile("arca_comunal/"+utility.toString(aumentar_arca)+".png");
                    ejecutarCartaArca(back_ficha_2,1);
                }

                if(mostrarCartaFortuna(back_ficha_2)&&carta_fortuna_activa){
                    carta_fortuna_activa = false;
                    text_carta_fortuna.loadFromFile("fortuna/"+utility.toString(aumentar_fortuna)+".png");
                    ejecutarCartaFortuna(back_ficha_2,1,suma_dados);
                }

                if(pagar_renta){
                    cobrarRentaPropiedades(back_ficha_2,1);
                    rentaServicios(back_ficha_2,suma_dados,1);
                    pagar_renta = false;
                }

                if(back_ficha_2->getPosition().x==640&&back_ficha_2->getPosition().x==20){
                    msj_mostrar_accion = true;
                    aLaCarcel(back_ficha_2,1);
                }

                if(validarCompra(back_ficha_2)&&utility.clickSprite(back_comprar,mouse)){
                    validarInfoDeCompra(back_ficha_2, 1);
                }
                if(!validarCompra(back_ficha_2)){
                    if(utility.clickSprite(back_comprar,mouse)){
                        mensaje = true;
                    }
                }
                if(cobrar_impuesto&&infoPropiedad(back_ficha_2)==-1){
                    cobrarImpuestos(back_ficha_2,1);
                    cobrar_impuesto = false;
                }

                cobrarSalida(back_ficha_2,1);

                cout<<"pos x: "<<back_ficha_2->getPosition().x<<endl;
                cout<<"pos y: "<<back_ficha_2->getPosition().y<<endl;
                cout<<"suma: "<<suma_dados<<endl;
                txt_turnos.setString("Turno de: "+jugadores[1].getNombre());
                suma_dados=0;
            }


            //PROBANDO TABLERO
            if(utility.clickSprite(back_btnAceptar,mouse)){mensaje = false;}
            if(utility.clickSprite(back_btnCapital_insuf,mouse)){msj_capital_insuf = false;}
            if(utility.clickSprite(back_btnPropiedad_comprada,mouse)){msj_propiedad_comprada = false;}
            if(utility.clickSprite(back_btnEjecutar_accion,mouse)){msj_mostrar_accion = false;msj_ejecutar_accion=true;}
        }


        txt_jugador_1.setString(jugadores[0].getNombre()+"\t"+utility.toString(jugadores[0].getCapital()));
        txt_jugador_2.setString(jugadores[1].getNombre()+"\t"+utility.toString(jugadores[1].getCapital()));
        txt_banco.setString("Banco:\t"+utility.toString(banco.capital_bancario));

        if(utility.clickText(txt_jugador_1,mouse)){
            cout<<"Haciendo clic en el texto"<<endl;
        }

//        back_puntero.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

        window.draw(back_tablero);
        window.draw(back_derecha_tablero);
        window.draw(back_dado_1);
        window.draw(back_dado_2);
        window.draw(txt_jugador_1);
        window.draw(txt_jugador_2);
        window.draw(txt_banco);
        window.draw(txt_turnos);
        window.draw(back_carta_arca);
        window.draw(back_carta_fortuna);
        window.draw(back_comprar);
        window.draw(back_btnHipotecar);
        if(mensaje){window.draw(back_info);}
        if(mensaje){window.draw(back_btnAceptar);}
        if(msj_capital_insuf){window.draw(back_capital_insuf);}
        if(msj_capital_insuf){window.draw(back_btnCapital_insuf);}
        if(msj_propiedad_comprada){window.draw(back_propiedad_comprada);}
        if(msj_propiedad_comprada){window.draw(back_btnPropiedad_comprada);}
        if(msj_mostrar_accion){window.draw(back_ejecutar_accion);window.draw(back_btnEjecutar_accion);}
//        window.setView(view);
//        window.draw(back_puntero);

        if(ficha1){window.draw(*back_ficha_1);}
        if(ficha2){window.draw(*back_ficha_2);}
        if(ficha3){window.draw(*back_ficha_3);}
        if(ficha4){window.draw(*back_ficha_4);}
        if(ficha5){window.draw(*back_ficha_5);}
        if(ficha6){window.draw(*back_ficha_6);}

        window.display();
    }
}

void JugarMonopoly::ejecutarFunciones(sf::Sprite* sprite,int posJugador,int suma_dados, sf::Vector2f mouse)
{
    movimiento(sprite,suma_dados);

    if(mostrarCartaArca(sprite)&&carta_arca_activa){
        carta_arca_activa = false;
        text_carta_arca.loadFromFile("arca_comunal/"+utility.toString(aumentar_arca)+".png");
        ejecutarCartaArca(sprite,posJugador);
    }

    if(mostrarCartaFortuna(sprite)&&carta_fortuna_activa){
        carta_fortuna_activa = false;
        text_carta_fortuna.loadFromFile("fortuna/"+utility.toString(aumentar_fortuna)+".png");
        ejecutarCartaFortuna(sprite,posJugador,suma_dados);
    }


    if(utility.clickSprite(back_btnHipotecar,mouse)){
        ventanaHipotecar(jugadores[0].getNombre(),0);
    }

    if(pagar_renta){
        cobrarRentaPropiedades(sprite,posJugador);
        rentaServicios(sprite,suma_dados,posJugador);
        pagar_renta = false;
    }

    if(sprite->getPosition().x==640&&sprite->getPosition().y==20){
        msj_mostrar_accion = true;
        aLaCarcel(sprite,posJugador);
    }

    if(validarCompra(sprite)&&utility.clickSprite(back_comprar,mouse)){
        validarInfoDeCompra(sprite, posJugador);
    }

    if(!validarCompra(sprite)){
        if(utility.clickSprite(back_comprar,mouse)){
            mensaje = true;
        }
    }
    if(cobrar_impuesto&&infoPropiedad(sprite)==-1){
        cobrarImpuestos(sprite,posJugador);
        cobrar_impuesto = false;
    }

    cobrarSalida(sprite,posJugador);

    txt_turnos.setString("Turno de: "+jugadores[0].getNombre());
    suma_dados=0;
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
//    sf::Font font;
    sf::Text text;
//    if(!font.loadFromFile("arial.ttf")){}
//    text.setFont(font);
//    text.setCharacterSize(24);
//    text.setColor(sf::Color::Blue);
    cout<<posJugador<<endl;
    if(propiedades[infoPropiedad(sprite)].getNombreDuenio()=="banco"){
        if(jugadores[posJugador].capital > propiedades[infoPropiedad(sprite)].getValorPropiedad()){
            if(ventanaCompras(sprite,jugadores[posJugador].nombre)){
                jugadores[posJugador].retirar(propiedades[infoPropiedad(sprite)].getValorPropiedad());
                banco.depositar(propiedades[infoPropiedad(sprite)].getValorPropiedad());
                propiedades[infoPropiedad(sprite)].setNombreDuenio(jugadores[posJugador].nombre);
                text.setString(propiedades[infoPropiedad(sprite)].getNombrePosesion());
                jugadores[posJugador].nombre_propiedades.push_back(text);
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

//bool JugarMonopoly::verificarSalida(sf::Sprite* sprite)
//{
//    if(sprite->getPosition().x==640&&sprite->getPosition().y > 20){
//        return true;
//    }
//}

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
            jugadores[posJugador].retirar(50);
            banco.depositar(50);
            window.close();
        }

        if(utility.clickSprite(back_esperar,mouse)){
            jugadores[posJugador].setIsPreso(true);
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

bool JugarMonopoly::aLaCarcel(sf::Sprite* sprite, int posJugador)
{
    if(sprite->getPosition().x==640&&sprite->getPosition().y==20)
    {
        if(msj_ejecutar_accion){
            sprite->setPosition(20,640);
            ventanaSalirCarcel(posJugador);
            return true;
        }
    }
    return false;
}

//bool JugarMonopoly::esperarTresTurnos(int acum, int dado1, int dado2, int posJugador)
//{
//    if(acum <= 3){
//        if(dado1 == dado2){
//            jugadores[posJugador].setIsPreso(false);
//            return true;
//        }
//    }
//
//    if(acum == 3){
//        if(dado1 != dado2){
//            jugadores[posJugador].retirar(50);
//            banco.depositar(50);
//            jugadores[posJugador].setIsPreso(false);
//        }
//    }
//}

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
                    cout<<propiedad.getRenta()<<endl;
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
    sf::Texture texture, text_pointer;
    sf::Sprite background, back_pointer;
    sf::Font font;
    sf::Vector2f mouse;
    sf::Text txt1,txt2,txt3,txt4,txt5,txt6;

    window.create(sf::VideoMode(500,400),"Hipotecas",sf::Style::Close);
    window.setMouseCursorVisible(false);
    view = window.getView();

    if(!font.loadFromFile("arial.ttf")){}

    text_pointer.loadFromFile("punteros/puntero_venta.png");
    back_pointer.setTexture(text_pointer);
    texture.loadFromFile("ventanas/back_hipoteca.png");
    background.setTexture(texture);

    txt1.setFont(font);txt1.setCharacterSize(24);txt1.setColor(sf::Color::Blue);txt1.setPosition(100,50);
    txt2.setFont(font);txt2.setCharacterSize(24);txt2.setColor(sf::Color::Blue);txt2.setPosition(100,100);
    txt3.setFont(font);txt3.setCharacterSize(24);txt3.setColor(sf::Color::Blue);txt3.setPosition(100,150);
    txt4.setFont(font);txt4.setCharacterSize(24);txt4.setColor(sf::Color::Blue);txt4.setPosition(100,200);
    txt5.setFont(font);txt5.setCharacterSize(24);txt5.setColor(sf::Color::Blue);txt5.setPosition(100,250);
    txt6.setFont(font);txt6.setCharacterSize(24);txt6.setColor(sf::Color::Blue);txt6.setPosition(100,300);

    while(window.isOpen())
    {
        sf::Event event;
        mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        while(window.pollEvent(event))
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }

            if(event.type==sf::Event::Closed)
            {
                window.close();
            }
        }

        int x=50, y=20;

        back_pointer.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

        window.draw(background);
//        for(int c = 0;c <jugadores[posJugador].nombre_propiedades.size();c++){
            jugadores[posJugador].nombre_propiedades[0].setFont(font);
            txt1 = jugadores[posJugador].nombre_propiedades[0];
            jugadores[posJugador].nombre_propiedades[1].setFont(font);
            txt2 = jugadores[posJugador].nombre_propiedades[1];
//        }

        window.draw(txt1);
        window.draw(txt2);
        window.draw(txt3);
        window.draw(txt4);
        window.draw(txt5);
        window.draw(txt6);
        window.setView(view);
        window.draw(back_pointer);
        window.display();
    }
}

bool JugarMonopoly::mostrarCartaArca(sf::Sprite* sprite)
{
    if(sprite->getPosition().x==495&&sprite->getPosition().y==640
       ||sprite->getPosition().x==20&&sprite->getPosition().y==215
       ||sprite->getPosition().x==640&&sprite->getPosition().y==215)
    {
        if(aumentar_arca==17){
            aumentar_arca = 0;
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
            aumentar_fortuna = 0;
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
