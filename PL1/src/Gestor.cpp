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

/**
* Constructor donde se inicializan las variables
*/
Gestor::Gestor()
{

}

/**
* Destructor vacío
*/
Gestor::~Gestor()
{
    //dtor
}

/**
* Genera una cola de reservas aleatoria del tamaño limite dado (con nombres del señor de los anillos)
*/
void Gestor::generarColaReservas()
{
    colaReservas.generarReservas();
}

/**
* Muestra por pantalla la cola de reservas
*/
void Gestor::mostrarColaReservas()
{
    cout << "-----------COLA DE RESERVAS----------------------" << endl;
    colaReservas.mostrarCola();
} //Opci�n 2

/**
* Vacia la cola de Reservas
*/
void Gestor::vaciarColaReservas()
{
    colaReservas.vaciarCola();
} //Opci�n 3

/**
*  Genera una pila de 20 mesas con datos aleatorios (al menos 8 en terraza)
*/
void Gestor::generarPilaMesas()
{
    pilaMesas.generarMesas(seHaComenzadoLaSimulacion);
} //Opci�n 4

/**
* Muestra por pantalla la pila de mesas
*/
void Gestor::mostrarPilaMesas()
{
    cout << "-----------PILA DE MESAS-------------------------" << endl;
    pilaMesas.mostrarPilaMesas();
} //Opción 5

/**
* Vacia la pila de mesas
*/
void Gestor::vaciarPilaMesas()
{
    pilaMesas.vaciarPila();
} //Opci�n 6

/**
* Muestra por pantalla el arbol binario de datos
**/
void Gestor::mostrarAbbPedidos()
{
    cout << "-------------ABB DE PEDIDOS----------------------" << endl;
    abbPedidos.verEnOrden();
}

/**
* Simula el cambio de hora sacando la mitad de los pedidos de cada categoría de la lista de pedidos e insertándolos en el árbol de pedidos
*/
void Gestor::simularCambioHora()
{
    Lista pedidosFinalizados = listaPedidos.sacarSiguientesPedidos(pilaMesas);
    int longitud = pedidosFinalizados.getLongitud();
    for(int j = 0; j < longitud; j++)
    {
        pedidosFinalizados.elemInicial().setFinalizado(true);
        abbPedidos.insertar(pedidosFinalizados.elemInicial().getNombreCliente(), &(pedidosFinalizados.elemInicial()));
        pedidosFinalizados.eliminarPrimero();
    }
}

/**
* Procesa una reserva dada (ya sea pdte o común) y devuelve el pedido creado si consigue encontrar mesas.
*
* Procesa la reserva dada, buscando las mesas disponibles correspondientes, saca esas mesas de la pila si las hay
* y se crea un pedido con los datos de la reserva y las mesas asignadas. Si no se consigue gestionar se encola en
* la cola de reservas pendientes a menos que sea una reserva la última pasada de la simulación por la cola de reservas
* pendientes, en cuyo caso se añade a la cola de reservas no gestionadas (o de gestión fallida).
* También permite procesar reservas fuera del sistema de colas con reinsertarEnCola puesto a false.
*/
Pedido* Gestor::procesarReserva(Reserva* pReserva,bool esReservaPdt, bool esReservaPdtDelFinal, bool reinsertarEnCola)
{
    //Se guarda el número de personas de la reserva
    int numPersonas = pReserva->getNumPersonas();

    //Se inicializa el pedido a crear
    Pedido* pPedido = nullptr;

    //Buscamos las mesas necesarias para cada numPersonas y se añaden a la lista de pedidos si las encuentra
    bool mesasDisponibles = false;
    Mesa** mesas = pilaMesas.buscarMesas(pReserva,numPersonas);
    if(mesas[0] != nullptr)
    {
        mesasDisponibles = true;
    }


    if(mesasDisponibles)
    {
        //Se crea el pedido con esas mesas
        pPedido = crearPedidos(mesas,pReserva);
        //Si no es necesario reinsertarla en la cola se retorna el pedido creado. Especificamente se usa para crear pedidos independientes al sistema de colas, buscando las mesas.
        if(!reinsertarEnCola)
        {
            return pPedido;
        }
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
    return pPedido;
}

/**
* Simula la gestión completa de la siguiente reserva
*
* Simula la gestión completa de la siguiente reserva (ya sea de la cola de reservas, o si la cola de reservas está
* vacía, de la cola de reservas pendientes), procesandola y atendiendo a la simulación de reservas pendientes
* cada 2 reservas comunes y simulando el cambio de hora si es necesario.
*/
void Gestor::simularGestionProximaReserva()
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
    Reserva* pReserva = siguienteReserva(esReservaPdtDelFinal);

    //Se guarda la hora actual para comprobar el cambio de hora
    string horaActual = pReserva->getHoraReserva();

    //Se procesa la siguiente reserva
    Pedido* pPedido = procesarReserva(pReserva,esReservaPdtDelFinal,esReservaPdtDelFinal,true);
    if (pPedido != nullptr)
    {
        insertarPedidoEnLista(pPedido);
    }

    //Si pertenece a colaReservas se comprueba el cambio de hora
    if(!esReservaPdtDelFinal)
    {
        //Se comprueba si han terminado todas las reservas de una hora
        if(comprobarCambioHora(horaActual))
        {
            simularCambioHora();
        }
    }

    //Por cada 2 reservas que salen de cola reservas se comprueba una de colas pendientes si la hay
    if(numReservasGestionadas>0 && numReservasGestionadas%2 == 0)
    {
        if(!colaReservasPdtes.esVacia())
        {
            //Se guarda la próxima reserva pendiente, se procesa y se muestran sus datos
            pReserva = siguienteReserva(true);
            procesarReserva(pReserva,true,false,true);
        }
    }
} //Opci�n 7

