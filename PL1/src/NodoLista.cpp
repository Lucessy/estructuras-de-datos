#include "NodoLista.h"
#include <iostream>
#include <Pedido.h>

NodoLista::NodoLista()
{
    //ctor
    valor = Pedido();
    siguiente = NULL;
    anterior = NULL;
}

NodoLista::~NodoLista()
{
    //dtor
}

NodoLista::NodoLista(const Pedido& elem, NodoLista* sig, NodoLista* ant)
{
    //ctor
    valor = elem;
    siguiente = sig;
    anterior = ant;
}

