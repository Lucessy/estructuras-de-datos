#include "ABB.h"
#include <iostream>
using namespace std;

ABB::ABB()
{
    //ctor
    raiz=nullptr;
}

ABB::ABB(NodoABB *r)
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

void ABB::verInOrden()
{
    verInOrden(raiz);
}

void ABB::verInOrden(NodoABB *raiz)
{
    cout << "Entrando en verInOrden..." << endl;
    if(raiz!=nullptr)
    {
        verInOrden(raiz->hijo_i);
        cout << raiz->nombreCliente << endl; //Mostrar datos de cliente y sus pedidos
        //raiz->listaPedidosCliente->mostrarDatosLista();
        verInOrden(raiz->hijo_d);
    }
}

void ABB::insertar(string nombreCliente)
{
    insertar(nombreCliente,raiz);
}

void ABB::insertar(string nombreCliente, NodoABB *nodo)
{
    cout << "Insertando en el árbol" << endl;
    //Da problemas al intentar insertarlo en el arbol MIRARLO
    if((nodo->nombreCliente>nombreCliente)||(nodo->nombreCliente==nombreCliente))
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
