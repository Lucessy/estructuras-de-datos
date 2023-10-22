#ifndef PILA_H
#define PILA_H
#include <NodoPila.h>


class Pila
{
    public:
        Pila();
        virtual ~Pila();

        bool esVacia();
        void apilar(Mesa mesa);
        void desapilar();
        void mostrarPilaMesas();

    protected:

    private:
        NodoPila* cima;
};

#endif // PILA_H
