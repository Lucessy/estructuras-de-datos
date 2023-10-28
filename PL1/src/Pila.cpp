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

void Pila::apilar(Mesa& mesa)
{
    NodoPila* nuevo = new NodoPila(mesa,cima);
    cima = nuevo;
}

void Pila::vaciarPila()
{
    while(cima!=NULL)
    {
        desapilar();
    }
}

void Pila::desapilar()
{
    if(cima)
    {
        NodoPila* nodo= cima;
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
        cout << "Número de mesa de cima: " << cima->pmesa ->numMesa << endl;
    }
}

Mesa Pila::getCima()
{
    return cima->pmesa;

}

void Pila::mostrarPilaMesas()
{
    NodoPila* aux = cima;
    if(esVacia())
    {
        cout << "Pila vacia" << endl;
    }
    else
    {
        cout << "Datos de la pila:" << endl << endl;
        while(aux)
        {
            aux->pmesa->mostrarMesa();
            aux = aux->siguiente;
        }
        cout << "Fin de los datos de la cola de reservas." << endl;
    }
}

//!!!!!!!!!!!!!!!!!
void Pila::sacarEnPosicion(int posicion)
{
    if (n <= 0)
    {
        // No hay nada que hacer si n es 0 o negativo.
        return;
    }

    if (p.esVacia())
    {
        // No hay suficientes datos en la pila.
        cout << "No hay suficientes datos en la pila." << endl;
        return;
    }

    Mesa mesa;
    p.desapilar();
    sacar_en_pos(p, n - 1);

    if (n != 1)
    {
        p.apilar(mesa);
    }

}