/**
* Muestra los datos por pantalla de la cola de reservas, cola de reservas pendientes, cola de reservas con gestión fallida, pila de mesas y lista de pedidos
*/
void Gestor::mostrarDatos()
{
    //Mostramos por pantalla la cola de reservas, cola de reservas pendientes, pila de mesas y lista de pedidos
    cout << "-----------PILA DE MESAS DISPONIBLES-------------" << endl;
    pilaMesas.mostrarPilaMesas();
    cout << "-----------COLA DE RESERVAS----------------------" << endl;
    colaReservas.mostrarCola();
    cout << "-----------COLA DE RESERVAS PENDIENTES-----------" << endl;
    colaReservasPdtes.mostrarCola();
    cout << "-----------LISTA DE PEDIDOS----------------------" << endl;
    listaPedidos.mostrarDatosLista();
    cout << "--------COLA DE RESERVAS CON GESTION FALLIDA-----" << endl;
    colaReservasNoGestionadas.mostrarCola();
}

/**
*   Devuelve la siguiente reserva de la cola reservas, o si está vacía, de la cola de reservas pendientes
*/
Reserva* Gestor::siguienteReserva(bool esReservaPdte)
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
bool Gestor::comprobarCambioHora(string horaInicial)
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
* Crear y devuelve un pedido para una reserva con mesa/s asignadas, dadas la reserva, las mesas y la lista de pedidos donde añadirlo
*/
Pedido* Gestor::crearPedidos(Mesa** mesas, Reserva* pReserva)
{
    Mesa* mesasAsignadas[2];
    mesasAsignadas[0] = mesas[0];
    mesasAsignadas[1] = mesas[1];
    Pedido* pPedido = new Pedido(mesasAsignadas,pReserva->getNombreCliente(),pReserva->getNumPersonas(),pReserva->getPreferenciaMenu(),pReserva->getSituacionMesa(),false);
    return pPedido;
}


/**
* Simula la gestión completa de todas las próximas reservas de cola reservas a la misma hora. Aunque gestiona una reserva pdte cada 2 comunes,
* no gestiona las reservas pendientes de la última pasada de la simulación, cuando ya se han acabado las reservas de la cola de reservas
*/
void Gestor::simularGestionReservasProximaHora()
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
        Reserva* pReserva = siguienteReserva(false);

        //Se procesa la siguiente reserva
        Pedido* pPedido = procesarReserva(pReserva,false,false,true);
        if (pPedido != nullptr)
        {
            insertarPedidoEnLista(pPedido);
        }

        //Por cada 2 reservas que salen de cola reservas se comprueba una de colas pendientes si la hay
        if(numReservasGestionadas>0 && numReservasGestionadas%2 == 0)
        {
            if(!colaReservasPdtes.esVacia())
            {
                //Se guarda la próxima reserva pendiente, se procesa y se muestran sus datos
                pReserva = siguienteReserva(true);
                procesarReserva(pReserva,true,false,true);
            }
        }
        //Se comprueba si ha habido cambio de hora
        haHabidoCambioHora = comprobarCambioHora(horaActual);
    }
    //Al terminar simula el cambio de hora
    simularCambioHora();
}//Opci�n 8

