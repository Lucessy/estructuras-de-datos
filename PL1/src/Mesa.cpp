#include "Mesa.h"

//numero {1..20}
//Capacidad {2 || 4}
//situacion {Interior || Terraza}

Mesa::Mesa()
{
    //Create new random table
}

Mesa::Mesa(int numero,int capacidad,string situacion_Mesa)
{
    //Create new random table
}

Mesa::~Mesa()
{
    //dtor
}

int get_num_mesa()
{
    return num_mesa;
}

int get_capacidad()
{
    return capacidad;
}

string get_situacion_Mesa()
{
    return situacion_Mesa;
}
