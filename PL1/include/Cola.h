#ifndef COLA_H
#define COLA_H
#include "NodoCola.h"
#include "Reserva.h"

class Cola
{
    public:
        Cola();
        virtual ~Cola();
        //Metodos de la clase
        void encolar(Reserva& reserva);
        void desencolar();
        Reserva* inicio();
        Reserva* fin();
        bool esVacia();
        void mostrarCola();
        void vaciarCola();
        void generarReservas();

    protected:

    private:
        NodoCola * primero;
        NodoCola * ultimo;
};

#endif // COLA_H
