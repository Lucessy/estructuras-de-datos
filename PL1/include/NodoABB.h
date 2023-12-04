#ifndef NODOABB_H
#define NODOABB_H

#include <string>
#include "Pedido.h"
#include "Lista.h"
#include "ABB.h"

class ABB;  // Forward declaration

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
