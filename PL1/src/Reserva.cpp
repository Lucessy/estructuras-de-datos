#include "Reserva.h"
#include <cstring>
#include <iostream>

Reserva::Reserva(string nombreCliente,string horaReserva,string situacionMesa,int numeroPersonas,string preferenciaMenu)
{
    this->nombreCliente=nombreCliente;
    this->horaReserva=horaReserva;
    this->situacionMesa=situacionMesa;
    this->numeroPersonas=numeroPersonas;
    this->preferenciaMenu=preferenciaMenu;
}


Reserva::~Reserva()
{
    //dtor
}

void Reserva::mostrarReserva(){
     cout << "Nombre cliente: " << nombreCliente << endl;
    cout << "  -Hora de la reserva: " << horaReserva << endl;
    cout << "  -Número de personas: " << numeroPersonas << endl;
    cout << "  -Situación de preferencia: " << situacionMesa <<  endl;
    cout << "  -Menú de preferencia: " << preferenciaMenu << endl << endl;
}


//Getters
string Reserva::getNombreCliente()
{
    return nombreCliente;
}

string Reserva::getSituacionMesa()
{
    return situacionMesa;
}

int Reserva::getNumPersonas()
{
    return numeroPersonas;
}

string Reserva::getPreferenciaMenu()
{
    return preferenciaMenu;
}

string Reserva::getHoraReserva()
{
    return horaReserva;
}

