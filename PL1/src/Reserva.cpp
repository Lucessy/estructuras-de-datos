#include "Reserva.h"
#include <cstring>

Reserva::Reserva(string nombreCliente,string horaReserva)
{
    this->nombreCliente=nombreCliente;
    this->horaReserva=horaReserva;
}

Reserva::Reserva()
{
    //Create new random reservation
}

Reserva::~Reserva()
{
    //dtor
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

