#ifndef NODOPILA_H
#define NODOPILA_H
#include <Mesa.h>


class NodoPila
{
    public:
        NodoPila();
        NodoPila(const Mesa& elemento,NodoPila *sig = NULL);
        virtual ~NodoPila();

    protected:

    private:
        Mesa elemento;
        NodoPila *siguiente;
        friend class Pila;
};

#endif // NODOPILA_H
