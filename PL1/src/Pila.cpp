#include "Pila.h"
#include <iostream>
#include "NodoPila.h"
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

bool Pila::buscarMesa(Reserva* pReserva, int capacidad)
{
    bool mesaEncontrada = false;
    bool ultimoNodo = false;
    bool aumentarMesa = false;
    int capacidadActual;
    //Creamos un puntero auxiliar hacia el NodoPila de la cima
    NodoPila* actualNodo = cima;
    //Creamos los punteros anterior y siguiente para poder localizar la mesa bien.
    NodoPila* anteriorNodo = nullptr;
    NodoPila* siguienteNodo = actualNodo->siguiente;
    cout << "COMENZANDO---------" << endl;
    if(capacidad<=4)
    {
        capacidadActual = (capacidad <=2 ? 2 : 4);

        while (!mesaEncontrada && !ultimoNodo)
        {
            if(capacidadActual==actualNodo->pmesa->getCapacidad() && pReserva->getSituacionMesa()==actualNodo->pmesa->getSituacionMesa())
            {
                cout << "MESA ENCONTRADA---------" << endl;
                mesaEncontrada = true;
                pReserva->asignarMesa(actualNodo->pmesa);
                if(anteriorNodo==nullptr)
                {
                    cima = siguienteNodo;
                }
                else
                {
                    anteriorNodo->siguiente = siguienteNodo;

                }
                delete actualNodo;
            }
            else
            {
                if(siguienteNodo==nullptr)
                {
                    if(capacidad<=2 && !aumentarMesa)
                    {
                        //Resetamos los punteros de la pila para buscar de nuevo una mesa más grande
                        actualNodo = cima;
                        anteriorNodo = nullptr;
                        siguienteNodo = actualNodo->siguiente;
                        aumentarMesa = true;
                        capacidadActual = 4;
                        cout << "AUMENTO DE MESA---------" << endl;
                    }
                    else
                    {
                        ultimoNodo = true;
                    }
                }
                else
                {
                    anteriorNodo = actualNodo;
                    actualNodo = siguienteNodo;
                    siguienteNodo = actualNodo->siguiente;
                }
            }

        }

        return mesaEncontrada;
    }
    else
    {
        bool mesaEncontrada2 = false;

        //Creamos un puntero auxiliar hacia el NodoPila de la cima
        NodoPila* actualNodo2 = cima;
        //Creamos los punteros anterior y siguiente para poder localizar la mesa bien.
        NodoPila* anteriorNodo2 = nullptr;
        NodoPila* siguienteNodo2 = actualNodo2->siguiente;
        capacidadActual = (capacidad <=6 ? 2 : 4);

        cout << "COMENZANDO WHILE---------" << endl;
        while (!mesaEncontrada && !ultimoNodo)
        {
            if(capacidadActual==actualNodo->pmesa->getCapacidad() && pReserva->getSituacionMesa()==actualNodo->pmesa->getSituacionMesa())
            {
                cout << "MESA ENCONTRADA1---------" << endl;
                mesaEncontrada = true;
                capacidadActual = 4;
                while(!mesaEncontrada2 && !ultimoNodo)
                {
                    if(capacidadActual==actualNodo2->pmesa->getCapacidad() && pReserva->getSituacionMesa()==actualNodo2->pmesa->getSituacionMesa() && actualNodo->pmesa->getNumMesa()!=actualNodo2->pmesa->getNumMesa())
                    {

                        cout << "MESA ENCONTRADA2---------" << endl;
                        mesaEncontrada2 = true;
                    }
                    else
                    {
                        if(siguienteNodo2==nullptr)
                        {
                            ultimoNodo = true;
                        }
                        else
                        {
                            anteriorNodo2 = actualNodo2;
                            actualNodo2 = siguienteNodo2;
                            siguienteNodo2 = actualNodo2->siguiente;
                        }

                    }
                }
            }
            else
            {
                if(siguienteNodo==nullptr)
                {
                    if(capacidad<=6 && !aumentarMesa)
                    {
                        //Resetamos los punteros de la pila para buscar de nuevo una mesa más grande
                        actualNodo = cima;
                        anteriorNodo = nullptr;
                        siguienteNodo = actualNodo->siguiente;
                        aumentarMesa = true;
                        capacidadActual = 4;
                        cout << "Aumentamos capacidad---------" << endl;
                    }
                    else
                    {
                        ultimoNodo = true;
                    }
                }
                else
                {
                    cout << "Siguiente mesa---------" << endl;
                    anteriorNodo = actualNodo;
                    actualNodo = siguienteNodo;
                    siguienteNodo = actualNodo->siguiente;
                }
            }

        }

        cout << "SALIENDO WHILE---------" << endl;
        if(mesaEncontrada && mesaEncontrada2)
        {
            if(actualNodo->pmesa->getNumMesa()>actualNodo2->pmesa->getNumMesa())
            {
                cout << "HACIENDO EL SWITCH---------" << endl;
                std::swap(actualNodo, actualNodo2);
                std::swap(anteriorNodo, anteriorNodo2);
                std::swap(siguienteNodo, siguienteNodo2);
            }
            cout << "SALIENDO switch---------" << endl;

            pReserva->asignarMesa(actualNodo->pmesa);
            pReserva->asignarMesa(actualNodo2->pmesa);

            cout << "Terminado asignar---------" << endl;
            if(anteriorNodo==nullptr)
            {
                if(anteriorNodo2->pmesa->getNumMesa()==actualNodo->pmesa->getNumMesa())
                {
                    cima = siguienteNodo2;
                }else{
                    cima = siguienteNodo;
                    anteriorNodo2->siguiente = siguienteNodo2;
                }
            }
            else
            {
                if(anteriorNodo2->pmesa->getNumMesa()==actualNodo->pmesa->getNumMesa())
                {
                    anteriorNodo->siguiente = siguienteNodo2;
                }else
                {
                    anteriorNodo->siguiente=siguienteNodo;
                    anteriorNodo2->siguiente=siguienteNodo2;
                }
            }
                delete actualNodo;
                delete actualNodo2;


            cout << "AMBAS MESAS ENCONTRADAS---------" << endl;

            return true;
        }

        cout << "NIGUNA MESA ENCONTRADA---------" << endl;
        return false;
    }

}


