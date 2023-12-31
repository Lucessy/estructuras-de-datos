#ifndef RESERVA_H
#define RESERVA_H
#include <iostream>
#include <string>
#include "Mesa.h"
using namespace std;

class Reserva
{
    public:
        Reserva(string nombreCliente,string horaReserva,string situacionMesa,int numeroPersonas,string preferenciaMenu);
        virtual ~Reserva();
        string getNombreCliente();
        string getSituacionMesa();
        int getNumPersonas();
        string getPreferenciaMenu();
        string getHoraReserva();
        void mostrarReserva();

    protected:

    private:
        string nombreCliente;
        string situacionMesa;
        int numeroPersonas;
        string horaReserva;
        string preferenciaMenu;
};

#endif // RESERVA_H
