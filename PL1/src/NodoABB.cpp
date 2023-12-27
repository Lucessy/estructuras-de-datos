#include "NodoABB.h"
#include "Lista.h"


NodoABB::NodoABB(string nomCliente,Pedido* pedido, NodoABB *izq, NodoABB *der)
{
    //ctor
    nombreCliente=nomCliente;
    hijo_i=izq;
    hijo_d=der;
    listaPedidosCliente = Lista();
    listaPedidosCliente.extenderListaPorDerecha(*pedido);
}

NodoABB::~NodoABB()
{
    //dtor.
}
