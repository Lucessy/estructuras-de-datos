#ifndef ABB_H
#define ABB_H
#include <NodoABB.h>
#include <string>
#include <Lista.h>
using namespace std;

class ABB
{
    public:
        ABB();
        virtual ~ABB();
        void verEnOrden(bool mostrarSoloNombres=false);
        void insertar(string nombre, Pedido* pedido);
        Lista* buscarListaPedidosPorNombre(string nombreCliente);

    protected:

    private:
        NodoABB* raiz;
        void verEnOrden(NodoABB *arb,bool mostrarSoloNombres,int left_counter,int right_counter);
        void insertar(string nom, Pedido* pedido, NodoABB *nodo);
        Lista* buscarListaPedidosPorNombre(string nombreCliente,NodoABB* nodo);

};

#endif // ABB_H
