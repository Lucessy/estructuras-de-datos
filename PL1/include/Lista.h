#ifndef LISTA_H
#define LISTA_H q
#include <NodoLista.h>
#include "Pila.h"

class Lista
{
    public:
        Lista();
        virtual ~Lista();
        void extenderListaPorDerecha(Pedido& elem, int ult = -1); //Se inicia a -1 para que no entre en caso de no ser llamado
        void extenderListaPorIzquierda(Pedido& elem, int ult = -1);
        Pedido& elemInicial();
        Pedido& elemFinal();
        void eliminarPrimero();
        void eliminarUltimo();
        bool esVacia();
        void mostrarDatosLista();
        Lista sacarSiguientesPedidos(Pila& pilaMesas);
        NodoLista* getPrimero();

        void extenderListaPorCategoria(Pedido& elem);

    protected:

    private:
        NodoLista* ultCompleto;
        NodoLista* ultSinGluten;
        NodoLista* ultVegano;

        NodoLista* primero;
        NodoLista* ultimo;
        int longitud;
        friend class NodoLista;
};

#endif // LISTA_H
