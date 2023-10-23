#include "Pedido.h"
#include <iostream>

Pedido::Pedido(int numMesa[], string nomCliente, int numPersonas, string prefMenu, string sitMesa, bool finalizado)
{
    numeroMesa[0] = numMesa[0];
    numeroMesa[1] = numMesa[1];
    nombreCliente = nomCliente;
    numeroPersonas = numPersonas;
    preferenciaMenu = prefMenu;
    situacionMesa = sitMesa;
    this->finalizado = finalizado;
}

Pedido::~Pedido()
{
    //dtor
}

void Pedido::mostrarPedido()
{
    cout << "Pedido con nombre de cliente: " << nombreCliente << endl;
    if(numeroMesa[1] == 0){
        cout << "  -Numero de mesa asignada: " <<numeroMesa[0] << endl;
    }else{
        cout << "  -Números de mesas asignadas: " << numeroMesa[0] << " , " << numeroMesa[1] << endl;
    }
    cout << "  -Número de personas: " << numeroPersonas <<  endl;
    cout << "  -Preferencia de menú: " << preferenciaMenu <<  endl;
    cout << "  -Situación de la mesa: " << situacionMesa <<  endl;
    cout << "  -Pedido: " << (finalizado ? "" : "no") << " finalizado" <<  endl;
}


int* Pedido::getpNumMesa(){
    return numeroMesa;
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
