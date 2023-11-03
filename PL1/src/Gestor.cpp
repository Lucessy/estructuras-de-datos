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

void Gestor::generarColaReservas(Cola& colaReservas,int limite)
{
    if(colaReservas.esVacia() == false)
    {
        cout << "Generando nueva cola de reservas. Vaciando la cola anterior." << endl;
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
        "Th�oden", "�owyn", "Gollum", "Bilbo", "Thorin",
        "Dwalin", "Balin", "Kili", "Fili", "Oin",
        "Gloin", "Dori", "Nori", "Ori", "Bombur", //30
        "Gollum", "Bilbo", "Thorin", "Dwalin", "Balin",
        "Kili", "Fili", "Oin", "Gloin", "Dori",
        "Nori", "Ori", "Bombur", "Gollum", "Bilbo",
        "Thorin", "Dwalin", "Balin", "Kili", "Fili",
        "Oin", "Gloin", "Nori", "Ori", "Bombur",
        "Gollum", "Bilbo", "Thorin", "Dwalin", "Balin" //60
    };

    srand(time(0));
    int turnoHora = -1;
    int numReservasPorTurno = (int)limite/3;

    for(int i = 0; i < limite; i++)
    {
        string nombreCliente = nombresPosibles[rand() % 60];
        string menu = menus[rand() % 3];
        string situacion = situaciones [rand() % 2];
        int numeroPersonas = rand() % 8 + 1;

        if((i)%numReservasPorTurno == 0 && turnoHora<2)
        {
            turnoHora ++;
            cout << "Cambio de turno" << i << endl;
        }
        string hora = horas[turnoHora];

        Reserva* preserva = new Reserva(nombreCliente, hora, situacion, numeroPersonas, menu);
        colaReservas.encolar(*preserva);
    }
    cout << "Cola de reservas generada." << endl;
} //Opcio�n 1

void Gestor::mostrarColaReservas(Cola& colaReservas)
{
    colaReservas.mostrarCola();
} //Opci�n 2

void Gestor::vaciarColaReservas(Cola& colaReservas)
{
    if(colaReservas.esVacia())
    {
        cout << "La cola de reservas ya est� vac�a." << endl;
        return;
    }
    colaReservas.vaciarCola();
    cout << "Cola de reservas vaciada." << endl;
} //Opci�n 3

void Gestor::generarPilaMesas(Pila& pilaMesas)
{
    if(!pilaMesas.esVacia())
    {
        cout << "Generando nueva pila de mesas. Vaciando la pila anterior." << endl;
        vaciarPilaMesas(pilaMesas);
    }
    string situaciones[2] = {"Terraza","Interior"};
    int capacidades[2] = {2,4};
    int numeroMesasTerraza = 0;
    int numSituacion;
    for(int numeroMesa=20; numeroMesa>=1; numeroMesa--)
    {
        //Genera aleatoriamente la capacidad
        int capacidad = capacidades [rand() % 2];

        string situacion;
        //Genera aleatoriamente la situación
        numSituacion = rand() % 2;
        //Garantizamos que habrá un mínimo de 8 mesas en Terraza
        if(numeroMesasTerraza < 8 && numSituacion == 0)
        {
            situacion = situaciones[0];
            numeroMesasTerraza++;
        }
        else
        {
            situacion = situaciones [numSituacion];
        }
        Mesa* pmesa = new Mesa(numeroMesa,capacidad,situacion);
        pilaMesas.apilar(*pmesa);
    }
    cout << "Pila de mesas generada." << endl;
    //cout << "Numero mesas en terraza:" << numeroMesasTerraza << endl;
} //Opci�n 4

void Gestor::mostrarPilaMesas(Pila& pilaMesas)
{
    pilaMesas.mostrarPilaMesas();
} //Opci�n 5

void Gestor::vaciarPilaMesas(Pila& pila)
{
    if(pila.esVacia())
    {
        cout << "La pila de mesas est� vac�a."<<endl;
        return;
    }
    pila.vaciarPila();
    cout << "Pila de mesas vaciada."<<endl;
} //Opci�n 6


//void obtenerMesa?

void Gestor::simularCambioHora(Pila& pilaMesas, Lista& listaPedidos)
{
    cout << "Simulando cambio de hora..." << endl;

    NodoLista* aux = listaPedidos.getPrimero();
    int i = 0;

    while(i<4)
    {
        if(aux->pPedido->getFinalizado() == false)
        {
            aux->pPedido->setFinalizado(true);
            pilaMesas.apilar(*aux->pPedido->getMesaAsignada1());
            if(aux->pPedido->getMesaAsignada2()!=nullptr)
            {
                pilaMesas.apilar(*aux->pPedido->getMesaAsignada1());
            }
            aux->pPedido->restablecerMesasAsignadas();
            i++;
        }
        aux = aux->siguiente;
    }
    cout << "Se han marcado los cuatro siguientes pedidos como finalizados y se han liberado sus mesas." << endl;
}

