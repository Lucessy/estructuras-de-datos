#ifndef ABB_H
#define ABB_H
#include <NodoABB.h>
#include <string>
using namespace std;

class ABB
{
    public:
        ABB();
        ABB(string nombre, NodoABB*hijo_lado_i=nullptr, NodoABB*hijo_lado_d=nullptr);
        ABB(NodoABB*r);
        virtual ~ABB();
        void verEnOrden();
        void insertar(string nombre);

    protected:

    private:
        NodoABB* raiz;
        void verEnOrden(NodoABB *arb);
        void insertar(string nom, NodoABB *nodo);

};

#endif // ABB_H
