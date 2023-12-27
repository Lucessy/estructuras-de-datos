#ifndef PILA_H
#define PILA_H
#include <NodoPila.h>
#include "Reserva.h"


class Pila
{
    public:
        Pila();
        virtual ~Pila();

        bool esVacia();
        void apilar(Mesa& mesa);
        void desapilar();
        void mostrarPilaMesas();
        void vaciarPila();
        Mesa& getMesaCima();
        Mesa** buscarMesas(Reserva* pReserva, int capacidad);
        bool contiene(Mesa* mesa);
        void generarMesas(bool seHaComenzadoLaSimulacion);

    protected:

    private:
        NodoPila* cima;
};

#endif // PILA_H
