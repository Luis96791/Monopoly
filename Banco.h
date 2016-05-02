#ifndef BANCO_H
#define BANCO_H


class Banco
{
    public:
        int capital_bancario;
        Banco();
        void depositar(int cantidad);
        void retirar(int cantidad);
        virtual ~Banco();

    protected:

    private:
};

#endif // BANCO_H
