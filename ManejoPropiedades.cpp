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

void ManejoPropiedades::ventanaCompras(sf::Sprite* sprite)
{
    sf::RenderWindow window;
    sf::Texture texture, text_titulo, text_boton_comprar;
    sf::Sprite background, back_titulo, back_boton_comprar;

    window.create(sf::VideoMode(400,250,32),"Comprar Propiedad",sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    texture.loadFromFile("verde.png");
    background.setTexture(texture);

    text_boton_comprar.loadFromFile("ventanas/boton_comprar.png");
    back_boton_comprar.setTexture(text_boton_comprar);

    back_boton_comprar.setPosition(230, 100);

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

    back_titulo.setTexture(text_titulo);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
            {
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
            }
        }
        window.draw(background);
        window.draw(back_titulo);
        window.draw(back_boton_comprar);
        window.display();
    }
}

ManejoPropiedades::~ManejoPropiedades()
{
    //dtor
}
