#include "Gestor.h"
#include "Cola.h"
#include "Reserva.h"
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

Gestor::Gestor()
{
    //ctor
}

Gestor::~Gestor()
{
    //dtor
}

Cola Gestor::generarColaReservas()
{
    Cola cola;
    string times[3] = {"13:30", "14:30", "15:30"};

    // Seed the random number generator
    srand(time(0));

    // Generate at least 12 reservations
    for(int i = 0; i < 12; i++)
    {
        // Generate a random client name (in this case, "Client" followed by a number)
        string clientName = "Client" + to_string(i+1);

        // Choose a time from the array in order
        string time = times[i / 4];

        // Create the reservation and add it to the queue
        Reserva reserva(clientName, time);
        cola.encolar(reserva);
    }

    // You can add more reservations with completely random data here if you want
    for(int j = 12; j < 20; j++)
    {
        // Generate a random client name (in this case, "Client" followed by a number)
        string clientName = "Client" + to_string(j+1);

        // Choose a random time from the array
        string time = times[rand() % 3]; // Use rand() to choose a random time

        // Create the reservation and add it to the queue
        Reserva reserva(clientName, time);
        cola.encolar(reserva);
    }

    return cola;
}
