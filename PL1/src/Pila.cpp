#include "Pila.h"
#include <iostream>
#include "NodoPila.h"
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

void Pila::apilar(const Mesa& mesa)
{
    NodoPila* nuevo = new NodoPila(mesa,cima);
    cima = nuevo;
}

void Pila::vaciarPila()
{
        while(cima)
    {
        desapilar();
    }
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
    NodoPila* aux = cima;
        if(esVacia()){
            cout << "Pila vacia" << endl;
        }
        else{
            cout << "Datos de la pila:" << endl << endl;
            while(aux){
                cout << "Numero de mesa: " << aux->elemento.getNumMesa() << endl;
                cout << "  -Capacidad: " << aux->elemento.getCapacidad() << endl;
                cout << "  -Situación de preferencia: " << aux->elemento.getSituacionMesa() <<  endl;
                aux = aux->siguiente;
            }
            cout << "Fin de los datos de la cola de reservas." << endl;
        }
}
