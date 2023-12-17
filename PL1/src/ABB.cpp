#include "ABB.h"
#include <iostream>
#include <Lista.h>
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

void ABB::verEnOrden(bool mostrarSoloNombres,bool soloVeganos)
{
    if(raiz == nullptr){
        cout << "El árbol está vacío" << endl;
    }else{
        verEnOrden(raiz,mostrarSoloNombres,0,0,soloVeganos);
    }
}

void ABB::verEnOrden(NodoABB *nodo,bool mostrarSoloNombres,int left_counter,int right_counter,bool soloVeganos)
{
    if(nodo!=nullptr)
    {
        verEnOrden(nodo->hijo_i,mostrarSoloNombres,left_counter+1,right_counter,soloVeganos);

        if(!soloVeganos || (soloVeganos && (nodo->listaPedidosCliente).getUltVegano() != nullptr)){
            //Mostrar datos de cliente y sus pedidos
            if(!mostrarSoloNombres && !soloVeganos){
                cout << "\nNodo: Izq: " << left_counter << " , Der: " << right_counter << endl;
            }
            cout << "Nombre de cliente: " << nodo->nombreCliente << endl;
            if(!mostrarSoloNombres){
                cout << "Lista de pedidos realizados por el cliente: " << endl;
                nodo->listaPedidosCliente.mostrarDatosLista();
            }
        }
        verEnOrden(nodo->hijo_d,left_counter,mostrarSoloNombres,right_counter+1,soloVeganos);
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
        nodo->listaPedidosCliente.extenderListaPorCategoria(*pedido);
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

Lista* ABB::buscarListaPedidosPorNombre(string nombreCliente){
    return buscarListaPedidosPorNombre(nombreCliente,raiz);
}

Lista* ABB::buscarListaPedidosPorNombre(string nombreCliente, NodoABB* nodo)
{
    if(nodo!=nullptr)
    {
        if(nodo->nombreCliente == nombreCliente){
            return &(nodo->listaPedidosCliente);
        }
        Lista* temp = buscarListaPedidosPorNombre(nombreCliente,nodo->hijo_i);
        if(temp == nullptr){
            return buscarListaPedidosPorNombre(nombreCliente,nodo->hijo_d);
        }else{
            return temp;
        }
    }
    return nullptr;
}
