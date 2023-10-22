#ifndef NODOCOLA_H
#define NODOCOLA_H
#include <iostream>
#include "Reserva.h"

class NodoCola
{
    public:
        NodoCola();
        //Otro constructor

        NodoCola(const Reserva& reserva, NodoCola*sig=NULL);
        virtual ~NodoCola();
        NodoCola *siguiente;

        Reserva reserva;

    protected:

    private:
        //Los atributos
};

#endif // NODOCOLA_H
