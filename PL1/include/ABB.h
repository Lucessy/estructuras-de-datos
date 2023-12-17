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
    void verEnOrden(bool mostrarSoloNombres=false,bool soloVeganos=false);
    void insertar(string nombre, Pedido* pedido);
    Lista* buscarListaPedidosPorNombre(string nombreCliente);

    void sumarCategorias();
    int getLongCompleto();
    int getLongSinGluten();
    int getLongVegano();
protected:

private:
    NodoABB* raiz;
    void verEnOrden(NodoABB *arb,bool mostrarSoloNombres,int left_counter,int right_counter,bool soloVeganos);
    void insertar(string nom, Pedido* pedido, NodoABB *nodo);
    Lista* buscarListaPedidosPorNombre(string nombreCliente,NodoABB* nodo);

    int longCompleto;
    int longSinGluten;
    int longVegano;
    void sumarCategorias(NodoABB *nodo,int left_counter,int right_counter);

};

#endif // ABB_H
