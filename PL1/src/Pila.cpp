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
    //dtor
    while(cima)
    {
        desapilar();
    }
}
bool Pila::esVacia()
{
    return cima == NULL;
}

void Pila::apilar(Mesa& mesa) //Modificado
{
    NodoPila* nuevo = new NodoPila(mesa,cima);
    cima = nuevo;
}

void Pila::apilarEnOrden(Mesa& mesa) //Modificado
{
    NodoPila* aux = cima;
    NodoPila* anterior = nullptr;
    bool apilado = false;
    NodoPila* nuevo;
    while(!apilado)
    {
        if(aux->siguiente!=nullptr)
        {
            if(aux->pmesa->getNumMesa()>mesa.getNumMesa())
            {
                if(cima==aux)
                {
                    nuevo = new NodoPila(mesa,cima);
                    cima = nuevo;
                    cout << "APILADO CIMA" << endl;
                    apilado = true;
                }
                else
                {
                    apilado = true;
                    nuevo = new NodoPila(mesa,aux);
                    anterior->siguiente = nuevo;
                    cout << "APILADO ENTRE MEDIAS" << endl;
                }
            }
            else
            {
                anterior = aux;
                aux = aux->siguiente;
            }

        }
        else
        {
            apilado = true;
            if(aux->pmesa->getNumMesa()>mesa.getNumMesa())
            {
                nuevo = new NodoPila(mesa,aux);
                anterior->siguiente = nuevo;
            }
            else
            {
                nuevo = new NodoPila(mesa,nullptr);
                aux->siguiente=nuevo;
            }
        }
    }
    cout << nuevo->pmesa->getNumMesa() << endl;
}

void Pila::vaciarPila()
{
    while(cima!=NULL)
    {
        desapilar();
    }
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
void Pila::mostrarCima()
{
    if(esVacia())
    {
        cout << "Pila vacia"<<endl;
    }
    else
    {
        cout << "Número de mesa de cima: " << cima->pmesa ->numMesa << endl;
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
        cout << "Fin de los datos de la cola de reservas." << endl << endl;
    }
}

Mesa** Pila::buscarMesas(Reserva* pReserva, int capacidad)
{
    cout << "Entro xd" << endl;
    NodoPila* ant1 = nullptr;
    NodoPila* nodo1 = nullptr;
    NodoPila* sig1 = nullptr;

    NodoPila* ant2 = nullptr;
    NodoPila* nodo2 = nullptr;
    NodoPila* sig2 = nullptr;

    NodoPila* antAux = nullptr;
    NodoPila* nodoAux = cima;
    NodoPila* sigAux = nodoAux->siguiente;



    const int combs[4][2][2] = {{{2,0},{4,0}},
                            {{4,0},{2,2}},
                            {{2,4},{4,4}},
                            {{4,4},{0,0}}};

    // Busca las dos posibles combinaciones de mesas para la capacidad dada siguiendo el orden de preferencia
    // Ejemplo: Para 6 personas, currentComb =  {{2,4},{4,4}}, por lo que se prioriza la combinación {2,4} a {4,4}
    bool mesasEncontradas = false;
    for(int i = 0; i<2; i++)
    {
        cout << "Buscando primera combinación" << endl;
        //Se buscan ambas mesas para la combinación actual
        bool buscando = true;
        while(nodoAux && buscando)
        {
            //Encontrar primera mesa
            if(nodoAux->pmesa->situacionMesa == pReserva->getSituacionMesa())
            {
                cout << "Analizando mesa con misma situacion" << endl;
                //Si encuentra la primera mesa la guarda
                if(nodoAux->pmesa->capacidad == combs[((capacidad-1)/2)][i][0] && nodo1 == nullptr)
                {
                    cout << "Mesa 1 encontrada" << endl;
                    ant1 = antAux;
                    nodo1 = nodoAux;
                    sig1 = sigAux;
                }
                //Si encuentra la segunda mesa la guarda
                else if(nodoAux->pmesa->capacidad == combs[((capacidad-1)/2)][i][1] && nodo2 == nullptr)
                {
                    cout << "Mesa 2 encontrada" << endl;
                    ant2 = antAux;
                    nodo1 = nodoAux;
                    sig1 = sigAux;
                }
                //Si tenemos la primera mesa y la segunda o la primera sin necesitar la segunda se deja de buscar
                if(nodo1 != nullptr && (nodo2!=nullptr || combs[((capacidad-1)/2)][i][1] == 0))
                {
                    cout << "Combinación encontrada" << endl;
                    buscando = false;
                }
            }
            //Cambio de nodo
            antAux = nodoAux;
            nodoAux = sigAux;
            sigAux = nodoAux->siguiente;
        }
        //Si ha encontrado la combinación primera no se sigue
        if(!buscando){
            mesasEncontradas = true;
            break;
        }
        //Si no ha encontrado la combinación , se reinician las variables
        else{
            ant1 = nullptr;
            nodo1 = nullptr;
            sig1 = nullptr;
            ant2 = nullptr;
            nodo2 = nullptr;
            sig2 = nullptr;
        }
    }

    Mesa** mesas = new Mesa*[2];
    mesas[0] = nullptr;
    mesas[1] = nullptr;

    cout << "mesas encontradas: " << mesasEncontradas << endl;
    //Se extirpan las mesas
    if(mesasEncontradas){

        //Se extirpa la mesa 1
        mesas[0] = nodo1->pmesa;
        if(ant1 != nullptr){
            ant1->siguiente = sig1;
        }else{
            cima = sig1;
        }
        delete nodo1;

        //Se extirpa la mesa 2 si la hay
        if(nodo2 != nullptr){
            mesas[1] = nodo2->pmesa;
            if(ant2 != nullptr){
                ant2->siguiente;
            }else{
                cima = sig2;
            }
            delete nodo2;
        }
    }

    cout << "Fin función" << endl;
    return mesas;

}


