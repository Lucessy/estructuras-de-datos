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



void Lista::extenderListaPorDerecha(Pedido& elem)
{
    NodoLista* nuevoNodo = new NodoLista(elem,nullptr,ultimo);
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

    string pref = elem.getPreferenciaMenu();
    if(pref == "completo"){
        ultCompleto = nuevoNodo;
    }
    else if(pref == "sinGluten"){
        ultSinGluten = nuevoNodo;
    }
    else{
        ultVegano = nuevoNodo;
    }

    longitud++;
}

void Lista::extenderListaPorIzquierda(Pedido& elem)
{
    NodoLista* nuevoNodo = new NodoLista(elem,primero,nullptr);
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

    string pref = elem.getPreferenciaMenu();
    if(pref == "completo"){
        ultCompleto = nuevoNodo;
    }
    else if(pref == "sinGluten"){
        ultSinGluten = nuevoNodo;
    }
    else{
        ultVegano = nuevoNodo;
    }

    longitud++;
}

/**
* Extiende la lista con el elemento dado, en su posición correspondiente por categoría.
* Las categorías se distribuyen en este orden: completo, sinGluten,vegano
* La lista está siempre ordenada, los nuevos elementos se insertan en su posición correspondiente al final su categoría.
*/
void Lista::extenderListaPorCategoria(Pedido& elem)
{
    string categoria = elem.getPreferenciaMenu();
    NodoLista* sig = nullptr;

    // Se guarda una referencia al puntero que se usará para insertar el elemento dependiendo de su categoría.
    NodoLista** punteroUtilizado = nullptr;
    bool insertar = false;

    if(categoria=="completo")
    {
        // Si aún no hay ningún menú completo la lista simplemente se extiende por la izquierda porque irá primero así
        if(ultCompleto==nullptr)
        {
            extenderListaPorIzquierda(elem);
        }
        else
        {
            insertar = true;
            punteroUtilizado = &ultCompleto;
        }
    }
    else if(categoria=="sinGluten")
    {
        // Si no hay ya un pedido sin glutén, si no hay un pedido completo (el primero de las 3 categorías) se coloca a la izquierda
        // y si sí lo hay entonces se coloca a su derecha
        if(ultSinGluten==nullptr)
        {
            if(ultCompleto!=nullptr)
            {
                //Lo crea justo después del último completo
                NodoLista* nuevoNodo = new NodoLista(elem,ultCompleto->siguiente,ultCompleto);
                longitud++;
                if(ultCompleto->siguiente != nullptr)
                {
                    ultCompleto->siguiente->anterior = nuevoNodo;
                }
                ultCompleto->siguiente = nuevoNodo;
                ultSinGluten = nuevoNodo;
            }
            else
            {
                extenderListaPorIzquierda(elem);
            }
        }
        else
        {
            insertar = true;
            punteroUtilizado = &ultSinGluten;
        }
    }
    else
    {
        // Si no hay ya un último pedido vegano se inserta por la derecha y así será la última categoría como debe ser
        if(ultVegano==nullptr)
        {
            extenderListaPorDerecha(elem);
        }
        else
        {
            insertar = true;
            punteroUtilizado = &ultVegano;
        }
    }

    //Si el pedido no era el primero en ningún caso se inserta en su lugar correspondiente usando el puntero correspondiente a la categoría
    if(insertar){
        NodoLista* nuevoNodo = new NodoLista(elem, (*punteroUtilizado)->siguiente, (*punteroUtilizado));
        longitud++;
        if( (*punteroUtilizado)->siguiente != nullptr){
             (*punteroUtilizado)->siguiente->anterior = nuevoNodo;
        }
        (*punteroUtilizado)->siguiente = nuevoNodo;
        *punteroUtilizado = nuevoNodo;
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
