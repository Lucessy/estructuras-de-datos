#include "Reserva.h"
#include <cstring>
#include <iostream>
#include "Mesa.h"

Reserva::Reserva(string nombreCliente,string horaReserva,string situacionMesa,int numeroPersonas,string preferenciaMenu)
{
    this->nombreCliente=nombreCliente;
    this->horaReserva=horaReserva;
    this->situacionMesa=situacionMesa;
    this->numeroPersonas=numeroPersonas;
    this->preferenciaMenu=preferenciaMenu;
    this->numeroMesasAsignadas=0;
    this->mesaAsignada1=nullptr;
    this->mesaAsignada2=nullptr;
}


Reserva::~Reserva()
{
    //dtor
}

void Reserva::mostrarReserva()
{
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

Mesa Reserva::getMesaAsignada1()
{
    return *mesaAsignada1;
}

Mesa Reserva::getMesaAsignada2()
{
    return *mesaAsignada2;
}

void Reserva::asignarMesa(Mesa* mesa)
{
    if (numeroMesasAsignadas == 0)
    {
        mesaAsignada1 = mesa;
    }
    else if (numeroMesasAsignadas == 1)
    {
        mesaAsignada2 = mesa;
    }
    numeroMesasAsignadas++;
}

void Reserva::restablecerMesasAsignadas()
{
    mesaAsignada1 = nullptr;
    mesaAsignada2 = nullptr;
    numeroMesasAsignadas = 0;
}

