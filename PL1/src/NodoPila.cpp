#include "NodoPila.h"
#include <Mesa.h>

NodoPila::NodoPila()
{
    elemento = Mesa();
    siguiente = NULL;
}
NodoPila::NodoPila(const Mesa& elemento, NodoPila* sig)
{
    this -> elemento = elemento;
    siguiente = sig;
}

NodoPila::~NodoPila()
{
    //dtor
}
