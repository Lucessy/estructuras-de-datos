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

void Gestor::generarColaReservas(Cola& colaReservas)
{
    if(colaReservas.esVacia() == false)
    {
        vaciarColaReservas(colaReservas);
    }
    string horas[] = {"13:30", "14:30", "15:30"};
    string menus[] = {"vegano", "sinGluten", "completo"};
    string situaciones[] = {"Terraza","Interior"};
    string nombresPosibles[] =
    {
        "Frodo", "Aragorn", "Gandalf", "Legolas", "Gimli",
        "Sam", "Boromir", "Merry", "Pippin", "Sauron",
        "Saruman", "Elrond", "Galadriel", "Faramir", "Denethor",
        "Théoden", "Éowyn", "Gollum", "Bilbo", "Thorin",
        "Dwalin", "Balin", "Kili", "Fili", "Oin",
        "Gloin", "Dori", "Nori", "Ori", "Bombur", //30
        "Gollum", "Bilbo", "Thorin", "Dwalin", "Balin",
        "Kili", "Fili", "Oin", "Gloin", "Dori",
        "Nori", "Ori", "Bombur", "Gollum", "Bilbo",
        "Thorin", "Dwalin", "Balin", "Kili", "Fili",
        "Oin", "Gloin", "Nori", "Ori", "Bombur",
        "Gollum", "Bilbo", "Thorin", "Dwalin", "Balin" //60
    };

    int limite = 12;

    srand(time(0));


    for(int i = 0; i < 20; i++)
    {
        string nombreCliente = nombresPosibles[rand() % 60];
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
        Reserva* preserva = new Reserva(nombreCliente, hora, situacion, numeroPersonas, menu);
        colaReservas.encolar(*preserva);
    }
    cout << "Cola de reservas generada." << endl;
}

void Gestor::mostrarColaReservas(Cola& colaReservas)
{
    colaReservas.mostrarCola();
} //Opción 2

void Gestor::vaciarColaReservas(Cola& colaReservas)
{
    if(colaReservas.esVacia())
    {
        cout << "La cola de reservas ya está vacía." << endl;
        return;
    }
    colaReservas.vaciarCola();
    cout << "Cola de reservas vaciada." << endl;
} //Opción 3

void Gestor::generarPilaMesas(Pila& pilaMesas)
{
    string situaciones[2] = {"Terraza","Interior"};
    int capacidades[2] = {2,4};
    for(int numeroMesa=20; numeroMesa>=1; numeroMesa--)
    {
        //Genera aleatoriamente la capacidad
        int capacidad = capacidades [rand() % 2];
        string situacion = situaciones [rand() % 2];
        Mesa* pmesa = new Mesa(numeroMesa,capacidad,situacion);
        pilaMesas.apilar(*pmesa);
    }
    cout << "Pila de mesas generada." << endl;
} //Opción 4

void Gestor::mostrarPilaMesas(Pila& pilaMesas)
{
    pilaMesas.mostrarPilaMesas();
} //Opción 5

void Gestor::vaciarPilaMesas(Pila& pila)
{
    if(pila.esVacia())
    {
        cout << "La pila de mesas está vacía."<<endl;
        return;
    }
    pila.vaciarPila();
    cout << "Pila de mesas vaciada."<<endl;
} //Opción 6


void Gestor::simularGestionReservaPendiente(Cola& colaReservas, Cola& colaReservasPdtes,Pila& pilaMesas, Lista& listaPedidos)
{

}


//void obtenerMesa?

void Gestor::simularCambioHora(Pila& pilaMesas, Lista& listaPedidos)
{
    listaPedidos.completarSiguientes4Pedidos();
    cout << "Se han marcado los cuatro siguientes pedidos como finalizados y se han liberado sus mesas." << endl;
}


void Gestor::procesarReserva(Reserva* pReserva, Cola& colaReservasPdtes,Pila& pilaMesas, Lista& listaPedidos,bool insertarEnReservasPdtes)
{

    //Se buscan las mesas necesarias con la situación deseada
    bool mesasDisponibles = false;
    int numerosMesa[2] = {0,0};
    if(pReserva->getNumPersonas() <= 4)
    {

    }
    else
    {

    }

    //Si hay mesas disponiles
    if(mesasDisponibles)
    {
        //Se genera el pedido y se añade a la lista de pedidos
        Pedido* pedido = new Pedido(numerosMesa,pReserva->getNombreCliente(),pReserva->getNumPersonas(),pReserva->getPreferenciaMenu(),pReserva->getSituacionMesa(),false);
        listaPedidos.extenderListaPorDerecha(*pedido);
        numReservasGestionadas++;
        delete pReserva;
    }
    else if (insertarEnReservasPdtes)
    {
        //Se añade la reserva a la cola de reservas pendientes
        colaReservasPdtes.encolar(*pReserva);
    }
}


