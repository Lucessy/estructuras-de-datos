#include "Cola.h"

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

Cola::encolar(char elemento)
{
    NodoCola *nuevo_nodo = new NodoCola(elemento);
    if(esVacia()){
        primero=nuevo_nodo;
        ultimo=nuevo_nodo;
    }else{
        ultimo->siguiente = nuevo_nodo;
        ultimo=nuevo_nodo;
    }
    longitud++;
}

Cola::desencolar()
{
    if(!esVacia){
        char elemento = primero->elemento;
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
        return elemento;
    }
}

Cola::inicio()
{
        if(!esVacia())
        {
            return primero->elemento;
        }
}

Cola::fin()
{
    if(!esVacia())
    {
            return ultimo->elemento;
    }
}

Cola::esVacia()
{
    return((primero=NULL)&&(ultimo=NULL));
}

Cola::mostrarCola()
{
        NodoCola *aux = primero;
        if(esVacia()){
            cout << "Cola vacia" << endl;
        }
        else{
            cout << "Datos de la cola:" << endl;
            while(aux){
                cout << aux->elemento << endl;
                aux=aux->siguiente;
            }
        }
}

Cola::getLongitud()
{
    return longitud;
}
