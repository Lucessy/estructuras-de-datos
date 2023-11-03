#ifndef LISTA_H
#define LISTA_H
#include <NodoLista.h>

class Lista
{
    public:
        Lista();
        virtual ~Lista();
        void extenderListaPorDerecha(Pedido& elem);
        void extenderListaPorIzquierda(Pedido& elem);
        Pedido& elemInicial();
        Pedido& elemFinal();
        bool esVacia();
        Pedido& elemEnPosicion(int indice);
        void mostrarDatosLista();
        void completarSiguientes4Pedidos();
        NodoLista* getPrimero();

    protected:

    private:
        NodoLista* primero;
        NodoLista* ultimo;
        int longitud;
        friend class NodoLista;
};

#endif // LISTA_H
