#ifndef NODOLISTA_H
#define NODOLISTA_H
#include <iostream>
#include <Pedido.h>

class NodoLista
{
    public:
        NodoLista(Pedido& elem, NodoLista*sig=NULL, NodoLista*ant = NULL);
        virtual ~NodoLista();

    protected:

    private:
        Pedido* pPedido;
        NodoLista* siguiente;
        NodoLista* anterior;
        friend class Lista;
        friend class Gestor;
};

#endif // NODOLISTA_H
