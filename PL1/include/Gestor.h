#ifndef GESTOR_H
#define GESTOR_H
#include "Cola.h"
#include "Pila.h"
#include "Lista.h"
#include <ABB.h>

using namespace std;

class Gestor
{
public:
    Gestor();
    virtual ~Gestor();
    void generarColaReservas(); //Opción 1
    void mostrarColaReservas(); //Opción 2
    void vaciarColaReservas(); //Opción 3

    void generarPilaMesas(); //Opción 4
    void mostrarPilaMesas(); //Opción 5
    void vaciarPilaMesas(); //Opción 6

    void mostrarAbbPedidos(); //Opción 18

    void simularGestionProximaReserva(); //Opción 7
    void simularGestionReservasProximaHora(); //Opción 8
    void simularGestionReservasTotal(); //Opción 9

    void mostrarDatos();

    void Salir(); //Opción 0


    //Atributos públicos
    int numReservasGestionadas;

protected:

private:
    ABB abbPedidos;
    Cola colaReservas;
    Cola colaReservasPdtes;
    Cola colaReservasNoGestionadas;
    Lista listaPedidos;
    Pila pilaMesas;
    void procesarReserva(Reserva* pReserva,bool esReservaPdt, bool esReservaPdtDelFinal);
    void simularCambioHora();
    Reserva* siguienteReserva(bool esReservaPdte);
    bool comprobarCambioHora(string horaInicial);
    void crearPedidos(Mesa** mesas, Reserva* pReserva);

    bool seHaComenzadoLaSimulacion;

};

#endif // GESTOR_H
