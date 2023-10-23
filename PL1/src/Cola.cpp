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
    longitud=0;
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
    longitud++;
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
        longitud--;
    }
}

void Cola::vaciarCola(){
    while(primero != NULL){
        desencolar();
    }
}

Reserva Cola::inicio()
{
        if(!esVacia())
        {
            return *(primero->preserva);
        }
}

Reserva Cola::fin()
{
    if(!esVacia())
    {
            return *(ultimo->preserva);
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
                cout << "Nombre cliente: " << aux->preserva->getNombreCliente() << endl;
                cout << "  -Hora de la reserva: " << aux->preserva->getHoraReserva() << endl;
                cout << "  -Número de personas: " << aux->preserva->getNumPersonas() << endl;
                cout << "  -Situación de preferencia: " << aux->preserva->getSituacionMesa() <<  endl;
                cout << "  -Menú de preferencia: " << aux->preserva->getPreferenciaMenu() << endl << endl;

                aux = aux->siguiente;
            }
            cout << "Fin de los datos de la cola de reservas." << endl;
        }
}

int Cola::getLongitud()
{
    return longitud;
}

NodoCola& Cola::getNodo(int i) {
    NodoCola* current = primero;
    for (int j = 0; j < i; j++) {
        current = current->siguiente;
    }
    return *current;
}

