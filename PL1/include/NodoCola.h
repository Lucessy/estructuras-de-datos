#ifndef NODOCOLA_H
#define NODOCOLA_H
#include <iostream>

class NodoCola
{
    public:
        NodoCola();
        //Otro constructor
        NodoCoLa(char e, NodoCola*sig=NULL);
        virtual ~NodoCola();

    protected:

    private:
        //Los atributos
        NodoCola *siguiente;
        char elemento;
};

#endif // NODOCOLA_H
