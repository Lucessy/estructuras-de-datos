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
        static Cola generarColaReservas(Cola& colaReservas); //Opción 1
        static void mostrarColaReservas(Cola& colaReservas); //Opción 2
        static void vaciarColaReservas(Cola& colaReservas); //Opción 3

        static Pila generarPilaMesas(Pila& pilaMesas); //Opción 4
        static void mostrarPilaMesas(Pila& pilaMesas); //Opción 5
        static void vaciarPilaMesas(Pila& pila); //Opción 6

        static void simularGestionPrimeraReserva(Cola colaReservas, Cola colaReservasPdtes, Lista listaPedidos); //Opción 7
        static void simularGestionReservasProximaHora(Cola colaReservas, Cola colaReservasPdtes, Lista listaPedidos); //Opción 8
        static void simularGestionReservasTotal(Cola colaReservas, Cola colaReservasPdtes, Lista listaPedidos); //Opción 9

        static void Salir(); //Opción 0

    protected:

    private:

};

#endif // GESTOR_H