void Gestor::simularGestionProximaReserva(Cola& colaReservas, Cola& colaReservasPdtes,Pila& pilaMesas, Lista& listaPedidos)
{
    //Comprueba que las cola no estén vacía y si se trata de una reserva pendiente en la última
    //pasada de la simulación.
    bool esReservaPdte = false;
    if(colaReservas.esVacia())
    {
        if(colaReservasPdtes.esVacia())
        {
            cout << "No hay reservas que simular.";
            return;
        }
        esReservaPdte = true;
    }

    //Siguiente reserva, ya sea de colaReservas o de colaReservasPdtes
    //Se saca la reserva de la cola
    Reserva* pReserva = siguienteReserva(esReservaPdte,colaReservas,colaReservasPdtes);

    //Se guarda la hora actual para comprobar el cambio de hora
    string horaActual = pReserva->getHoraReserva();

    //Se procesa la siguiente reserva
    procesarReserva(pReserva,colaReservasPdtes,pilaMesas,listaPedidos,!esReservaPdte);

    //Por cada 2 reservas que salen de cola reservas se comprueba una de colas pendientes si la hay
    if(numReservasGestionadas>0 && numReservasGestionadas%2 == 0)
    {
        simularGestionReservaPendiente(colaReservas,colaReservasPdtes,pilaMesas,listaPedidos);
    }

    if(!esReservaPdte)
    {
        //Se comprueba si han terminado todas las reservas de una hora
        if(comprobarCambioHora(horaActual,colaReservas))
        {
            simularCambioHora(pilaMesas,listaPedidos);
        }
    }

} //Opción 7


bool Gestor::comprobarCambioHora(string horaInicial,Cola& colaReservas)
{
    if(colaReservas.esVacia())
    {
        return true;
    }
    else
    {
        Reserva* pSigReserva = colaReservas.inicio();
        if(pSigReserva->getHoraReserva() != horaInicial)
        {
            return true;
        }
    }
    return false;
}


void Gestor::simularGestionReservasProximaHora(Cola& colaReservas, Cola& colaReservasPdtes,Pila& pilaMesas, Lista& listaPedidos)
{
    //Comprueba si la cola está vacía
    if(colaReservas.esVacia())
    {
        cout << "No quedan reservas con hora en la cola de reservas." << endl;
        return;
    }

    //Se guarda la hora actual para comprobar el cambio de hora
    string horaActual = colaReservas.inicio()->getHoraReserva();

    //Procesa reservas mientras no haya cambio de hora
    bool haHabidoCambioHora = false;
    while(!haHabidoCambioHora)
    {
        //Saca la reserva de la cola
        Reserva* pReserva = colaReservas.inicio();
        colaReservas.desencolar();

        //Se procesa la siguiente reserva
        procesarReserva(pReserva,colaReservasPdtes,pilaMesas,listaPedidos,true);

        //Por cada 2 reservas que salen de cola reservas se comprueba una de colas pendientes si la hay
        if(numReservasGestionadas>0 && numReservasGestionadas%2 == 0)
        {
            simularGestionReservaPendiente(colaReservas,colaReservasPdtes,pilaMesas,listaPedidos);
        }

        //Se comprueba si ha habido cambio de mesa
        haHabidoCambioHora = comprobarCambioHora(horaActual,colaReservas);
    }
    //Al terminar simula el cambio de hora
    simularCambioHora(pilaMesas,listaPedidos);
}
//Opción 8


void Gestor::simularGestionReservasTotal(Cola& colaReservas, Cola& colaReservasPdtes,Pila& pilaMesas, Lista& listaPedidos)
{

} //Opción 9



void Gestor::Salir()
{
    cout << "Gracias por usar UltraReserva3000. Nos vemos pronto." << endl;
    //Otras cosas que realizar antes de salir:


} //Opción 0

Reserva* Gestor::siguienteReserva(bool esReservaPdte, Cola& colaReservas, Cola& colaReservasPdtes)
{
    //Siguiente reserva, ya sea de colaReservas o de colaReservasPdtes
    //Se saca la reserva de la cola
    if(!esReservaPdte)
    {
        Reserva* pReserva = colaReservas.inicio();
        colaReservas.desencolar();
        return pReserva;
    }
    else
    {
        Reserva* pReserva = colaReservasPdtes.inicio();
        colaReservasPdtes.desencolar();
        return pReserva;
    }
}
