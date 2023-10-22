#include "NodoPila.h"

NodoPila::NodoPila()
{
    elemento = Mesa();
    siguiente = NULL;
}
NodoPila::NodoPila(Mesa elemento, NodoPila* sig)
{
    this -> elemento = elemento;
    siguiente = sig;
}

NodoPila::~NodoPila()
{
    //dtor
}
