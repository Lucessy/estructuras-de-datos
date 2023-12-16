#ifndef NODOABB_H
#define NODOABB_H
#include <string>
#include <Lista.h>

using namespace std;

class NodoABB
{
    public:
        NodoABB(string nombreCliente, Pedido* pedido,NodoABB*izq=nullptr, NodoABB*der=nullptr);
        virtual ~NodoABB();

    protected:

    private:
        string nombreCliente;
        Lista listaPedidosCliente;
        NodoABB* hijo_i;
        NodoABB* hijo_d;
        friend class ABB;
};

#endif // NODOABB_H
