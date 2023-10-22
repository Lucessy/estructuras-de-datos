#ifndef LISTA_H
#define LISTA_H
#include <NodoLista.h>


class Lista
{
    public:
        Lista();
        virtual ~Lista();

        void extenderListaPorDerecha(const Pedido& elem);
        void extenderListaPorIzquierda(const Pedido& elem);
        const Pedido& elemInicial();
        const Pedido& elemFinal();
        bool esVacia();
        const Pedido& elemEnPosicion(int indice);
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
