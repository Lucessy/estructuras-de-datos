#include "Cola.h"
#include "NodoCola.h"
#include <iostream>
#include "Reserva.h"
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

using namespace std;

Cola::Cola()
{
    //ctor.
    primero=NULL;
    ultimo=NULL;
}

Cola::~Cola()
{
    //dtor.
}

void Cola::encolar(Reserva& reserva)
{
    NodoCola *nuevo_nodo = new NodoCola(reserva);
    if(esVacia())
    {
        primero=nuevo_nodo;
        ultimo=nuevo_nodo;
    }
    else
    {
        ultimo->siguiente = nuevo_nodo;
        ultimo=nuevo_nodo;
    }
}

void Cola::desencolar()
{
    if(!esVacia())
    {
        NodoCola *aux = primero;

        if((primero==ultimo)&&(primero->siguiente == NULL))
        {
            primero=NULL;
            ultimo=NULL;
            aux->siguiente=NULL;
            delete(aux);
        }
        else
        {
            primero = primero->siguiente;
            aux->siguiente=NULL;
            delete(aux);
        }
    }
}

/**
* Genera una cola de reservas aleatoria del tamaño limite dado (con nombres del señor de los anillos)
*/
void Cola::generarReservas()
{
    //Si la cola ya tiene reservas se vacia primero
    if(esVacia() == false)
    {
        cout << "Generando nueva cola de reservas. Vaciando la cola anterior." << endl;
        vaciarCola();
    }

    // Generar y mostrar el número aleatorio
    int numeroAleatorio = rand() % (50 - 12 + 1) + 12;
    cout << "Generando:" << numeroAleatorio << " reservas aleatorias..." << endl;

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

    //Inicialización de variables
    srand(time(0));
    int turnoHora = -1;
    int numReservasPorTurno = (int)numeroAleatorio/3;

    //Generación de las reservas
    for(int i = 0; i < numeroAleatorio; i++)
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
        //Crear y añadir nueva reserva
        Reserva* preserva = new Reserva(nombreCliente, hora, situacion, numeroPersonas, menu);
        encolar(*preserva);
    }
}

void Cola::vaciarCola()
{
    if(esVacia())
    {
        cout << "La cola de reservas ya está vacía." << endl;
        return;
    }
    while(primero != NULL)
    {
        desencolar();
    }
    cout << "Cola de reservas vaciada." << endl;
}

Reserva* Cola::inicio()
{
    if(!esVacia())
    {
        return (primero->preserva);
    }
}

Reserva* Cola::fin()
{
    if(!esVacia())
    {
        return (ultimo->preserva);
    }
}

bool Cola::esVacia()
{
    return((primero==NULL)&&(ultimo==NULL));
}

void Cola::mostrarCola()
{
    NodoCola *aux = primero;
    if(esVacia())
    {
        cout << "Cola vacia" << endl;
    }
    else
    {
        cout << "Datos de la cola:" << endl << endl;
        while(aux)
        {
            aux->preserva->mostrarReserva();
            aux = aux->siguiente;
        }
        cout << "Fin de los datos de la cola" << endl << endl;
    }
}

