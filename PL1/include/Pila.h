#ifndef PILA_H
#define PILA_H
#include <NodoPila.h>
#include "Reserva.h"
#include "Lista.h"


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
        Mesa& getMesaCima();
        bool buscarMesa(Reserva* pReserva, int capacidad, Lista& listaPedidos);

    protected:

    private:
        NodoPila* cima;
};

#endif // PILA_H
