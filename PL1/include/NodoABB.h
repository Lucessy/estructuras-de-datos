#ifndef NODOABB_H
#define NODOABB_H
#include <string>

using namespace std;

class NodoABB
{
    public:
        NodoABB(string nombreCliente, NodoABB*izq=nullptr, NodoABB*der=nullptr);
        virtual ~NodoABB();

    protected:

    private:
        string nombreCliente;
        NodoABB* hijo_i;
        NodoABB* hijo_d;
        friend class ABB;
};

#endif // NODOABB_H
