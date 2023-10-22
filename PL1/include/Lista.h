#ifndef LISTA_H
#define LISTA_H
#include <NodoLista.h>


class Lista
{
    public:
        Lista();
        virtual ~Lista();

        void extenderListaPorDerecha(int elem);
        void extenderListaPorIzquierda(int elem);
        int elemInicial();
        int elemFinal();
        bool esVacia();
        int elemEnPosicion(int indice);
        void mostrarDatosLista();
        void borrarLista();


    protected:

    private:
        NodoLista* primero;
        NodoLista* ultimo;
        int longitud;
        friend class NodoLista;
};

#endif // LISTA_H
