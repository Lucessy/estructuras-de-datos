#ifndef NODOLISTA_H
#define NODOLISTA_H
#include <iostream>

class NodoLista
{
    public:
        NodoLista();
        //NodoCola(const Pedido& pedido, NodoCola*sig=NULL);
        NodoLista(int elem, NodoLista*sig=NULL, NodoLista*ant = NULL);
        virtual ~NodoLista();

    protected:

    private:
        int valor;
        NodoLista* siguiente;
        NodoLista* anterior;
        friend class Lista;
};

#endif // NODOLISTA_H
