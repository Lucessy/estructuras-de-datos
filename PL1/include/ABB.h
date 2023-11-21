#ifndef ABB_H
#define ABB_H


class ABB
{
    public:
        ABB();
        ABB(string nombre, NodoABB *hijo_lado_i=nullptr, NodoABB *hijo_lado_d=nullptr);
        virtual ~ABB();
        void verInOrden();
        void insertar(string nombre);

    protected:

    private:
        NodoABB *raiz;
        void verInOrden(NodoABB *arb);
        void insertar(string nom, NodoABB *nodo);

};

#endif // ABB_H
