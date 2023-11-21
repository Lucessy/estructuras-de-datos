#ifndef NODOABB_H
#define NODOABB_H
#include "Pedido.h"
#include "Lista.h"


class NodoABB
{
    public:
        NodoABB(string nombreCliente, NodoABB *izq=nullptr, NodoABB *der=nullptr);
        virtual ~NodoABB();


    protected:

    private:
        string nombreCliente;
        Lista listaPedidosCliente; //Por orden de llegada
        NodoABB *hijo_i;
        NodoABB *hijo_d;

    friend class ABB;
};

#endif // NODOABB_H
