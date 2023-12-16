#include "ABB.h"
#include <iostream>
using namespace std;

ABB::ABB()
{
    //ctor
    raiz=nullptr;
}

ABB::~ABB()
{
    //dtor
}

void ABB::verEnOrden(bool mostrarSoloNombres)
{
    if(raiz == nullptr){
        cout << "El árbol está vacío" << endl;
    }else{
        verEnOrden(raiz,mostrarSoloNombres,0,0);
    }
}

void ABB::verEnOrden(NodoABB *nodo,bool mostrarSoloNombres,int left_counter,int right_counter)
{
    if(nodo!=nullptr)
    {
        verEnOrden(nodo->hijo_i,mostrarSoloNombres,left_counter+1,right_counter);
        //Mostrar datos de cliente y sus pedidos
        if(!mostrarSoloNombres){
            cout << "\nNodo: Izq: " << left_counter << " , Der: " << right_counter << endl;
        }
        cout << "Nombre de cliente: " << nodo->nombreCliente << endl;
        if(!mostrarSoloNombres){
            cout << "Lista de pedidos realizados por el cliente: " << endl;
            nodo->listaPedidosCliente.mostrarDatosLista();
        }
        verEnOrden(nodo->hijo_d,left_counter,mostrarSoloNombres,right_counter+1);
    }
}

void ABB::insertar(string nombreCliente, Pedido* pedido)
{
    insertar(nombreCliente, pedido, raiz);
}

void ABB::insertar(string nombreCliente, Pedido* pedido, NodoABB *nodo)
{
    cout << "Insertando en el árbol" << endl;

    if(raiz == nullptr){
        raiz = new NodoABB(nombreCliente,pedido,nullptr,nullptr);
        cout << "Añadida nueva raiz" <<endl;
        return;
    }

    //Da problemas al intentar insertarlo en el arbol MIRARLO
    if (nodo->nombreCliente == nombreCliente){
        //nodo->listaPedidosCliente.extenderListaPorCategoria(*pedido);
    }
    else if(nodo->nombreCliente > nombreCliente)
    {
        if(nodo->hijo_i == nullptr)
        {
            NodoABB *nuevo = new NodoABB(nombreCliente, pedido); // Hay que colocar si es igual a uno se sustituye
            nodo->hijo_i=nuevo;
        }
        else
        {
            insertar(nombreCliente,pedido,nodo->hijo_i);
        }
    }
    else
    {
        if(nodo->hijo_d == nullptr)
        {
            NodoABB *nuevo = new NodoABB(nombreCliente,pedido);
            nodo->hijo_d=nuevo;
        }
        else
        {
            insertar(nombreCliente,pedido,nodo->hijo_d);
        }
    }
}
