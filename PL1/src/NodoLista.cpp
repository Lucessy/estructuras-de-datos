#include "NodoLista.h"
#include <iostream>

NodoLista::NodoLista()
{
    //ctor
    valor = 0;
    siguiente = NULL;
    anterior = NULL;
}

NodoLista::~NodoLista()
{
    //dtor
}

NodoLista::NodoLista(int elem, NodoLista* sig, NodoLista* ant)
{
    //ctor
    valor = elem;
    siguiente = sig;
    anterior = ant;
}

