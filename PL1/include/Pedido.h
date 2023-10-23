#ifndef PEDIDO_H
#define PEDIDO_H
#include <iostream>
#include <string>
using namespace std;

class Pedido
{
    public:
        Pedido(int numMesa[], string nomCliente, int numPersonas, string prefMenu, string sitMesa, bool finalizado);
        virtual ~Pedido();
        int* getpNumMesa();
        string getNombreCliente();
        int getNumPersonas();
        string getPreferenciaMenu();
        string getSituacionMesa();
        bool getFinalizado();
        void setFinalizado(bool estado);

        void mostrarPedido();

    protected:

    private:
        int numeroMesa[2];
        string nombreCliente;
        int numeroPersonas;
        string preferenciaMenu;
        string situacionMesa;
        bool finalizado;

};

#endif // PEDIDO_H
