#include "Gestor.h"
#include "Cola.h"
#include "Reserva.h"
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

Cola Gestor::generarColaReservas()
{
    Cola cola;
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

        if(i<limite)
        {
            string hora = horas[i / 4];
            Reserva reserva(nombreCliente, hora, situacion, numeroPersonas, menu);
            cola.encolar(reserva);
        }
        else
        {
            string hora = horas[rand() % 3];
            Reserva reserva(nombreCliente, hora, situacion, numeroPersonas, menu);
            cola.encolar(reserva);
        }
    }
    return cola;
}

void Gestor::mostrarColaReservas(Cola colaReservas)
{
    colaReservas.mostrarCola(); //Se puede implementar de esta manera(?
} //Opción 2

Cola Gestor::vaciarColaReservas()
{
    Cola cola;
    return cola;
} //Opción 3

Pila Gestor::generarPilaMesas()
{
    Pila pila;
    return pila;
} //Opción 4

void Gestor::mostrarPilaMesas()
{

} //Opción 5

Pila Gestor::vaciarPilaReservas()
{
    Pila pila;
    return pila;
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
