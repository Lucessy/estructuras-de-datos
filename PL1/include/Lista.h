#ifndef LISTA_H
#define LISTA_H
class ABB;
#include <NodoLista.h>
#include "Pila.h"
#include "ABB.h"

class Lista
{
    public:
        Lista();
        virtual ~Lista();
        void extenderListaPorDerecha(Pedido& elem);
        void extenderListaPorIzquierda(Pedido& elem);
        Pedido& elemInicial();
        Pedido& elemFinal();
        void eliminarPrimero();
        void eliminarUltimo();
        bool esVacia();
        void mostrarDatosLista();
        void completarSiguientesPedidos(Pila& pilaMesas, ABB& abbPedidos);
        NodoLista* getPrimero();

    protected:

    private:
        NodoLista* primero;
        NodoLista* ultimo;
        int longitud;
        friend class NodoLista;
};

#endif // LISTA_H
