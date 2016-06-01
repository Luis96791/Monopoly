#ifndef PADRE_H
#define PADRE_H


class Padre
{
    public:
        Padre();
        int arreglo[10];
        int getPos(int pos);
        void setPosicion(int pos, int num);
        virtual int suma()=0;
        virtual int mayor()=0;
        virtual ~Padre();
    protected:

    private:

};

#endif // PADRE_H
