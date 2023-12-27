#include "Pedido.h"
#include <iostream>

Pedido::Pedido(Mesa* mesaAsignada[], string nomCliente, int numPersonas, string prefMenu, string sitMesa,bool finalizado)
{
    nombreCliente = nomCliente;
    numeroPersonas = numPersonas;
    preferenciaMenu = prefMenu;
    situacionMesa = sitMesa;
    this->finalizado = finalizado;
    mesa[0] = mesaAsignada[0];
    mesa[1] = mesaAsignada[1];
}

Pedido::~Pedido()
{
    //dtor.
}

void Pedido::mostrarPedido()
{
    cout << "Pedido con nombre de cliente: " << nombreCliente << endl;
    if( mesa[0]!=nullptr && mesa[1]==nullptr)
    {
        cout << "  -Numero de mesa asignada: " <<mesa[0]->getNumMesa() << endl;
    }
    else if(mesa[0]!=nullptr && mesa[1]!=nullptr)
    {
        cout << "  -Números de mesas asignadas: " << mesa[0]->getNumMesa() << " , " << mesa[1]->getNumMesa() << endl;
    }else
    {
        cout << "  -Número de mesa asignada: No hay mesas asignadas" << endl;
    }
    cout << "  -Número de personas: " << numeroPersonas <<  endl;
    cout << "  -Preferencia de menú: " << preferenciaMenu <<  endl;
    cout << "  -Situación de la mesa: " << situacionMesa <<  endl;
    cout << "  -Pedido: " << (finalizado ? "" : "no") << " finalizado" <<  endl << endl;
}

void Pedido::setFinalizado(bool estado)
{
    finalizado = estado;
}


string Pedido::getNombreCliente()
{
    return nombreCliente;
}

int Pedido::getNumPersonas()
{
    return numeroPersonas;
}

string Pedido::getPreferenciaMenu()
{
    return preferenciaMenu;
}

string Pedido::getSituacionMesa()
{
    return situacionMesa;
}

bool Pedido::getFinalizado()
{
    return finalizado;
}

void Pedido::restablecerMesasAsignadas()
{
    mesa[0] = nullptr;
    mesa[1] = nullptr;
}

Mesa* Pedido::getMesaAsignada1()
{
    return mesa[0];
}

Mesa* Pedido::getMesaAsignada2()
{
    return mesa[1];
}
