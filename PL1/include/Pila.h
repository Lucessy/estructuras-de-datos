#ifndef PILA_H
#define PILA_H
#include <NodoPila.h>


class Pila
{
    public:
        Pila();
        virtual ~Pila();

        bool esVacia();
        void apilar(const Mesa& mesa);
        void desapilar();
        void mostrarCima();
        void mostrarPilaMesas();
        void vaciarPila();

    protected:

    private:
        NodoPila* cima;
};

#endif // PILA_H
