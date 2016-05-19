#ifndef MI_VECTOR_H
#define MI_VECTOR_H
#include <vector>
#include <iostream>

using namespace std;

class Mi_vector
{
    public:
        Mi_vector();
        void setNombre(string n);
        void setEdad(int e);
        string getNombre();
        int getEdad();
        virtual ~Mi_vector();

    protected:
    private:
        string nombre;
        int edad;
};

#endif // MI_VECTOR_H
