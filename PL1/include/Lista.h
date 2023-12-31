#ifndef LISTA_H
#define LISTA_H q
#include <NodoLista.h>
#include "Pila.h"

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
        void mostrarDatosLista(string pref = "");
        Lista sacarSiguientesPedidos(Pila& pilaMesas);
        NodoLista* getPrimero();
        int getLongitud();
        NodoLista* getUltVegano();
        void extenderListaPorCategoria(Pedido& elem);

        int getLongCompleto();
        int getLongSinGluten();
        int getLongVegano();

    protected:

    private:
        NodoLista* ultCompleto;
        int longCompleto;
        NodoLista* ultSinGluten;
        int longSinGluten;
        NodoLista* ultVegano;
        int longVegano;


        NodoLista* primero;
        NodoLista* ultimo;
        int longitud;

        void finalizarPedidos(Lista& listaPedidos,Pila& pilaMesas);
        void insertarMitadCategoria(Lista& listaAux,NodoLista* primCategoria,int* contadorCategoria,NodoLista** punteroCategoria);
        friend class NodoLista;
};

#endif // LISTA_H
