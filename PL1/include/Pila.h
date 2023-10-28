#ifndef PILA_H
#define PILA_H
#include <NodoPila.h>


class Pila
{
    public:
        Pila();
        virtual ~Pila();

        bool esVacia();
        void apilar(Mesa& mesa);
        void desapilar();
        void mostrarCima();
        void mostrarPilaMesas();
        void vaciarPila();
        Mesa& getCima();


    protected:

    private:
        NodoPila* cima;
};

#endif // PILA_H
