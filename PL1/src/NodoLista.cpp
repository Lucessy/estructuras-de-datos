#include "NodoLista.h"
#include <iostream>
#include <Pedido.h>

NodoLista::~NodoLista()
{
    //dtor
}

NodoLista::NodoLista(Pedido& elem, NodoLista* sig, NodoLista* ant)
{
    //ctor
    pPedido = &elem;
    siguiente = sig;
    anterior = ant;
}

