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
        static Cola generarColaReservas(); //Opción 1
        static void mostrarColaReservas(Cola colaReservas); //Opción 2
        static Cola vaciarColaReservas(); //Opción 3

        static Pila generarPisaMesas(); //Opción 4
        static void mostrarPilaMesas(); //Opción 5
        static Pila vaciarPilaReservas(); //Opción 6

        static void simularGestionPrimeraReserva(Cola colaReservas, Cola colaReservasPdtes, Lista listaPedidos); //Opción 7
        static void simularGestionReservasProximaHora(Cola colaReservas, Cola colaReservasPdtes, Lista listaPedidos); //Opción 8
        static void simularGestionReservasTotal(Cola colaReservas, Cola colaReservasPdtes, Lista listaPedidos); //Opción 9

        static void Salir(); //Opción 0

    protected:

    private:

};

#endif // GESTOR_H
