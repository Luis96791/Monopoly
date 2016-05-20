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

void ManejoPropiedades::ventanaCompras()
{
    sf::RenderWindow window;
    sf::Texture texture;
    sf::Sprite background;

    window.create(sf::VideoMode(400,400,32),"Comprar Propiedad",sf::Style::Close);
    window.setVerticalSyncEnabled(true);

    texture.loadFromFile("verde.png");
    background.setTexture(texture);

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
        window.display();
    }
}

ManejoPropiedades::~ManejoPropiedades()
{
    //dtor
}
