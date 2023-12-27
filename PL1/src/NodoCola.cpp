#include "NodoCola.h"
#include <iostream>


NodoCola::NodoCola(Reserva& reservaCliente, NodoCola*sig)
{
    preserva = &reservaCliente;
    siguiente = sig;
}

NodoCola::~NodoCola()
{
    //dtor.
}
