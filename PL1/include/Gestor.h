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
    void generarColaReservas(); //Opción 0
    void mostrarColaReservas(); //Opción 1
    void vaciarColaReservas(); //Opción 2

    void generarPilaMesas(); //Opción 3
    void mostrarPilaMesas(); //Opción 4
    void vaciarPilaMesas(); //Opción 5

    void simularGestionProximaReserva(); //Opción 6
    void simularGestionReservasProximaHora(); //Opción 7
    void simularGestionReservasTotal(); //Opción 8

    void insertarPedidosEnLista(Pedido** pedidos,int longitudPedidos); //Opción 9
    void mostrarListaPedidos(); //Opción 10
    void mostrarColaReservasPendientes(); //Opción 12
    void insertarPedidoEnABB(Pedido* pedido); //Opción 13
    void mostrarAbbPedidos(); //Opción 14
    void mostrarNombresClientesAlfabeticamente(); //Opción 15
    void mostrarPedidosDeCliente(string nombreCliente); //Opción 16
    void mostrarCantidadPedidoPorCategoria(); //Opción 17
    void mostrarClientesConMenuVegano(); //Opción 18

    void Salir(); //Opción 19

    //Funciones públicas auxiliares
    void mostrarDatos();
    bool estaEnPilaMesas(Mesa* mesa);
    Pedido* procesarReserva(Reserva* pReserva,bool esReservaPdt, bool esReservaPdtDelFinal,bool reinsertarEnCola);


protected:

private:

    //Colecciones privadas
    ABB abbPedidos;
    Cola colaReservas;
    Cola colaReservasPdtes;
    Cola colaReservasNoGestionadas;
    Lista listaPedidos;
    Pila pilaMesas;

    //Métodos y funciones privadas
    void simularCambioHora();
    Reserva* siguienteReserva(bool esReservaPdte);
    bool comprobarCambioHora(string horaInicial);
    Pedido* crearPedidos(Mesa** mesas, Reserva* pReserva);

    // Variables privadas
    bool seHaComenzadoLaSimulacion;
    int numReservasGestionadas;

};

#endif // GESTOR_H
