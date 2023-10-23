#ifndef NODOPILA_H
#define NODOPILA_H
#include "Mesa.h"


class NodoPila
{
    public:
        NodoPila(Mesa& elemento,NodoPila *sig = NULL);
        virtual ~NodoPila();

    protected:

    private:
        Mesa* pmesa;
        NodoPila *siguiente;
        friend class Pila;
};

#endif // NODOPILA_H
