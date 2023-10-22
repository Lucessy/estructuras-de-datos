#include <iostream>
#include <locale.h>
using namespace std;



int main()
{
    //Cambiamos el formato de texto de la consola para que soporte tildes y otros carácteres castellanos
    setlocale(LC_ALL, "");

    //string nombresPosibles[] = {"Alice", "Bob", "Charlie", "David", "Eve", "Frank","Grace", "Hannah", "Ivan", "Jack", "Karen"}

    //Comienzo de programa
    //Mostrar por pantalla las opciones disponibles:
    cout << "Bienvenido al simulador de gestión de mesas y reservas UltraReserva3000.\n";
    cout << "Escribe el número de una las siguientes opciones para realizarla:\n";
    cout << "1. Generar una cola de reservas aleatoria\n";
    cout << "2. Mostrar los datos de la cola de reservas\n";
    cout << "3. Borrar los datos de la cola de reservas\n";
    cout << "4. Gerarar una pila de 20 mesas aleatoria\n";
    cout << "5. Mostrar los datos de la pila de mesas\n";
    cout << "6. Borrar los datos de la pila de mesas\n";
    cout << "7. Simular la gestión de la próxima reserva de la cola\n";
    cout << "8. Simular la gestión de toda la ronda de reservas de la próxima hora\n";
    cout << "9. Simular la gestión de todas las reservas de la cola\n";
    cout << "0. Salir\n\n";

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
            cout << "La elección escogida no es correcta. Escoge una válida.\n\n";
        }
        maxIntentos--;
    }
    if(maxIntentos == 0)
    {
        cout << "Superaste el número de intentos de elección. Finalizando programa.";
        return 0;
    }

    switch(eleccion)
    {
        case 1:
            cout << "Opcion 1";
            break;
        case 2:
            cout << "Salir";
            break;
        case 3:
            cout << "Salir";
            break;
        case 4:
            cout << "Salir";
            break;
        case 5:
            cout << "Salir";
            break;
        case 6:
            cout << "Salir";
            break;
        case 7:
            cout << "Salir";
            break;
        case 8:
            cout << "Salir";
            break;
        case 9:
            cout << "Salir";
            break;
        case 0:
            cout << "Salir";
            break;
    }

    cout << "EndOfMain";



}
