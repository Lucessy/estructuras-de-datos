#include "ABB.h"
#include "NodoABB.h"

ABB::ABB()
{
    //ctor
    raiz=nullptr;
}

ABB:ABB(NodoABB *r)
{
    raiz=r;
}

ABB::ABB(string nombreCliente, NodoABB *hli, NodoABB *hld)
{
    raiz= new NodoABB(nombreCliente,hli,hld);

}

ABB::~ABB()
{
    //dtor
}

void ABB:verInOrden()
{
    verInOrden(raiz);
}

void ABB::verInOrden(NodoABB *arbol)
{
    if(arb!=nullptr)
    {
        verInOrden(arbol->hijo_i);
        cout << arbol->nombreCliente << endl; //Mostrar datos de cliente y sus pedidos
        cout << "  " << arbol->listaPedidosCliente.mostrarDatosLista() << endl;
        verInOrden(arbol->hijo_d);
    }
}

void ABB::insertar(string nombreCliente)
{
    insertar(nombreCliente,raiz);
}

void ABB::insertar(string nombreCliente, NodoABB *nodo)
{
    if((nodo->valor>nombreCliente)||(nodo->valor==nombreCliente))
    {
        if(nodo->hijo_i == nullptr)
        {
            NodoABB *nuevo = new NodoABB(nombreCliente); // Hay que colocar si es igual a uno se sustituye
            nodo->hijo_i=nuevo;
        }
        else
        {
            insertar(nombreCliente,nodo->hijo_i);
        }
    }
    else
    {
        if(nodo->hijo_d == nullptr)
        {
            NodoABB *nuevo = new NodoABB(nombreCliente);
            nodo->hijo_d=nuevo;
        }
        else
        {
            insertar(nombreCliente,nodo->hijo_d);
        }
    }
}
