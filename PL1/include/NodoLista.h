#ifndef NODOLISTA_H
#define NODOLISTA_H
#include <iostream>
#include <Pedido.h>

class NodoLista
{
    public:
        NodoLista();
        //NodoCola(const Pedido& pedido, NodoCola*sig=NULL);
        NodoLista(const Pedido& elem, NodoLista*sig=NULL, NodoLista*ant = NULL);
        virtual ~NodoLista();

    protected:

    private:
        Pedido valor;
        NodoLista* siguiente;
        NodoLista* anterior;
        friend class Lista;
};

#endif // NODOLISTA_H
