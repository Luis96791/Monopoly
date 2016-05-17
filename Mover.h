#ifndef MOVER_H
#define MOVER_H


class Mover
{
    public:
        int x,y;
        Mover(int x,int y);
        int getX();
        int getY();
        virtual ~Mover();

    protected:

    private:
};

#endif // MOVER_H
