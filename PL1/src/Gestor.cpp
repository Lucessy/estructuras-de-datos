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

/**
*
*/
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
        }
        string hora = horas[turnoHora];

        Reserva* preserva = new Reserva(nombreCliente, hora, situacion, numeroPersonas, menu);
        colaReservas.encolar(*preserva);
    }
    cout << "Cola de reservas generada." << endl;
} //Opcio�n 1

/**
*
*/
void Gestor::mostrarColaReservas(Cola& colaReservas)
{
    colaReservas.mostrarCola();
} //Opci�n 2

/**
*
*/
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

/**
*
*/
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

/**
*
*/
void Gestor::mostrarPilaMesas(Pila& pilaMesas)
{
    pilaMesas.mostrarPilaMesas();
} //Opci�n 5

/**
*
*/
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

/**
*
*/
void Gestor::simularCambioHora(Pila& pilaMesas, Lista& listaPedidos)
{
    listaPedidos.completarSiguientesPedidos(pilaMesas);
}

/**
*
*/
void Gestor::procesarReserva(Reserva* pReserva, Cola& colaReservasPdtes,Cola& colaReservasNoGestionadas,Pila& pilaMesas, Lista& listaPedidos,bool esReservaPdt, bool esReservaPdtDelFinal)
{
    //Se guarda el número de personas de la reserva
    int numPersonas = pReserva->getNumPersonas();

    //Buscamos las mesas necesarias para cada numPersonas y se añaden a la lista de pedidos si las encuentra
    bool mesasDisponibles = false;
    Mesa** mesas = pilaMesas.buscarMesas(pReserva,numPersonas);
    if(mesas[0] != nullptr)
    {
        mesasDisponibles = true;
    }
    if(mesasDisponibles)
    {
        crearPedidos(mesas,pReserva,listaPedidos);
    }


    //Si hay mesas disponiles y no es una reserva pendiente se aumenta el contador de reservas gestionadas
    if(mesasDisponibles)
    {
        if(!esReservaPdt)
        {
            numReservasGestionadas++;
        }
        delete pReserva;
    }
    //Si no se encuentra mesa se añade a la cola correspondiente
    else if(!esReservaPdtDelFinal)
    {
        //Se añade la reserva a la cola de reservas pendientes
        colaReservasPdtes.encolar(*pReserva);
    }
    else
    {

        //Se añade a la cola de reservas no gestionadas
        colaReservasNoGestionadas.encolar(*pReserva);
    }
}

/**
* Simula la gestión de todas las próximas reservas de cola reservas a la misma hora. No simula reservas pendientes.
*/
void Gestor::simularGestionProximaReserva(Cola& colaReservas, Cola& colaReservasPdtes, Cola& colaReservasNoGestionadas,Pila& pilaMesas, Lista& listaPedidos)
{
    //Comprueba que las cola no están vacías y si se trata de una reserva pendiente
    //en la última pasada de la simulación por la cola de reservas pendientes.
    bool esReservaPdtDelFinal = false;
    if(colaReservas.esVacia())
    {
        if(colaReservasPdtes.esVacia())
        {
            cout << "No hay reservas que simular."<<endl;
            return;
        }
        esReservaPdtDelFinal = true;
    }

    //Se almacena la siguiente reserva de colaReservas, y si no quedan, de colaReservasPdtes
    //Se saca la reserva de la cola
    Reserva* pReserva = siguienteReserva(esReservaPdtDelFinal,colaReservas,colaReservasPdtes);

    //Se guarda la hora actual para comprobar el cambio de hora
    string horaActual = pReserva->getHoraReserva();

    //Se procesa la siguiente reserva
    cout << "-------------Procesando reserva-------------" <<endl;
    procesarReserva(pReserva,colaReservasPdtes,colaReservasNoGestionadas,pilaMesas,listaPedidos,esReservaPdtDelFinal,esReservaPdtDelFinal);

    //Si pertenece a colaReservas se comprueba el cambio de hora
    if(!esReservaPdtDelFinal)
    {
        //Se comprueba si han terminado todas las reservas de una hora
        cout << " Cambio de hora: " << (comprobarCambioHora(horaActual,colaReservas) ? "Si":"No") << endl;
        if(comprobarCambioHora(horaActual,colaReservas))
        {
            cout << "Simulando el cambio de hora..." << endl;
            simularCambioHora(pilaMesas,listaPedidos);
            cout << "Cambio de hora simulado." << endl;
        }
    }

    //Por cada 2 reservas que salen de cola reservas se comprueba una de colas pendientes si la hay
    if(numReservasGestionadas>0 && numReservasGestionadas%2 == 0)
    {
        if(!colaReservasPdtes.esVacia())
        {
            //Se guarda la próxima reserva pendiente, se procesa y se muestran sus datos
            cout << "--------------Procesando reserva pendiente----------" << endl;
            pReserva = siguienteReserva(true,colaReservas,colaReservasPdtes);
            procesarReserva(pReserva,colaReservasPdtes,colaReservasNoGestionadas,pilaMesas,listaPedidos,true,false);
        }
    }
    cout << "SIMULACION DE LAS GESTIONES TERMINADA" << endl;
} //Opci�n 7

