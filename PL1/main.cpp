#include <iostream>
#include <locale.h>
#include "Cola.h"
#include "NodoCola.h"
#include "Reserva.h"
#include "Gestor.h"
#include "Lista.h"
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
using namespace std;


Gestor gestor;
Cola colaReservas;
Cola colaReservasPdtes;
Lista listaPedidos;
Pila pilaMesas;

int main()
{
    //Cambiamos el formato de texto de la consola para que soporte tildes y otros carácteres castellanos
    setlocale(LC_ALL, "");

    //string nombresPosibles[] = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank","Grace", "Hannah", "Ivan", "Jack", "Karen"}

    //Comienzo de programa
    //Mostrar por pantalla las opciones disponibles:
    cout << "Bienvenido al simulador de gestión de mesas y reservas UltraReserva3000." << endl;

    bool programaEnEjecucion = true;
    while(programaEnEjecucion)
    {
        cout << endl << "Menú: Escribe el número de una las siguientes opciones para realizarla:" << endl;
        cout << "1. Generar una cola de reservas aleatoria" << endl;
        cout << "2. Mostrar los datos de la cola de reservas" << endl;
        cout << "3. Borrar los datos de la cola de reservas" << endl;
        cout << "4. Generar una pila de 20 mesas aleatoria" << endl;
        cout << "5. Mostrar los datos de la pila de mesas" << endl;
        cout << "6. Borrar los datos de la pila de mesas" << endl;
        cout << "7. Simular la gestión de la próxima reserva de la cola" << endl;
        cout << "8. Simular la gestión de toda la ronda de reservas de la próxima hora" << endl;
        cout << "9. Simular la gestión de todas las reservas de la cola" << endl;
        cout << "0. Salir\n" << endl;

        int eleccion;
        bool eleccionValida = false;
        int maxIntentos = 3;
        while(!eleccionValida && maxIntentos>0)
        {
            cin >> eleccion;
            if(eleccion >=0 && eleccion < 10)
            {
                eleccionValida=true;
            }
            else
            {
                cout << "La elección escogida no es correcta. Escoge una válida.\n" << endl;
            }
            maxIntentos--;
        }
        if(maxIntentos == 0)
        {
            cout << "Superaste el número de intentos de elección. Finalizando programa." << endl;
            return 0;
        }

        switch(eleccion)
        {
            case 1:
                cout << "Generando aleatoriamente la cola de reservas..." << endl;
                gestor.generarColaReservas(colaReservas);
                break;
            case 2:
                cout << "Mostrando la cola de reservas creada..." << endl;
                gestor.mostrarColaReservas(colaReservas);
                break;
            case 3:
                cout << "Vaciando la cola de reservas..." << endl;
                gestor.vaciarColaReservas(colaReservas);
                break;
            case 4:
                cout << "Generando aleatoriamente la pila de mesas..." << endl;
                gestor.generarPilaMesas(pilaMesas);
                break;
            case 5:
                cout << "Mostrando la pila de mesas creada..." << endl;
                gestor.mostrarPilaMesas(pilaMesas);
                break;
            case 6:
                cout << "Vaciando la pila de mesas..." << endl;
                gestor.vaciarPilaMesas(pilaMesas);
                break;
            case 7:
                cout << "Simulando la gestión de la primera reserva de la cola de reservas..." << endl;
                gestor.simularGestionPrimeraReserva(colaReservas, colaReservasPdtes, listaPedidos);
                break;
            case 8:
                cout << "Simulando la gestión de las reservas y creación de pedidos de todas las reservas para la misma hora..." << endl;
                gestor.simularGestionReservasProximaHora(colaReservas, colaReservasPdtes, listaPedidos); //Opción 8
                break;
            case 9:
                cout << "Simulando la gestión de todas las reservas del restaurante..." << endl;
                gestor.simularGestionReservasTotal(colaReservas, colaReservasPdtes, listaPedidos); //Opción 9
                break;

            case 0:
                cout << "Saliendo del programa..." << endl;
                gestor.Salir();
                programaEnEjecucion = false;
                break;
            }
    }
    cout << "EndOfMain";



}



