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
    if(es_vacia()){
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
    if(!es_vacia){
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
        if(!es_vacia())
        {
            return primero->elemento;
        }
}

Cola::fin()
{
    if(!es_vacia())
    {
            return ultimo->elemento;
    }
}

Cola::es_vacia()
{
    return((primero=NULL)&&(ultimo=NULL));
}

Cola::mostrarCola()
{
        NodoCola *aux = primero;
        if(es_vacia()){
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

Cola::get_longitud()
{
    return longitud;
}
