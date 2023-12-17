#include "Lista.h"
#include <iostream>
using namespace std;

Lista::Lista()
{
    //Se crea lista vacia
    primero = nullptr;
    ultimo = nullptr;
    ultCompleto = nullptr;
    ultSinGluten = nullptr;
    ultVegano = nullptr;

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



void Lista::extenderListaPorDerecha(Pedido& elem, int ult)
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

    switch(ult)
    {
    case 0:
        ultCompleto = nuevoNodo;
        break;
    case 1:
        ultSinGluten = nuevoNodo;
        break;
    case 2:
        ultVegano = nuevoNodo;
        break;
    }

    longitud++;
}

void Lista::extenderListaPorIzquierda(Pedido& elem, int ult)
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

    switch(ult)
    {
    case 0:
        ultCompleto = nuevoNodo;
        break;
    case 1:
        ultSinGluten = nuevoNodo;
        break;
    case 2:
        ultVegano = nuevoNodo;
        break;
    }

    longitud++;
}

void Lista::extenderListaPorCategoria(Pedido& elem)
{
    string categoria = elem.getPreferenciaMenu();
    NodoLista* sig = nullptr;
    if(categoria=="completo")
    {
        // 0
        if(ultCompleto==nullptr)
        {
            extenderListaPorIzquierda(elem,0);
        }
        else
        {
            NodoLista* nuevoNodo = new NodoLista(elem,ultCompleto->siguiente,ultCompleto);
            ultCompleto->siguiente->anterior = nuevoNodo;
            ultCompleto->siguiente = nuevoNodo;
            ultCompleto = nuevoNodo;
            longitud++;
        }
    }
    else if(categoria=="sinGluten")
    {
        // 1
        if(ultSinGluten==nullptr)
        {
            if(ultCompleto!=nullptr)
            {
                NodoLista* nuevoNodo = new NodoLista(elem,ultCompleto->siguiente,ultCompleto);
                if(ultCompleto->siguiente != nullptr)
                {
                    ultCompleto->siguiente->anterior = nuevoNodo;
                }
                ultCompleto->siguiente = nuevoNodo;
                ultSinGluten = nuevoNodo;
                longitud++;
            }
            else
            {
                extenderListaPorIzquierda(elem,1);
            }
        }
        else
        {
            NodoLista* nuevoNodo = new NodoLista(elem,ultSinGluten->siguiente,ultSinGluten);
            ultSinGluten->siguiente->anterior = nuevoNodo;
            ultSinGluten->siguiente = nuevoNodo;
            ultSinGluten = nuevoNodo;
            longitud++;
        }
    }
    else
    {
        // 2
        if(ultVegano==nullptr)
        {
            extenderListaPorDerecha(elem,2);
        }
        else
        {
            NodoLista* nuevoNodo = new NodoLista(elem,ultVegano->siguiente,ultVegano);
            ultVegano->siguiente->anterior = nuevoNodo;
            ultVegano->siguiente = nuevoNodo;
            ultVegano = nuevoNodo;
            longitud++;
        }
    }
}

Pedido& Lista::elemInicial()
{
    return *(primero->pPedido);
}

Pedido& Lista::elemFinal()
{
    return *(ultimo->pPedido);
}

void Lista::eliminarPrimero()
{
    if(!esVacia())
    {
        NodoLista *aux = primero;

        if((primero==ultimo)&&(primero->siguiente == NULL))
        {
            primero=NULL;
            ultimo=NULL;
        }
        else
        {
            primero = primero->siguiente;
        }
        aux->siguiente=NULL;
        aux->anterior = NULL;
        delete(aux);
        longitud--;
    }
}

void Lista::eliminarUltimo()
{
    if(!esVacia())
    {
        NodoLista *aux = ultimo;

        if((primero==ultimo)&&(ultimo->siguiente == NULL))
        {
            primero=NULL;
            ultimo=NULL;
        }
        else
        {
            ultimo->anterior->siguiente = NULL;
            ultimo = ultimo->anterior;
        }
        aux->siguiente=NULL;
        aux->anterior = NULL;
        delete(aux);
        longitud--;
    }
}


bool Lista::esVacia()
{
    return longitud == 0;
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


/*
* Saca de la lista los pedidos finalizados [la mitad de los pedidos de cada preferencia de menú] y devuelve una lista de pedidos con ellos
*/
Lista Lista::sacarSiguientesPedidos(Pila& pilaMesas)
{
    int i= 0;
    NodoLista* aux = primero;
    while(aux && i < 4) //Cambiar finalizado por la mitad de cada preferenica de menú
    {
        if(aux->pPedido->getFinalizado() == false)
        {
            aux->pPedido->setFinalizado(true);
            if(aux->pPedido->getMesaAsignada1() != nullptr)
            {
                pilaMesas.apilar(*(aux->pPedido->getMesaAsignada1()));
            }
            if(aux->pPedido->getMesaAsignada2() != nullptr)
            {
                pilaMesas.apilar(*(aux->pPedido->getMesaAsignada2()));
            }
            cout << "Añadiendo a árbol de pedidos" << endl;
            //abbPedidos.insertar(aux->pPedido->getNombreCliente());
            i++;
        }
        aux = aux->siguiente;
    }
}
