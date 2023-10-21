#ifndef COLA_H
#define COLA_H
#include "NodoCola.h"

class Cola
{
    public:
        Cola();
        virtual ~Cola();
        //Metodos de la clase
        void encolar(char);
        char desencolar();
        char inicio();
        char fin();
        bool es_vacia();
        void mostrarCola();

    protected:

    private:
        NodoCola * primero;
        NodoCola * ultimo;
        int longitud;
};

#endif // COLA_H
