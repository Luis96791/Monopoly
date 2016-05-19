#include "Prueba.h"

Prueba::Prueba()
{
    //ctor
}

void Prueba::setMiVector(Mi_vector vec)
{
    mi_vector.push_back(vec);
}

Mi_vector Prueba::getMiVector(int pos)
{
    return mi_vector[pos];
}

void Prueba::llenarMiVector()
{
    string archivo = "archivo.txt";
    Mi_vector vec;
//    vec.setNombre("luis");vec.setEdad(20);
//    setMiVector(vec);
//    vec.setNombre("luis1");vec.setEdad(30);
//    setMiVector(vec);
//    vec.setNombre("luis2");vec.setEdad(40);
//    setMiVector(vec);

    ifstream in(archivo.c_str());
    string n; int e;
    while(in>>n&&in>>e)
    {
        vec.setNombre(n);
        vec.setEdad(e+25);
        setMiVector(vec);
    }
    in.close();
//    while(e != 0)
//    {
//        cout<<"Ingrese Nombre: ";
//        cin>>n;
//        cout<<"Ingrese Edad: ";
//        cin>>e;
//        vec.setNombre(n);
//        vec.setEdad(e);

//    }

}

void Prueba::mostrarMiVector()
{
    for(unsigned int i=0;i < mi_vector.size(); i++)
    {
        cout<<"Nombre: "<<getMiVector(i).getNombre()<<endl;
        cout<<"Edad: "<<getMiVector(i).getEdad()<<endl;
        cout<<'\n'<<endl;
    }
}

Prueba::~Prueba()
{
    //dtor
}
