#include "Pila.h"
#include <iostream>
#include "NodoPila.h"
#include "Pedido.h"
#include "Mesa.h"
using namespace std;


Pila::Pila()
{
    //ctor
    cima=NULL;
}

Pila::~Pila()
{
    //dtor.
    while(cima)
    {
        desapilar();
    }
}
bool Pila::esVacia()
{
    return cima == NULL;
}

void Pila::apilar(Mesa& mesa)
{
    NodoPila* nuevo = new NodoPila(mesa,cima);
    cima = nuevo;
}



void Pila::vaciarPila()
{
    if(esVacia())
    {
        cout << "La pila de mesas est� vac�a."<<endl;
        return;
    }
    while(cima!=NULL)
    {
        desapilar();
    }
    cout << "Pila de mesas vaciada."<<endl;
}

void Pila::desapilar()
{
    if(cima)
    {
        NodoPila* nodo= cima;
        cima = nodo->siguiente;
        delete nodo;
    }
}

Mesa& Pila::getMesaCima()
{
    return *(cima->pmesa);

}

void Pila::mostrarPilaMesas()
{
    NodoPila* aux = cima;
    if(esVacia())
    {
        cout << "Pila vacia" << endl;
    }
    else
    {
        cout << "Datos de la pila:" << endl << endl;
        while(aux)
        {
            aux->pmesa->mostrarMesa();
            aux = aux->siguiente;
        }
        cout << "Fin de los datos de la pila de mesas." << endl << endl;
    }
}

Mesa** Pila::buscarMesas(Reserva* pReserva, int capacidad)
{

    NodoPila* ant1 = nullptr;
    NodoPila* nodo1 = nullptr;

    NodoPila* ant2 = nullptr;
    NodoPila* nodo2 = nullptr;

    NodoPila* antAux = nullptr;
    NodoPila* nodoAux = cima;

    const int combs[4][2][2] = {{{2,0},{4,0}},
        {{4,0},{2,2}},
        {{2,4},{4,4}},
        {{4,4},{0,0}}
    };

    // Busca las dos posibles combinaciones de mesas para la capacidad dada siguiendo el orden de preferencia
    // Ejemplo: Para 6 personas, currentComb =  {{2,4},{4,4}}, por lo que se prioriza la combinaci�n {2,4} a {4,4}
    bool mesasEncontradas = false;
    for(int i = 0; i<2; i++)
    {

        //Se buscan ambas mesas para la combinaci�n actual
        bool buscando = true;
        while(nodoAux && buscando)
        {
            if((capacidad == 7 || capacidad == 8) && i==1)
            {
                ant1 = nullptr;
                nodo1 = nullptr;
                ant2 = nullptr;
                nodo2 = nullptr;
                break;
            }

            //Encontrar primera mesa
            if(nodoAux->pmesa->situacionMesa == pReserva->getSituacionMesa())
            {
                ;
                //Si encuentra la primera mesa la guarda
                if(nodo1 == nullptr && (nodoAux->pmesa->capacidad == combs[((capacidad-1)/2)][i][0]))
                {
                    ant1 = antAux;
                    nodo1 = nodoAux;
                }
                //Si encuentra la segunda mesa la guarda
                else if(nodo2 == nullptr&&(nodoAux->pmesa->capacidad == combs[((capacidad-1)/2)][i][1]))
                {
                    ant2 = antAux;
                    nodo2 = nodoAux;
                }
                //Si tenemos la primera mesa y la segunda o la primera sin necesitar la segunda se deja de buscar
                if(nodo1 != nullptr && (nodo2!=nullptr || combs[((capacidad-1)/2)][i][1] == 0))
                {
                    buscando = false;
                }
            }
            //Cambio de nodo
            antAux = nodoAux;
            nodoAux = nodoAux->siguiente;
        }
        //Si ha encontrado la combinaci�n primera no se sigue
        if(!buscando)
        {
            mesasEncontradas = true;
            break;
        }
        //Si no se ha encontrado la combinaci�n , se reinician las variables
        else
        {
            ant1 = nullptr;
            nodo1 = nullptr;
            ant2 = nullptr;
            nodo2 = nullptr;
        }
    }

    Mesa** mesas = new Mesa*[2];
    mesas[0] = nullptr;
    mesas[1] = nullptr;

    //Se extirpan las mesas
    if(mesasEncontradas)
    {

        //Se extirpa la mesa 1
        mesas[0] = nodo1->pmesa;
        if(ant1 != nullptr)
        {
            ant1->siguiente = nodo1->siguiente;
        }
        else
        {
            cima = nodo1->siguiente;
        }
        if(ant2 == nodo1)
        {
            ant2 = ant1;
        }
        delete nodo1;

        //Se extirpa la mesa 2 si la hay
        if(nodo2 != nullptr)
        {
            mesas[1] = nodo2->pmesa;
            if(ant2 != nullptr)
            {
                ant2->siguiente = nodo2->siguiente;
            }
            else
            {
                cima = nodo2->siguiente;
            }
            delete nodo2;
        }
    }

    return mesas;

}

/**
*  Genera una pila de 20 mesas con datos aleatorios (al menos 8 en terraza)
*/
void Pila::generarMesas(bool seHaComenzadoLaSimulacion)
{
    //Comprueba que la simulaci�n no ha comenzado a�n para evitar duplicamiento de mesas
    if(seHaComenzadoLaSimulacion)
    {
        cout << "No se puede alterar la pila de mesas una vez se ha empezado la simulaci�n." << endl;
        return;
    }
    //Si la pila no est� vacia se vac�a primero
    if(!esVacia())
    {
        cout << "Generando nueva pila de mesas. Vaciando la pila anterior." << endl;
        vaciarPila();
    }
    //Inicializaci�n de variables
    string situaciones[2] = {"Terraza","Interior"};
    int capacidades[2] = {2,4};
    int numeroMesasTerraza = 0;
    int numSituacion;
    //Generaci�n de mesas
    for(int numeroMesa=20; numeroMesa>=1; numeroMesa--)
    {
        //Genera aleatoriamente la capacidad
        int capacidad = capacidades [rand() % 2];
        string situacion;

        //Genera aleatoriamente la situaci�n
        numSituacion = rand() % 2;
        //Garantizamos que habr� un m�nimo de 8 mesas en Terraza
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
        apilar(*pmesa);
    }
}

bool Pila::contiene(Mesa* mesa)
{
    NodoPila* aux = cima;
    while(aux)
    {
        if (aux->pmesa == mesa)
        {
            return true;
        }
        aux = aux->siguiente;
    }
    return false;
}

