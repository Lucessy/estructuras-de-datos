#include "NodoABB.h"


NodoABB::NodoABB(string nomCliente, NodoABB *izq, NodoABB *der)
{
    //ctor
    nombreCliente=nomCliente;
    hijo_i=izq;
    hijo_d=der;
}

NodoABB::~NodoABB()
{
    //dtor
}
