#ifndef GESTOR_H
#define GESTOR_H
#include "Cola.h"
#include "Pila.h"
#include "Lista.h"


class Gestor
{
    public:
        Gestor();
        virtual ~Gestor();
        Cola generarColaReservas(); //Opción 1
        void mostrarColaReservas(Cola colaReservas); //Opción 2
        Cola vaciarColaReservas(); //Opción 3

        Pila generarPisaMesas(); //Opción 4
        void mostrarPilaMesas(); //Opción 5
        Pila vaciarPilaReservas(); //Opción 6

        void simularGestionPrimeraReserva(Cola colaReservas, Cola colaReservasPdtes, Lista listaPedidos); //Opción 7
        void simularGestionReservasProximaHora(Cola colaReservas, Cola colaReservasPdtes, Lista listaPedidos); //Opción 8
        void simularGestionReservasTotal(Cola colaReservas, Cola colaReservasPdtes, Lista listaPedidos); //Opción 9

        void Salir(); //Opción 0

    protected:

    private:

};

#endif // GESTOR_H
