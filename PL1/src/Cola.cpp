#include "Cola.h"
#include "NodoCola.h"
#include <iostream>
#include "Reserva.h"

using namespace std;

Cola::Cola()
{
    //ctor
    primero=NULL;
    ultimo=NULL;
}

Cola::~Cola()
{
    //dtor
}

void Cola::encolar(Reserva& reserva)
{
    NodoCola *nuevo_nodo = new NodoCola(reserva);
    if(esVacia()){
        primero=nuevo_nodo;
        ultimo=nuevo_nodo;
    }else{
        ultimo->siguiente = nuevo_nodo;
        ultimo=nuevo_nodo;
    }
}

void Cola::desencolar()
{
    if(!esVacia()){
        NodoCola *aux = primero;

        if((primero==ultimo)&&(primero->siguiente == NULL)){
            primero=NULL;
            ultimo=NULL;
            aux->siguiente=NULL;
            delete(aux);
        }else{
            primero = primero->siguiente;
            aux->siguiente=NULL;
            delete(aux);
        }
    }
}

void Cola::vaciarCola(){
    while(primero != NULL){
        desencolar();
    }
}

Reserva* Cola::inicio()
{
        if(!esVacia())
        {
            return (primero->preserva);
        }
}

Reserva* Cola::fin()
{
    if(!esVacia())
    {
            return (ultimo->preserva);
    }
}

bool Cola::esVacia()
{
    return((primero==NULL)&&(ultimo==NULL));
}

void Cola::mostrarCola()
{
        NodoCola *aux = primero;
        if(esVacia()){
            cout << "Cola vacia" << endl;
        }
        else{
            cout << "Datos de la cola:" << endl << endl;
            while(aux){
                aux->preserva->mostrarReserva();
                aux = aux->siguiente;
            }
            cout << "Fin de los datos de la cola" << endl << endl;
        }
}

