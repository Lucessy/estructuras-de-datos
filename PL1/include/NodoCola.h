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

    protected:

    private:
        //Los atributos
        NodoCola *siguiente;
        Reserva reserva;
        friend class Cola;
};

#endif // NODOCOLA_H