/**
* Simula la gestión completa de todas las reservas de colaReservas y al acabarse estas, de colaReservasPdtes.
* Simula el cambio de hora cuando es necesario y gestiona una reserva pdte cada 2 comunes.
* Al finalizar la simulación, inserta en el ABB de pedidos los pedidos restantes hasta que la lista se quede vacía.
*/
void Gestor::simularGestionReservasTotal()
{
    seHaComenzadoLaSimulacion = true;
    while((!colaReservas.esVacia() || !colaReservasPdtes.esVacia()))
    {
        simularGestionProximaReserva();
    }
    while(!listaPedidos.esVacia())
    {
        simularCambioHora();
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


/**
* Inserta el pedido dado en la lista de pedidos.
*/
void Gestor::insertarPedidoEnLista(Pedido* pedido)
{
    listaPedidos.extenderListaPorCategoria(*pedido);
}

/**
* Muestra los datos de la lista de pedidos. No muestra mensaje inicial solo muestra los datos.
*/
void Gestor::mostrarListaPedidos()
{
    cout << "-----------LISTA DE PEDIDOS----------------------" << endl;
    listaPedidos.mostrarDatosLista();
}

/**
* Muestra los datos de la cola de reservas pendientes. No muestra mensaje inicial solo muestra los datos.
*/
void Gestor::mostrarColaReservasPendientes()
{
    cout << "-----------COLA DE RESERVAS PENDIENTES-----------" << endl;
    colaReservasPdtes.mostrarCola();
}

/**
* Inserta un pedido dado por un puntero a pedido en su posición correspondiente en el ABB.
*/
void Gestor::insertarPedidoEnABB(Pedido* pedido)
{
    pedido->setFinalizado(true);
    if(pedido->getMesaAsignada1() != nullptr)
    {
        pilaMesas.apilar(*(pedido->getMesaAsignada1()));
    }
    if(pedido->getMesaAsignada2() != nullptr)
    {
        pilaMesas.apilar(*(pedido->getMesaAsignada2()));
    }
    abbPedidos.insertar(pedido->getNombreCliente(),pedido);
}

/**
* Muestra los nombres y solo los nombres de todos los clientes que han realizado al menos un pedido, ordenados alfabeticamente.
*/
void Gestor::mostrarNombresClientesAlfabeticamente()
{
    cout << "-------------ABB DE PEDIDOS----------------------" << endl;
    abbPedidos.verEnOrden(true);
}

/**
* Muestra todos los pedidos realizados por un cliente dado su nombre.
*/
void Gestor::mostrarPedidosDeCliente(string nombreCliente)
{
    Lista* listaPedidos = abbPedidos.buscarListaPedidosPorNombre(nombreCliente);
    if (listaPedidos == nullptr)
    {
        cout << "No se ha gestionado ningún pedido del cliente: " << nombreCliente << endl;
    }
    else
    {
        cout << "Pedidos gestionados para el cliente: " << nombreCliente << endl << endl;
        listaPedidos->mostrarDatosLista();
    }
}

/**
* Muestra la cantidad de pedidos gestionados por cada categoría: MenuVegano, SinGluten, etc. No muestra mensaje inicial, solos los datos.
*/
void Gestor::mostrarCantidadPedidoPorCategoria()
{
    abbPedidos.sumarCategorias();
}

/**
* Muestra los datos de los pedidos gestionados de los clientes que han realizado pedidos de categoría MenuVegano
*/
void Gestor::mostrarClientesConMenuVegano()
{
    cout << "-------------ABB DE PEDIDOS----------------------" << endl;
    abbPedidos.verEnOrden(false,true);
}





