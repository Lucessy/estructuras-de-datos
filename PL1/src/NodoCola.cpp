#include "NodoCola.h"

NodoCola::NodoCola()
{
    elemento='o';
    siguiente=NULL;
    //ctor
}

NodoCola::NodoCola(char e,NodoCola*sig)
{
    elemento = e;
    siguiente = sig;
}

NodoCola::~NodoCola()
{
    //dtor
}
