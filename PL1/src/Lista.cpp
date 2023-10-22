#include "Lista.h"
#include <iostream>
using namespace std;

Lista::Lista()
{
    //Se crea lista vacia
    primero = NULL;
    ultimo = NULL;
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



void Lista::extenderListaPorDerecha(const Pedido& elem)
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

void Lista::extenderListaPorIzquierda(const Pedido& elem)
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

const Pedido& Lista::elemInicial()
{
    return primero->valor;
}

const Pedido& Lista::elemFinal()
{
    return ultimo->valor;
}

bool Lista::esVacia()
{
    return longitud == 0;
}

const Pedido& Lista::elemEnPosicion(int indice)
{
    NodoLista* aux = primero;
    for(int i = 0; i<indice; i++)
    {
        aux = aux->siguiente;
    }
    return aux->valor;
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
        //cout << aux->valor.nombrePedido << endl;
        aux = aux->siguiente;
    }
}

void Lista::borrarLista()
{

}
