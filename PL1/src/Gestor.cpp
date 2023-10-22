#include "Gestor.h"
#include "Cola.h"
#include "Reserva.h"
#include "Mesa.h"
#include "Pila.h"
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

using namespace std;

Gestor::Gestor()
{
    //ctor
}

Gestor::~Gestor()
{
    //dtor
}

Cola Gestor::generarColaReservas(Cola& colaReservas)
{
    if(colaReservas.esVacia() == false)
    {
        vaciarColaReservas(colaReservas);
    }
    string horas[3] = {"13:30", "14:30", "15:30"};
    string menus[3] = {"vegano", "sinGluten", "completo"};
    string situaciones[2] = {"Terraza","Interior"};

    int limite = 12;

    srand(time(0));


    for(int i = 0; i < 20; i++)
    {
        string nombreCliente = "Client" + to_string(i+1);
        string menu = menus[rand() % 3];
        string situacion = situaciones [rand() % 2];
        int numeroPersonas = rand() % 8 + 1;

        string hora;
        if(i<limite)
        {
            hora = horas[i / 4];
        }
        else
        {
            hora = horas[rand() % 3];
        }
        Reserva reserva(nombreCliente, hora, situacion, numeroPersonas, menu);
        colaReservas.encolar(reserva);
    }
    cout << "Cola de reservas generada." << endl;
    return colaReservas;
}

void Gestor::mostrarColaReservas(Cola& colaReservas)
{
    colaReservas.mostrarCola(); //Se puede implementar de esta manera(?
} //Opción 2

void Gestor::vaciarColaReservas(Cola& colaReservas)
{
    colaReservas.vaciarCola();
} //Opción 3

Pila Gestor::generarPilaMesas(Pila& pilaMesas)
{
    string situaciones[2] = {"Terraza","Interior"};
    int capacidades[2] = {2,4};
    for(int numeroMesa=1; numeroMesa>=1; numeroMesa--)
    {
        //Genera aleatoriamente la capacidad
        int capacidad = capacidades [rand() % 2];
        string situacion = situaciones [rand() % 2];
        Mesa mesa(numeroMesa,capacidad,situacion);
        pilaMesas.apilar(mesa);
    }
    return pilaMesas;
} //Opción 4

void Gestor::mostrarPilaMesas(Pila& pilaMesas)
{
    pilaMesas.mostrarPilaMesas();
} //Opción 5

void Gestor::vaciarPilaReservas(Pila& pila)
{
    pila.vaciarPila();
} //Opción 6

void Gestor::simularGestionPrimeraReserva(Cola colaReservas, Cola colaReservasPdtes, Lista listaPedidos)
{

} //Opción 7

void Gestor::simularGestionReservasProximaHora(Cola colaReservas, Cola colaReservasPdtes, Lista listaPedidos)
{

}
//Opción 8

void Gestor::simularGestionReservasTotal(Cola colaReservas, Cola colaReservasPdtes, Lista listaPedidos)
{

} //Opción 9

void Gestor::Salir()
{
    cout << "Gracias por usar UltraReserva3000. Nos vemos pronto." << endl;
    //Otras cosas que realizar antes de salir:


} //Opción 0
