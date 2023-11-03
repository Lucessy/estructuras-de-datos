#include "Lista.h"
#include <iostream>
using namespace std;

Lista::Lista()
{
    //Se crea lista vacia
    primero = nullptr;
    ultimo = nullptr;
    longitud = 0;
}

Lista::~Lista()
{
    //dtor
    while(primero)
    {
        elemFinal();
    }
}



void Lista::extenderListaPorDerecha(Pedido& elem)
{
    NodoLista* nuevoNodo = new NodoLista(elem,NULL,ultimo);
    if(esVacia())
    {
        primero = nuevoNodo;
        ultimo = nuevoNodo;
    }
    else
    {
        ultimo->siguiente = nuevoNodo;
        ultimo = nuevoNodo;
    }
    longitud++;
}

void Lista::extenderListaPorIzquierda(Pedido& elem)
{
    NodoLista* nuevoNodo = new NodoLista(elem,primero,NULL);
    if(esVacia())
    {
        primero = nuevoNodo;
        ultimo = nuevoNodo;
    }
    else
    {
        primero->anterior = nuevoNodo;
        primero = nuevoNodo;
    }
    longitud++;
}

Pedido& Lista::elemInicial()
{
    return *(primero->pPedido);
}

Pedido& Lista::elemFinal()
{
    return *(ultimo->pPedido);
}

bool Lista::esVacia()
{
    return longitud == 0;
}


Pedido& Lista::elemEnPosicion(int indice)
{
    NodoLista* aux = primero;
    for(int i = 0; i<indice; i++)
    {
        aux = aux->siguiente;
    }
    return *(aux->pPedido);
}

void Lista::mostrarDatosLista()
{
    if(esVacia())
    {
        cout << "La lista está vacía" << endl;
        return;
    }
    NodoLista* aux = primero;
    for(int i = 0; i<longitud; i++)
    {
        aux->pPedido->mostrarPedido();
        aux = aux->siguiente;
    }
}


NodoLista* Lista::getPrimero()
{
    return primero;
}
