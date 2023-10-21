#ifndef NODOCOLA_H
#define NODOCOLA_H
#include <iostream>

class NodoCola
{
    public:
        NodoCola();
        //Otro constructor
        NodoCola(char e, NodoCola*sig=NULL);
        virtual ~NodoCola();
        NodoCola *siguiente;
        char elemento;

    protected:

    private:
        //Los atributos
};

#endif // NODOCOLA_H
