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

    //Crea los placeholders para el puntero que apunta al último nodo tras el cual se insertará el nuevo nodo,
    // el puntero que hay actualizar haciendo que apunte al nuevo nodo (ahora el último de la cagetegoría)
    // y el contador a utilizar, que representa la cantidad de cada tipo de pedido por categoría.
    NodoLista** punteroAUtilizar = nullptr;
    NodoLista** punteroAActualizar = nullptr;
    int* contadorAUtilizar = nullptr;

    //Asigna estos punteros y el contador adecuadamente.
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

    //El puntero a actualizar se iguala al puntero a utilizar y dependerá solo de la categoría.
    punteroAActualizar = punteroAUtilizar;

    //Se comprueba la categoría del pedido si aún no hay ninguno de ese tipo y si cumple ciertas condiciones se inserta directamente llamando a otra función
    // y se marca insertar a falso para no insertarlo manualmente más abajo.
    bool insertar = true;
    //Si el puntero es nulo se comprueban las condiciones
    if(*punteroAUtilizar == nullptr){
        //Si es vegano se extiende la lista por la derecha y así queda el último.
        if(categoria == "vegano"){
            extenderListaPorDerecha(elem);
            insertar = false;

        //Si es completo se inserta en la lista por la izquierda y así queda el primero.
        }else if (categoria == "completo"){
            extenderListaPorIzquierda(elem);
            insertar = false;

        //Si es de tipo sinGluten entonces:
        }else{
            // Si ya hay pedidos completos, el último completo es el puntero a utilizar como último elemento.
            if(ultCompleto != nullptr){
                punteroAUtilizar = &ultCompleto;
            // Si no hay pedidos completos (u sin glutén) , entonces simplemente se inserta por la izquierda y queda el primero.
            }else{
                extenderListaPorIzquierda(elem);
                insertar = false;
            }
        }
    }
    // Si se debe insertar el nuevo elemento se inserta después del elemento al que apunta el puntero a utilizar.
    if(insertar){
        /** Inicio de inserción */
        //Se crea el nuevo nodo usando el puntero a utilizar como último nodo
        NodoLista* nuevoNodo = new NodoLista(elem,(*punteroAUtilizar)->siguiente,(*punteroAUtilizar));
        //Si el siguiente al puntero a utilizar no es null, entonces se actualiza su anterior al nuevo nodo.
        if((*punteroAUtilizar)->siguiente != nullptr){
            (*punteroAUtilizar)->siguiente->anterior = nuevoNodo;
        }
        //Se actualiza el puntero a siguiente el puntero a utilizar al nuevo nodo
        (*punteroAUtilizar)->siguiente = nuevoNodo;
        /** Fin de inserción */

        //Se actualiza el puntero a actulizar que depende unicamente de la categoría para que apunte al último nodo de la categoría, es decir, el recien creado.
        (*punteroAActualizar) = nuevoNodo;

        //Se actualizan el primero y/o el último si es necesario.
        if(nuevoNodo->siguiente == nullptr){
            ultimo = nuevoNodo;
        }
        if(nuevoNodo->anterior == nullptr){
            primero = nuevoNodo;
        }
        //Se actualizan el contador a utilizar y la longitud de la lista
        (*contadorAUtilizar)++;
        longitud++;
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
* Saca de la lista los pedidos finalizados [la mitad de los pedidos de cada categoría] y devuelve una lista auxiliar de pedidos con ellos
*/
Lista Lista::sacarSiguientesPedidos(Pila& pilaMesas) {
    //Crea la lista auxiliar donde se guardarán la mitad de los pedidos de cada categoría
    Lista listaAux;

    cout << "(SacarPedidos)Longitud: " << longitud <<endl;
    cout << "(SacarPedidos)LongCompleto: " << longCompleto<<endl;
    cout << "(SacarPedidos)LongSinGluten: " << longSinGluten<<endl;
    cout << "(SacarPedidos)LongVegano: " << longVegano<<endl;

    /** Para cada tipo de categoría cambia el primCategoria, el contador y el punteroACategoria y llama a la función auxiliar
    insertarMitadCategoria() que inserta en la listaAux la mitad de los pedidos de esa categoría.*/

    //Caso completo
    if(ultCompleto != nullptr){
        cout << "Sacando pedidos completos " <<endl;
        NodoLista* primCategoria = primero;
        int* contador = &longCompleto;
        NodoLista** punteroACategoria = &ultCompleto;
        insertarMitadCategoria(listaAux,primCategoria,contador,punteroACategoria);
    }

    //Caso sin glutén
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

    //Caso vegano
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

    // Se muestran los datos de la lista con los pedidos extraídos
    cout << "Datos de la lista auxiliar con la mitad de los pedidos de cada categoría: "<<endl;
    listaAux.mostrarDatosLista();

    //Se llama a finalizarPedidos lo que libera las mesas de los pedidos y los marca como finalizados
    finalizarPedidos(listaAux,pilaMesas);

    //Finalmente se muestra información de depuración y se devuelve la lista auxiliar.
    cout << "(SacarPedidos)Longitud: " << longitud <<endl;
    cout << "(SacarPedidos)LongCompleto: " << longCompleto<<endl;
    cout << "(SacarPedidos)LongSinGluten: " << longSinGluten<<endl;
    cout << "(SacarPedidos)LongVegano: " << longVegano<<endl;
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

    //Se guarda el anterior del primero de la categoría que puede ser null
    NodoLista* antPrimCategoria = primCategoria->anterior;

    //Se crea un nuevo puntero aux que recorrerá la lista para coger la mitad de los pedidos
    NodoLista* aux = primCategoria;

    //Se calcula el número de pedidos a sacar redondeando hacia arriba los números con decimales
    int iters = ceil((*contadorCategoria)/2.0f);

    //Se recorre la lista usando el puntero auxiliar para sacar los pedidos
    for(int i=0; i< iters; i++){

        //Se añade el pedido del nodo actual a la lista auxiliar
        listaAux.extenderListaPorDerecha(*(aux->pPedido));

        //Se actualiza la longitud en la lista actual de la categoría y la longitud de la lista
        longitud--;
        (*contadorCategoria)--;

        //Se crea un puntero auxiliar temporal para guardar el puntero actual y destruirlo
        NodoLista* tempAux = aux;

        //Cambia el puntero auxiliar para que avance por la lista
        aux = tempAux->siguiente;

        //Se eliminan las referencias al nodo actual y se actualizan adecuadamente
        if(tempAux->siguiente != nullptr){
            tempAux->siguiente->anterior = antPrimCategoria;
        }
        if(tempAux->anterior != nullptr){
            tempAux->anterior->siguiente = tempAux->siguiente;
        }
        //Si en nodo actual era el primer nodo, entonces se actualiza primero para apuntar al siguiente nodo.
        else{
            primero = tempAux->siguiente;
        }
        //Se fijan todos los campos del nodo a null y luego se destruye, liberando su memoria
        tempAux->siguiente = nullptr;
        tempAux->anterior = nullptr;
        tempAux->pPedido = nullptr;
        delete tempAux;
    }
    //Si ya no quedan de la categoría, el puntero al último pedido de esa categoría se actualiza para que no apunte a nada.
    if((*contadorCategoria) == 0){
        *punteroCategoria = nullptr;
    }

    //Si aux no es null se actualiza su nodo anterior
    if(aux != nullptr){
        aux->anterior = antPrimCategoria;
    }
    //En caso contrario se actualiza el puntero a el último nodo de la lista
    else{
        ultimo = antPrimCategoria;
    }
    //Si había un nodo antes del primero para recortar entonces se actualiza el siguiente de ese nodo
    if(antPrimCategoria != nullptr){
        antPrimCategoria->siguiente = aux;
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
