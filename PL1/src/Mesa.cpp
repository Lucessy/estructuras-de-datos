#include "Mesa.h"
#include <iostream>

//numero {1..20}
//Capacidad {2 || 4}
//situacion {Interior || Terraza}

Mesa::Mesa(int numero,int capacidad,string situacionMesa)
{
    this->numMesa=numero;
    this->capacidad=capacidad;
    this->situacionMesa=situacionMesa;
}

Mesa::~Mesa()
{
    //dtor
}

void Mesa::mostrarMesa()
{
    cout << "Numero de mesa: " << numMesa << endl;
    cout << "  -Capacidad: " << capacidad << endl;
    cout << "  -Situación de mesa: " << situacionMesa <<  endl << endl;
}

int Mesa::getNumMesa()
{
    return numMesa;
}

int Mesa::getCapacidad()
{
    return capacidad;
}

string Mesa::getSituacionMesa()
{
    return situacionMesa;
}
