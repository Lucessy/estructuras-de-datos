#ifndef RESERVA_H
#define RESERVA_H
#include <iostream>
#include <string>
using namespace std;

class Reserva
{
    public:
        Reserva(string nombreCliente,string horaReserva);
        Reserva();
        virtual ~Reserva();
        string getNombreCliente();
        string getSituacionMesa();
        int getNumPersonas();
        string getPreferenciaMenu();
        string getHoraReserva();

    protected:

    private:
        string nombreCliente;
        string situacionMesa;
        int numeroPersonas;
        string horaReserva;
        string preferenciaMenu;
};

#endif // RESERVA_H
