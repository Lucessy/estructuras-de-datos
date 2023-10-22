#include "NodoCola.h"

NodoCola::NodoCola()
{
    reserva=Reserva();
    siguiente=NULL;
    //ctor
}


NodoCola::NodoCola(const Reserva& reservaCliente, NodoCola*sig)
{
    reserva = reservaCliente;
    siguiente = sig;
}

NodoCola::~NodoCola()
{
    //dtor
}
