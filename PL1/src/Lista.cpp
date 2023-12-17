#include "Lista.h"
#include <iostream>
#include <math.h>
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
    longCompleto = 0;
    longSinGluten = 0;
    longVegano = 0;
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
    if(pref == "completo")
    {
        ultCompleto = nuevoNodo;
        longCompleto++;
    }
    else if(pref == "sinGluten")
    {
        ultSinGluten = nuevoNodo;
        longSinGluten++;
    }
    else
    {
        ultVegano = nuevoNodo;
        longVegano++;
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
    if(pref == "completo")
    {
        if(ultCompleto == nullptr){
            ultCompleto = nuevoNodo;
        }
        longCompleto++;
    }
    else if(pref == "sinGluten")
    {
        if(ultSinGluten == nullptr){
            ultSinGluten = nuevoNodo;
        }
        longSinGluten++;
    }
    else
    {
        if(ultVegano == nullptr){
            ultVegano = nuevoNodo;
        }
        longVegano++;
    }

    longitud++;
}



/**
* Extiende la lista con el elemento dado, en su posici�n correspondiente por categor�a.
* Las categor�as se distribuyen en este orden: completo, sinGluten,vegano
* La lista est� siempre ordenada, los nuevos elementos se insertan en su posici�n correspondiente al final su categor�a.
*/
void Lista::extenderListaPorCategoria(Pedido& elem) {
    string categoria = elem.getPreferenciaMenu();

    NodoLista** punteroAUtilizar = nullptr;
    int* contadorAUtilizar = nullptr;

    if(categoria == "completo"){
        punteroAUtilizar = &ultCompleto;
        contadorAUtilizar = &longCompleto;
    }else if (categoria == "sinGluten"){
        punteroAUtilizar = &ultSinGluten;
        contadorAUtilizar = &longSinGluten;
    }else{
        punteroAUtilizar = &ultVegano;
        contadorAUtilizar = &longVegano;
    }

    bool insertar = true;
    if(*punteroAUtilizar == nullptr){
        if(categoria == "vegano"){
            extenderListaPorDerecha(elem);
            insertar = false;
        }else if (categoria == "completo"){
            extenderListaPorIzquierda(elem);
            insertar = false;
        }else{
            if(ultSinGluten != nullptr){
                punteroAUtilizar = &ultSinGluten;
            }else if(ultCompleto != nullptr){
                punteroAUtilizar = &ultCompleto;
            }else{
                extenderListaPorIzquierda(elem);
                insertar = false;
            }
        }
    }
    if(insertar){
        NodoLista* nuevoNodo = new NodoLista(elem,(*punteroAUtilizar)->siguiente,(*punteroAUtilizar));
        (*punteroAUtilizar)->siguiente = nuevoNodo;
        if(*punteroAUtilizar != nullptr){
            (*punteroAUtilizar)->siguiente->anterior = nuevoNodo;
        }
        (*punteroAUtilizar) = nuevoNodo;
        if(nuevoNodo->siguiente == nullptr){
            ultimo = nuevoNodo;
        }
        if(nuevoNodo->anterior == nullptr){
            primero = nuevoNodo;
        }
        (*contadorAUtilizar)++;
        longitud++;
    }
    cout << "Longitud: " << longitud <<endl;
    cout << "LongCompleto: " << longCompleto<<endl;
    cout << "LongSinGluten: " << longSinGluten<<endl;
    cout << "LongVegano: " << longVegano<<endl;
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

        string pref = primero->pPedido->getPreferenciaMenu();
        if(pref == "completo")
        {
            longCompleto--;
            if(longCompleto==0)
            {
                ultCompleto=nullptr;
            }
        }
        else if(pref == "sinGluten")
        {
            longSinGluten--;
            if(longSinGluten==0)
            {
                ultSinGluten=nullptr;
            }
        }
        else
        {
            longVegano--;
            if(longVegano==0)
            {
                ultVegano=nullptr;
            }
        }

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

        string pref = primero->pPedido->getPreferenciaMenu();
        if(pref == "completo")
        {
            longCompleto--;
            if(longCompleto==0)
            {
                ultCompleto=nullptr;
            }
        }
        else if(pref == "sinGluten")
        {
            longSinGluten--;
            if(longSinGluten==0)
            {
                ultSinGluten=nullptr;
            }
        }
        else
        {
            longVegano--;
            if(longVegano==0)
            {
                ultVegano=nullptr;
            }
        }

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


void Lista::mostrarDatosLista(string pref)
{
    if(esVacia())
    {
        cout << "La lista est� vac�a" << endl;
        return;
    }
    NodoLista* aux = primero;
    cout << "Longitud: " << longitud <<endl;
    for(int i = 0; i<longitud; i++)
    {
        if(pref == "" || pref == aux->pPedido->getPreferenciaMenu())
        {
            aux->pPedido->mostrarPedido();
        }
        aux = aux->siguiente;
    }
}


NodoLista* Lista::getPrimero()
{
    return primero;
}

NodoLista* Lista::getUltVegano()
{
    return ultVegano;
}

/**
* Saca de la lista los pedidos finalizados [la mitad de los pedidos de cada preferencia de men�] y devuelve una lista de pedidos con ellos
*/

Lista Lista::sacarSiguientesPedidos(Pila& pilaMesas) {
    Lista listaAux;

    if(ultCompleto != nullptr){
        cout << "Sacando pedidos completos " <<endl;
        NodoLista* primCategoria = primero;
        int* contador = &longCompleto;
        NodoLista** punteroACategoria = &ultCompleto;
        insertarMitadCategoria(listaAux,primCategoria,contador,punteroACategoria);
    }
    if(ultSinGluten != nullptr){
        cout << "Sacando pedidos sin glut�n " <<endl;
        NodoLista* primCategoria = nullptr;
        if(ultCompleto != nullptr){
            primCategoria = ultCompleto->siguiente;
        }else{
            primCategoria = primero;
        }
        cout << "PrimCategoria " <<primCategoria<<endl;
        int* contador = &longSinGluten;
        NodoLista** punteroACategoria = &ultSinGluten;
        insertarMitadCategoria(listaAux,primCategoria,contador,punteroACategoria);
    }
    if(ultVegano != nullptr){
        cout << "Sacando pedidos veganos " <<endl;
        NodoLista* primCategoria = nullptr;
        if(ultSinGluten != nullptr){
            primCategoria = ultSinGluten->siguiente;
        }else if(ultCompleto != nullptr){
            primCategoria = ultCompleto ->siguiente;
        }else{
            primCategoria = primero;
        }
        cout << "PrimCategoria " <<primCategoria<<endl;
        int* contador = &longVegano;
        NodoLista** punteroACategoria = &ultVegano;
        insertarMitadCategoria(listaAux,primCategoria,contador,punteroACategoria);
    }
    cout << "Datos de la lista auxiliar con la mitad de los pedidos de cada categor�a: "<<endl;
    listaAux.mostrarDatosLista();
    finalizarPedidos(listaAux,pilaMesas);
    cout << "Longitud: " << longitud <<endl;
    cout << "LongCompleto: " << longCompleto<<endl;
    cout << "LongSinGluten: " << longSinGluten<<endl;
    cout << "LongVegano: " << longVegano<<endl;
    return listaAux;
}

void Lista::finalizarPedidos(Lista& listaPedidos,Pila& pilaMesas){
    NodoLista* aux = listaPedidos.getPrimero();
    for(int i = 0; i< listaPedidos.getLongitud();i++){
        if(aux->pPedido->getMesaAsignada1() != nullptr){
            pilaMesas.apilar(*(aux->pPedido->getMesaAsignada1()));
        }
        if(aux->pPedido->getMesaAsignada2() != nullptr){
            pilaMesas.apilar(*(aux->pPedido->getMesaAsignada2()));
        }
        aux->pPedido->setFinalizado(true);
        aux=aux->siguiente;
    }
}

/**
* Inserta en la lista auxiliar dada la mitad de los pedidos de la categor�a dada
*/

void Lista::insertarMitadCategoria(Lista& listaAux,NodoLista* primCategoria,int* contadorCategoria,NodoLista** punteroCategoria){

    NodoLista* antPrimCategoria = primCategoria->anterior;
    NodoLista* aux = primCategoria;
    int iters = ceil((*contadorCategoria)/2.0f);
    for(int i=0; i< iters; i++){
        listaAux.extenderListaPorDerecha(*(aux->pPedido));
        longitud--;
        (*contadorCategoria)--;
        NodoLista* tempAux = aux;
        aux=tempAux->siguiente;
        delete tempAux;
    }
    if((*contadorCategoria) == 0){
        *punteroCategoria = nullptr;
    }
    if(aux != nullptr){
        aux->anterior = antPrimCategoria;
    }else{
        ultimo = antPrimCategoria;
    }
    if(antPrimCategoria != nullptr){
        antPrimCategoria->siguiente = aux;
    }
    if(primero == nullptr){
        primero = aux;
    }
}



int Lista::getLongitud()
{
    return longitud;
}

int Lista::getLongCompleto()
{
    return longCompleto;
}

int Lista::getLongSinGluten()
{
    return longSinGluten;
}

int Lista::getLongVegano()
{
    return longVegano;
}
