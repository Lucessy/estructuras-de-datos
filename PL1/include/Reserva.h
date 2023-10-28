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
        Mesa getMesaAsignada1();
        Mesa getMesaAsignada2();
        void asignarMesa(Mesa* mesa);
        int getNumeroMesasAsignadas();
        void restablecerMesasAsignadas();

        void mostrarReserva();


    protected:

    private:
        string nombreCliente;
        string situacionMesa;
        int numeroPersonas;
        string horaReserva;
        string preferenciaMenu;
        Mesa* mesaAsignada1;
        Mesa* mesaAsignada2;
        int numeroMesasAsignadas;
};

#endif // RESERVA_H