/**
*
*/
void Gestor::mostrarDatos(Cola& colaReservas, Cola& colaReservasPdtes,Cola& colaReservasNoGestionadas,Pila& pilaMesas, Lista& listaPedidos)
{
    //Mostramos por pantalla la cola de reservas, cola de reservas pendientes, pila de mesas y lista de pedidos
    cout << "-----------PILA DE MESAS DISPONIBLES-------------" << endl;
    pilaMesas.mostrarPilaMesas();
    cout << "-----------COLA DE RESERVAS----------------------" << endl;
    colaReservas.mostrarCola();
    cout << "-----------COLA DE RESERVAS PENDIENTES-----------" << endl;
    colaReservasPdtes.mostrarCola();
    cout << "-----------COLA DE RESERVAS CON GESTION FALLIDA--" << endl;
    colaReservasNoGestionadas.mostrarCola();
    cout << "-----------LISTA DE PEDIDOS----------------------" << endl;
    listaPedidos.mostrarDatosLista();
    cout << "-----------FIN DE DATOS----------------------" << endl;
}

/**
*
*/
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

/**
*
*/
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

/**
*
*/
void Gestor::crearPedidos(Mesa** mesas, Reserva* pReserva,Lista& listaPedidos)
{
    Mesa* mesasAsignadas[2];
    mesasAsignadas[0] = mesas[0];
    mesasAsignadas[1] = mesas[1];
    Pedido* pPedido = new Pedido(mesasAsignadas,pReserva->getNombreCliente(),pReserva->getNumPersonas(),pReserva->getPreferenciaMenu(),pReserva->getSituacionMesa(),false);
    listaPedidos.extenderListaPorDerecha(*pPedido);
}


/**
*
*/
void Gestor::simularGestionReservasProximaHora(Cola& colaReservas, Cola& colaReservasPdtes,Cola& colaReservasNoGestionadas,Pila& pilaMesas, Lista& listaPedidos)
{
    //Comprueba si la cola est� vac�a
    if(colaReservas.esVacia())
    {
        cout << "No quedan reservas en la cola de reservas." << endl;
        return;
    }
    //Se guarda la hora actual para comprobar el cambio de hora
    string horaActual = colaReservas.inicio()->getHoraReserva();

    //Procesa reservas mientras no haya cambio de hora
    bool haHabidoCambioHora = false;
    while(!haHabidoCambioHora)
    {
        //Se almacena la siguiente reserva de colaReservas, y si no quedan, de colaReservasPdtes
        //Se saca la reserva de la cola
        Reserva* pReserva = siguienteReserva(false,colaReservas,colaReservasPdtes);

        //Se procesa la siguiente reserva
        cout << "----------Procesando reserva------------" <<endl;
        procesarReserva(pReserva,colaReservasPdtes,colaReservasNoGestionadas,pilaMesas,listaPedidos,false,false);

        //Por cada 2 reservas que salen de cola reservas se comprueba una de colas pendientes si la hay
        if(numReservasGestionadas>0 && numReservasGestionadas%2 == 0)
        {
            if(!colaReservasPdtes.esVacia())
            {
                //Se guarda la próxima reserva pendiente, se procesa y se muestran sus datos
                cout << "---------Procesando reserva pendiente--------------" << endl;
                pReserva = siguienteReserva(true,colaReservas,colaReservasPdtes);
                procesarReserva(pReserva,colaReservasPdtes,colaReservasNoGestionadas,pilaMesas,listaPedidos,true,false);
            }
        }
        //Se comprueba si ha habido cambio de hora
        haHabidoCambioHora = comprobarCambioHora(horaActual,colaReservas);
    }
    //Al terminar simula el cambio de hora
    cout << "Simulando el cambio de hora..." << endl;
    simularCambioHora(pilaMesas,listaPedidos);
    cout << "Cambio de hora simulado." << endl;
}
//Opci�n 8

/**
*
*/
void Gestor::simularGestionReservasTotal(Cola& colaReservas, Cola& colaReservasPdtes,Cola& colaReservasNoGestionadas,Pila& pilaMesas, Lista& listaPedidos)
{
    int maxCounter = 150;
    while((!colaReservas.esVacia() || !colaReservasPdtes.esVacia()) && maxCounter > 0){
        simularGestionProximaReserva(colaReservas,colaReservasPdtes,colaReservasNoGestionadas,pilaMesas,listaPedidos);
        maxCounter--;
    }

} //Opci�n 9



void Gestor::Salir()
{
    cout << "Gracias por usar UltraReserva3000. Nos vemos pronto." << endl;
    //Otras cosas que realizar antes de salir:


} //Opci�n 0

