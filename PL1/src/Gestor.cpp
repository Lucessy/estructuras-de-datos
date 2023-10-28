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


void Gestor::simularGestionReservaPendiente(Cola& colaReservas, Cola& colaReservasPdtes,Pila& pilaMesas, Lista& listaPedidos)
{

}


//void obtenerMesa?

void Gestor::simularCambioHora(Pila& pilaMesas, Lista& listaPedidos)
{
    listaPedidos.completarSiguientes4Pedidos();
    cout << "Se han marcado los cuatro siguientes pedidos como finalizados y se han liberado sus mesas." << endl;
}

bool Gestor::buscarMesa(Pila& pilaMesas, Pila& pilaAux, Reserva* pReserva, int capacidad)
{
    bool mesaEncontrada = false;

    while (!mesaEncontrada && !pilaMesas.esVacia())
    {
        Mesa cima = pilaMesas.getCima();
        if (capacidad == cima.getCapacidad() && pReserva->getSituacionMesa() == cima.getSituacionMesa())
        {
            pReserva->asignarMesa(&cima);
            pilaMesas.desapilar();
            mesaEncontrada = true;
        }
        else
        {
            pilaAux.apilar(cima);
            pilaMesas.desapilar();
        }
    }

    while (!pilaAux.esVacia())
    {
        pilaMesas.apilar(pilaAux.getCima());
        pilaAux.desapilar();
    }

    return mesaEncontrada;
}

bool Gestor::buscarDosMesas(Pila& pilaMesas, Pila& pilaAux, Reserva* pReserva, int capacidad)
{
    bool primeraMesaEncontrada = false;
    bool segundaMesaEncontrada = false;
    // Crear una copia de las pilas: pilaMesas
    Pila pilaCopia;
    Pila pilaNoModificada;
    while (!pilaMesas.esVacia())
    {
        Mesa cima = pilaMesas.getCima();
        pilaAux.apilar(cima);
        pilaNoModificada.apilar(cima);  // Mantén un registro de la pila original
        pilaMesas.desapilar();
    }
    while(!pilaAux.esVacia())
    {
        Mesa cima = pilaMesas.getCima();
        pilaCopia.apilar(cima);  // Pila que se va a modificar
        pilaAux.desapilar();
    }

    while (!pilaCopia.esVacia() && (!primeraMesaEncontrada || !segundaMesaEncontrada))
    {
        Mesa cima = pilaCopia.getCima();
        if (capacidad == cima.getCapacidad() && pReserva->getSituacionMesa() == cima.getSituacionMesa())
        {
            if (!primeraMesaEncontrada)
            {
                pReserva->asignarMesa(&cima);
                primeraMesaEncontrada = true;
            }
            else if (!segundaMesaEncontrada)
            {
                pReserva->asignarMesa(&cima);
                segundaMesaEncontrada = true;
            }
        }
        else
        {
            pilaAux.apilar(cima);
        }
        pilaCopia.desapilar();
    }

    // Si encontraste dos mesas, está todo bien
    if (primeraMesaEncontrada && segundaMesaEncontrada)
    {
        // Devuelve las mesas que no se asignaron a una reserva a la pila original
        while (!pilaAux.esVacia())
        {
            pilaMesas.apilar(pilaAux.getCima());
            pilaAux.desapilar();
        }
        return true;
    }
    else
    {
        // Si no se encontraron suficientes mesas, devuelve false y restaura la pila original
        while (!pilaNoModificada.esVacia())
        {
            pilaMesas.apilar(pilaNoModificada.getCima());
            pilaNoModificada.desapilar();
            pReserva->mesaAsignada1=nullptr;
            pReserva->mesaAsignada2=nullptr;
        }

        return false;
    }
}

void Gestor::procesarReserva(Reserva* pReserva, Cola& colaReservasPdtes,Pila& pilaMesas, Lista& listaPedidos,bool insertarEnReservasPdtes)
{
    //Pila auxiliar para almacenar las mesas no asignadas
    Pila pilaAux;

    //Se buscan las mesas necesarias con la situaci�n deseada
    bool mesasDisponibles = false;

    //int numerosMesa[2] = {0,0};
    int numPersonas = pReserva->getNumPersonas();

    //Buscamos las mesas necesarias para cada numPersonas
    //Si solo se necesita una mesa
    if (numPersonas <= 2)
    {
        // Buscar mesa de capacidad 2
        mesasDisponibles = buscarMesa(pilaMesas, pilaAux, pReserva, 2);

        if (!mesasDisponibles)
        {
            // Si no se encontró mesa de capacidad 2, buscar mesa de capacidad 4
            mesasDisponibles = buscarMesa(pilaMesas, pilaAux, pReserva, 4);
        }
    }
    else if (numPersonas <= 4)
    {
        // Buscar mesa de capacidad 4
        mesasDisponibles = buscarMesa(pilaMesas, pilaAux, pReserva, 4);
    }
    /*else if (numPersonas <= 6)
    {
        // Buscar mesa de capacidad 6 (Capcidad 4 y otra capacidad 2)
        mesasDisponibles = buscarDosMesas(pilaMesas, pilaAux, pReserva, 6);
        if (!mesasDisponibles)
        {
            // Si no se encontró mesa de capacidad 4 y capacidad 2, buscar dos mesas de capacidad 4
            mesasDisponibles = buscarDosMesas(pilaMesas, pilaAux, pReserva, 4);
        }
    }*/
    else
    {
        // Buscar mesa de capacidad 8 - 5 (Dos de capacidad 4)
        mesasDisponibles = buscarDosMesas(pilaMesas, pilaAux, pReserva, 4);
    }

    //Si hay mesas disponiles
    if(mesasDisponibles)
    {
        //Se genera el pedido y se a�ade a la lista de pedidos
        Pedido* pedido = new Pedido(numerosMesa,pReserva->getNombreCliente(),pReserva->getNumPersonas(),pReserva->getPreferenciaMenu(),pReserva->getSituacionMesa(),false);
        listaPedidos.extenderListaPorDerecha(*pedido);
        numReservasGestionadas++;
        delete pReserva;
    }
    else if (insertarEnReservasPdtes)
    {
        //Se a�ade la reserva a la cola de reservas pendientes
        colaReservasPdtes.encolar(*pReserva);
    }
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

} //Opci�n 7

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
//Opci�n 8


void Gestor::simularGestionReservasTotal(Cola& colaReservas, Cola& colaReservasPdtes,Pila& pilaMesas, Lista& listaPedidos)
{

} //Opci�n 9



void Gestor::Salir()
{
    cout << "Gracias por usar UltraReserva3000. Nos vemos pronto." << endl;
    //Otras cosas que realizar antes de salir:


} //Opci�n 0

