#include "Pila.h"
#include <iostream>
using namespace std;


Pila::Pila()
{
    //ctor
    cima=NULL;
}

Pila::~Pila()
{
    //dtor
    while(cima)
    {
        desapilar();
    }
}
bool Pila::esVacia()
{
    return cima == NULL;
}

void Pila::apilar(Mesa mesa)
{
    NodoPila* nuevo = new NodoPila(mesa,cima);
    cima = nuevo;
}

void Pila::desapilar()
{
    NodoPila* nodo;
    if(cima)
    {
        nodo = cima;
        cima = nodo->siguiente;
        delete nodo;
    }
}
void Pila::mostrarCima()
{
    if(esVacia())
    {
        cout << "Pila vacia"<<endl;
    }
    else
    {
        cout << "Número de mesa de cima: " << cima->elemento.numMesa << endl;
    }
}


void Pila::mostrarPilaMesas()
{
    //Muestra los datos de la pila de mesas sin destruirla

}
