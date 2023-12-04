#include "Gestor.h"
#include "Cola.h"
#include "Reserva.h"
#include "Mesa.h"
#include "Pila.h"
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <random>
#include <cstdlib>

using namespace std;


Gestor::Gestor()
{

}

Gestor::~Gestor()
{
    //dtor
}

/**
* Genera una cola de reservas aleatoria del tamaño limite dado (con nombres del señor de los anillos)
*/
void Gestor::generarColaReservas(Cola& colaReservas)
{
    //Si la cola ya tiene reservas se vacia primero
    if(colaReservas.esVacia() == false)
    {
        cout << "Generando nueva cola de reservas. Vaciando la cola anterior." << endl;
        vaciarColaReservas(colaReservas);
    }

    // Generar y mostrar el número aleatorio
    int numeroAleatorio = rand() % (50 - 12 + 1) + 12;
    cout << "Generando:" << numeroAleatorio << " reservas aleatorias..." << endl;

    int turnoHora = 0;

    //Datos
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
        "Eomer", "Theodred", "Arwen", "Bard", "Thrain",
        "Dis", "Smaug", "Thranduil", "Celeborn", "Glorfindel",
        "Radagast", "Beorn", "Gwaihir", "Tom Bombadil", "Goldberry", //45
        "Treebeard", "Quickbeam", "Fangorn", "Barliman", "Butterbur",
        "Shadowfax", "Windfola", "Hasufel", "Arod", "Shadowfax",
        "Billy", "Bruce willis", "Gengis-khan", "Grishnákh","Sherlock" //60
    };

    //Generación de las reservas
    for(int i = 0; i < 12; i++)
    {
        string nombreCliente = nombresPosibles[rand() % 60];
        string menu = menus[rand() % 3];
        string situacion = situaciones [rand() % 2];
        int numeroPersonas = rand() % 8 + 1;

        if(i < 4)
        {
            turnoHora = 0;
        }
        else if(i < 8)
        {
            turnoHora = 1;
        }
        else
        {
            turnoHora = 2;
        }

        string hora = horas[turnoHora];

        //Crear y añadir nueva reserva
        Reserva* preserva = new Reserva(nombreCliente, hora, situacion, numeroPersonas, menu);
        colaReservas.encolar(*preserva);
    }
    for(int j = 12; j < numeroAleatorio; j++)
    {
        string nombreCliente = nombresPosibles[rand() % 60];
        string menu = menus[rand() % 3];
        string situacion = situaciones [rand() % 2];
        int numeroPersonas = rand() % 8 + 1;
        string hora = horas[rand() % 3];

        //Crear y añadir nueva reserva
        Reserva* preserva = new Reserva(nombreCliente, hora, situacion, numeroPersonas, menu);
        colaReservas.encolar(*preserva);
    }
    cout << "Cola de reservas generada." << endl;
} //Opcio�n 1

/**
* Muestra por pantalla la cola de reservas
*/
void Gestor::mostrarColaReservas(Cola& colaReservas)
{
    colaReservas.mostrarCola();
} //Opci�n 2

/**
* Vacia la cola de Reservas
*/
void Gestor::vaciarColaReservas(Cola& colaReservas)
{
    if(colaReservas.esVacia())
    {
        cout << "La cola de reservas ya está vacía." << endl;
        return;
    }
    colaReservas.vaciarCola();
    cout << "Cola de reservas vaciada." << endl;
} //Opci�n 3

/**
*  Genera una pila de 20 mesas con datos aleatorios (al menos 8 en terraza)
*/
void Gestor::generarPilaMesas(Pila& pilaMesas)
{
    //Comprueba que la simulación no ha comenzado aún para evitar duplicamiento de mesas
    if(seHaComenzadoLaSimulacion)
    {
        cout << "No se puede alterar la pila de mesas una vez se ha empezado la simulación." << endl;
        return;
    }
    //Si la pila no está vacia se vacía primero
    if(!pilaMesas.esVacia())
    {
        cout << "Generando nueva pila de mesas. Vaciando la pila anterior." << endl;
        vaciarPilaMesas(pilaMesas);
    }
    //Inicialización de variables
    string situaciones[2] = {"Terraza","Interior"};
    int capacidades[2] = {2,4};
    int numeroMesasTerraza = 0;
    int numSituacion;
    //Generación de mesas
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
        //Se crea la nueva mesa y se apila
        Mesa* pmesa = new Mesa(numeroMesa,capacidad,situacion);
        pilaMesas.apilar(*pmesa);
    }
    cout << "Pila de mesas generada." << endl;
    //cout << "Numero mesas en terraza:" << numeroMesasTerraza << endl;
} //Opci�n 4

