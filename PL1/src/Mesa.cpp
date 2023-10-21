#include "Mesa.h"

//numero {1..20}
//Capacidad {2 || 4}
//situacion {Interior || Terraza}

Mesa::Mesa()
{
    //Create new random table
}

Mesa::Mesa(int numero,int capacidad,string situacionMesa)
{
    //Create new random table
}

Mesa::~Mesa()
{
    //dtor
}

int Mesa::getNumMesa()
{
    return numMesa;
}

int Mesa::getCapacidad()
{
    return capacidad;
}

string Mesa::getSituacionMesa()
{
    return situacionMesa;
}