void Gestor::procesarReserva(Reserva* pReserva, Cola& colaReservasPdtes,Pila& pilaMesas, Lista& listaPedidos, bool esReservaPdte)
{
    //Se buscan las mesas necesarias con la situaci�n deseada
    bool mesasDisponibles = false;

    int numerosMesa[2] = {0,0};
    int capacidadNumerosMesa[2] = {0,0};
    int numPersonas = pReserva->getNumPersonas();

    //Buscamos las mesas necesarias para cada numPersonas
    cout << "Procesando siguiente mesa disponible ---------" << endl;
    mesasDisponibles = pilaMesas.buscarMesa(pReserva,numPersonas,listaPedidos);
    cout << "TERMINADO ---- MESA siguiente reserva---------" << endl;

    //Si hay mesas disponiles
    if(mesasDisponibles)
    {
        if(!esReservaPdte) //Solo se suma las reservas de cReservas, no las de cReservasPdte
        {
            numReservasGestionadas++;
        }
        delete pReserva;
    }
    else
    {
        //Se a�ade la reserva a la cola de reservas pendientes
        colaReservasPdtes.encolar(*pReserva);
    }
}


void Gestor::simularGestionProximaReserva(Cola& colaReservas, Cola& colaReservasPdtes,Pila& pilaMesas, Lista& listaPedidos)
{
    //Comprueba que las cola no est�n vac�a y si se trata de una reserva pendiente en la �ltima
    //pasada de la simulaci�n.
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

    procesarReserva(pReserva,colaReservasPdtes,pilaMesas,listaPedidos,esReservaPdte);
    cout << "TERMINADO ----- Procesando siguiente reserva---------" << endl;

    mostrarDatosDespuesDeGestionarReserva(colaReservas,colaReservasPdtes,pilaMesas,listaPedidos);
    cout << "TERMINADO MOSTRAR DATOS ---------" << endl;

    //Por cada 2 reservas que salen de cola reservas se comprueba una de colas pendientes si la hay
    if(numReservasGestionadas>0 && numReservasGestionadas%2 == 0)
    {
        cout << "Procesando siguiente mesa disponible PENDIENTES ---------" << endl;
        if(colaReservasPdtes.esVacia())
        {
            cout << "No hay reservas que simular.";
            return;
        }
        else
        {
            pReserva = siguienteReserva(true,colaReservas,colaReservasPdtes);
            procesarReserva(pReserva,colaReservasPdtes,pilaMesas,listaPedidos,true);
            mostrarDatosDespuesDeGestionarReserva(colaReservas,colaReservasPdtes,pilaMesas,listaPedidos);
            cout << "TERMINADO MOSTRAR DATOS PENDIENTES---------" << endl;
        }

    }

    if(!esReservaPdte)
    {
        //Se comprueba si han terminado todas las reservas de una hora
        cout << "Comprobando es reserva pendiente..." << endl;
        if(comprobarCambioHora(horaActual,colaReservas))
        {
            simularCambioHora(pilaMesas,listaPedidos);
        }
    }

} //Opci�n 7

void Gestor::mostrarDatosDespuesDeGestionarReserva(Cola& colaReservas, Cola& colaReservasPdtes,Pila& pilaMesas, Lista& listaPedidos)
{
    //Mostramos por pantalla la cola de reservas, cola de reservas pendientes, pila de mesas y lista de pedidos
    cout << "-----------COLA DE RESERVAS----------------------" << endl;
    colaReservas.mostrarCola();
    cout << "-----------COLA DE RESERVAS PENDIENTES-----------" << endl;
    colaReservasPdtes.mostrarCola();
    cout << "-----------PILA DE MESAS DISPONIBLES-------------" << endl;
    pilaMesas.mostrarPilaMesas();
    cout << "-----------LISTA DE PEDIDOS----------------------" << endl;
    listaPedidos.mostrarDatosLista();
}

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

bool Gestor::comprobarCambioHora(string horaInicial,Cola& colaReservas)
{
    if(colaReservas.esVacia())
    {
        return false; //Por que seria true????
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
    //Comprueba si la cola est� vac�a
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
        procesarReserva(pReserva,colaReservasPdtes,pilaMesas,listaPedidos,false);

        //Por cada 2 reservas que salen de cola reservas se comprueba una de colas pendientes si la hay
        if(numReservasGestionadas>0 && numReservasGestionadas%2 == 0)
        {
            procesarReserva(pReserva,colaReservasPdtes,pilaMesas,listaPedidos,true);
        }

        //Se comprueba si ha habido cambio de mesa
        haHabidoCambioHora = comprobarCambioHora(horaActual,colaReservas);
    }
    //Al terminar simula el cambio de hora
    simularCambioHora(pilaMesas,listaPedidos);
}
//Opci�n 8


void Gestor::simularGestionReservasTotal(Cola& colaReservas, Cola& colaReservasPdtes,Pila& pilaMesas, Lista& listaPedidos)
{

} //Opci�n 9



void Gestor::Salir()
{
    cout << "Gracias por usar UltraReserva3000. Nos vemos pronto." << endl;
    //Otras cosas que realizar antes de salir:


} //Opci�n 0

