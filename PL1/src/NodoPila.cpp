#include "NodoPila.h"
#include "Mesa.h"
#include <iostream>

NodoPila::NodoPila(Mesa& elemento, NodoPila* sig)
{
    pmesa = &elemento;
    siguiente = sig;
}

NodoPila::~NodoPila()
{
    //dtor.
}
