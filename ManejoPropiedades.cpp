#include "ManejoPropiedades.h"

ManejoPropiedades::ManejoPropiedades()
{
    //ctor
}

void ManejoPropiedades::setPropiedades(Propiedad propiedad)
{
    propiedades.push_back(propiedad);
}

Propiedad ManejoPropiedades::getPropiedades(int pos)
{
    return propiedades[pos];
}

void ManejoPropiedades::llenarPropiedades()
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

void ManejoPropiedades::setPrecio(int p)
{
    precio = p;
}

int ManejoPropiedades::getPrecio()
{
    return precio;
}

void ManejoPropiedades::setDuenio(string d)
{
    duenio = d;
}

string ManejoPropiedades::getDuenio()
{
    return duenio;
}

void ManejoPropiedades::mostrarPropiedades()
{
    for(unsigned int c =0;c < propiedades.size();c++)
    {
        cout<<getPropiedades(c).getNombrePosesion()<<" , "<<getPropiedades(c).getNombreDuenio()<<" , "<<
        getPropiedades(c).getColorPropiedad()<<" , "<<getPropiedades(c).getValorPropiedad()<<" , "<<
        getPropiedades(c).getRenta()<<" , "<<getPropiedades(c).getValorHipoteca()<<" , "<<
        getPropiedades(c).getValorHipoteca()<<" , "<<getPropiedades(c).getEstadoHipoteca()<<endl;
    }
}

bool ManejoPropiedades::ventanaCompras(string nombre, sf::Sprite* sprite)
{
    sf::RenderWindow window;
    sf::Vector2f mouse;
    sf::Texture texture, text_titulo, text_boton_comprar, text_boton_salir;
    sf::Sprite background, back_titulo, back_boton_comprar, back_boton_salir;

    window.create(sf::VideoMode(400,250,32),"Comprar Propiedad",sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    llenarPropiedades();

    texture.loadFromFile("verde.png");
    background.setTexture(texture);

    text_boton_comprar.loadFromFile("ventanas/boton_comprar.png");
    back_boton_comprar.setTexture(text_boton_comprar);
    text_boton_salir.loadFromFile("ventanas/boton_salir.png");
    back_boton_salir.setTexture(text_boton_salir);

    back_boton_comprar.setPosition(230,70);
    back_boton_salir.setPosition(230,140);

    while(window.isOpen())
    {
        mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::Event event;
        while(window.pollEvent(event))
        {

            if(utility.clickSprite(back_boton_salir,mouse)){
                window.close();
                return false;
            }

            if(utility.clickSprite(back_boton_comprar,mouse)){
                window.close();
                return true;
            }
        }

        if(sprite->getPosition().x==555&&sprite->getPosition().y==640){
            text_titulo.loadFromFile("propiedades/avenida_lempira.png");
            setPrecio(propiedades[0].getValorPropiedad());
            setDuenio(nombre);
            cout<<getDuenio()<<endl;
        }
        else if(sprite->getPosition().x==440&&sprite->getPosition().y==640){
            text_titulo.loadFromFile("propiedades/nova_prisa.png");
            setPrecio(propiedades[1].getValorPropiedad());
            propiedades[1].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==270&&sprite->getPosition().y==640){
            text_titulo.loadFromFile("propiedades/avenida_juan_pablo_2.png");
            setPrecio(propiedades[3].getValorPropiedad());
            propiedades[3].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==160&&sprite->getPosition().y==640){
            text_titulo.loadFromFile("propiedades/tercera_avenida.png");
            setPrecio(propiedades[4].getValorPropiedad());
            propiedades[4].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==105&&sprite->getPosition().y==640){
            text_titulo.loadFromFile("propiedades/bulevar_morazan.png");
            setPrecio(propiedades[5].getValorPropiedad());
            propiedades[5].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==20&&sprite->getPosition().y==555){
            text_titulo.loadFromFile("propiedades/avenida_circunvalacion.png");
            setPrecio(propiedades[6].getValorPropiedad());
            propiedades[6].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==20&&sprite->getPosition().y==440){
            text_titulo.loadFromFile("propiedades/105_brigada.png");
            setPrecio(propiedades[8].getValorPropiedad());
            propiedades[8].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==20&&sprite->getPosition().y==385){
            text_titulo.loadFromFile("propiedades/metro_plaza.png");
            setPrecio(propiedades[9].getValorPropiedad());
            propiedades[9].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==20&&sprite->getPosition().y==270){
            text_titulo.loadFromFile("propiedades/expo_centro.png");
            setPrecio(propiedades[11].getValorPropiedad());
            propiedades[11].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==20&&sprite->getPosition().y==160){
            text_titulo.loadFromFile("propiedades/segundo_anillo_periferico.png");
            setPrecio(propiedades[12].getValorPropiedad());
            propiedades[12].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==20&&sprite->getPosition().y==105){
            text_titulo.loadFromFile("propiedades/bulevar_los_proceres.png");
            setPrecio(propiedades[13].getValorPropiedad());
            propiedades[13].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==105&&sprite->getPosition().y==20){
            text_titulo.loadFromFile("propiedades/pasaje_valle.png");
            setPrecio(propiedades[14].getValorPropiedad());
            propiedades[14].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==215&&sprite->getPosition().y==20){
            text_titulo.loadFromFile("propiedades/maheco.png");
            setPrecio(propiedades[15].getValorPropiedad());
            propiedades[15].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==270&&sprite->getPosition().y==20){
            text_titulo.loadFromFile("propiedades/monumento_a_la_madre.png");
            setPrecio(propiedades[16].getValorPropiedad());
            propiedades[16].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==385&&sprite->getPosition().y==20){
            text_titulo.loadFromFile("propiedades/avenida_new_orleans.png");
            setPrecio(propiedades[18].getValorPropiedad());
            propiedades[18].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==440&&sprite->getPosition().y==20){
            text_titulo.loadFromFile("propiedades/mercado_el_rapido.png");
            setPrecio(propiedades[19].getValorPropiedad());
            propiedades[19].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==555&&sprite->getPosition().y==20){
            text_titulo.loadFromFile("propiedades/bulevar_del_norte.png");
            setPrecio(propiedades[21].getValorPropiedad());
            propiedades[21].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==640&&sprite->getPosition().y==105){
            text_titulo.loadFromFile("propiedades/avenida_junior.png");
            setPrecio(propiedades[22].getValorPropiedad());
            propiedades[22].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==640&&sprite->getPosition().y==160){
            text_titulo.loadFromFile("propiedades/molino_harinero_de_sula.png");
            setPrecio(propiedades[23].getValorPropiedad());
            propiedades[23].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==640&&sprite->getPosition().y==270){
            text_titulo.loadFromFile("propiedades/campo_agas.png");
            setPrecio(propiedades[24].getValorPropiedad());
            propiedades[24].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==640&&sprite->getPosition().y==440){
            text_titulo.loadFromFile("propiedades/parque_central.png");
            setPrecio(propiedades[26].getValorPropiedad());
            propiedades[26].setNombreDuenio(nombre);
        }
        else if(sprite->getPosition().x==640&&sprite->getPosition().y==555){
            text_titulo.loadFromFile("propiedades/estadio_olimpico.png");
            setPrecio(propiedades[27].getValorPropiedad());
            propiedades[27].setNombreDuenio(nombre);
        }

        back_titulo.setTexture(text_titulo);

        window.draw(background);
        window.draw(back_titulo);
        window.draw(back_boton_comprar);
        window.draw(back_boton_salir);
        window.display();
    }
}

ManejoPropiedades::~ManejoPropiedades()
{
    //dtor
}
