#ifndef NODOCOLA_H
#define NODOCOLA_H
#include <iostream>
#include "Reserva.h"

class NodoCola
{
    public:
        NodoCola(Reserva& reserva, NodoCola*sig=NULL);
        virtual ~NodoCola();

    protected:

    private:
        //Los atributos
        NodoCola *siguiente;
        Reserva* preserva;
        friend class Cola;
};

#endif // NODOCOLA_H
