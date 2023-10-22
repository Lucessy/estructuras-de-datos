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
        void encolar(const Reserva& reserva);
        Reserva desencolar();
        Reserva inicio();
        Reserva fin();
        bool esVacia();
        void mostrarCola();
        int getLongitud();
        NodoCola& getNodo(int i);

    protected:

    private:
        NodoCola * primero;
        NodoCola * ultimo;
        int longitud;
};

#endif // COLA_H