/**
* Muestra por pantalla la pila de mesas
*/
void Gestor::mostrarPilaMesas(Pila& pilaMesas)
{
    pilaMesas.mostrarPilaMesas();
} //Opci�n 5

/**
* Vacia la pila de mesas
*/
void Gestor::vaciarPilaMesas(Pila& pila)
{
    if(pila.esVacia())
    {
        cout << "La pila de mesas está vacía."<<endl;
        return;
    }
    pila.vaciarPila();
    cout << "Pila de mesas vaciada."<<endl;
} //Opci�n 6

/**
* Completa los siguientes cuatro pedidos después de cada cambio de hora y libera las mesas de los pedidos reapilandolas en la pila de mesas
*/
void Gestor::simularCambioHora(Pila& pilaMesas, Lista& listaPedidos)
{
    listaPedidos.completarSiguientesPedidos(pilaMesas,abbPedidos);
}

/**
* Procesa una reserva dada (ya sea pdte o común)
*
* Procesa la reserva dada, buscando las mesas disponibles correspondientes, saca esas mesas de la pila si las hay
* y se crea un pedido con los datos de la reserva y las mesas asignadas. Si no se consigue gestionar se encola en
* la cola de reservas pendientes a menos que sea una reserva la última pasada de la simulación por la cola de reservas
* pendientes, en cuyo caso se añade a la cola de reservas no gestionadas (o de gestión fallida).
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
* Simula la gestión completa de la siguiente reserva
*
* Simula la gestión completa de la siguiente reserva (ya sea de la cola de reservas, o si la cola de reservas está
* vacía, de la cola de reservas pendientes), procesandola y atendiendo a la simulación de reservas pendientes
* cada 2 reservas comunes y simulando el cambio de hora si es necesario.
*/
void Gestor::simularGestionProximaReserva(Cola& colaReservas, Cola& colaReservasPdtes, Cola& colaReservasNoGestionadas,Pila& pilaMesas, Lista& listaPedidos)
{
    seHaComenzadoLaSimulacion = true;
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
    cout << "SIMULACION DE LAS GESTION DE LA PROXIMA RESERVA TERMINADA" << endl;
} //Opci�n 7

/**
* Muestra los datos por pantalla de la cola de reservas, cola de reservas pendientes, cola de reservas con gestión fallida, pila de mesas y lista de pedidos
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
*   Devuelve la siguiente reserva de la cola reservas, o si está vacía, de la cola de reservas pendientes
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
* Comprueba si se ha producido un cambio de hora, entre la hora inicial dada y el primer elemento de la cola de reservas dada
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
* Crear y añade un pedido para una reserva con mesa/s asignadas, dadas la reserva, las mesas y la lista de pedidos donde añadirlo
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
* Simula la gestión completa de todas las próximas reservas de cola reservas a la misma hora. Aunque gestiona una reserva pdte cada 2 comunes,
* no gestiona las reservas pendientes de la última pasada de la simulación, cuando ya se han acabado las reservas de la cola de reservas.
*/
void Gestor::simularGestionReservasProximaHora(Cola& colaReservas, Cola& colaReservasPdtes,Cola& colaReservasNoGestionadas,Pila& pilaMesas, Lista& listaPedidos)
{
    seHaComenzadoLaSimulacion = true;
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
}//Opci�n 8

/**
* Simula la gestión completa de todas las reservas de colaReservas y al acabarse estas, de colaReservasPdtes.
* Simula el cambio de hora cuando es necesario y gestiona una reserva pdte cada 2 comunes.
*/
void Gestor::simularGestionReservasTotal(Cola& colaReservas, Cola& colaReservasPdtes,Cola& colaReservasNoGestionadas,Pila& pilaMesas, Lista& listaPedidos)
{
    seHaComenzadoLaSimulacion = true;
    int maxCounter = 150;
    while((!colaReservas.esVacia() || !colaReservasPdtes.esVacia()) && maxCounter > 0)
    {
        simularGestionProximaReserva(colaReservas,colaReservasPdtes,colaReservasNoGestionadas,pilaMesas,listaPedidos);
        maxCounter--;
    }

} //Opci�n 9


/**
* Muestra el mensaje de salida. Para funcionar de la forma esperada debe la última función llamada antes de finalizar el programa.
*/
void Gestor::Salir()
{
    cout << "Gracias por usar UltraReserva3000. Nos vemos pronto." << endl;
    //Otras cosas que realizar antes de salir:


} //Opci�n 0

