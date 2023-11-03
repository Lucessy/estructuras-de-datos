#ifndef PEDIDO_H
#define PEDIDO_H
#include <iostream>
#include <string>
#include "Mesa.h"
using namespace std;

class Pedido
{
public:
    Pedido(Mesa* mesa[], string nomCliente, int numPersonas, string prefMenu, string sitMesa,bool finalizado);
    virtual ~Pedido();

    string getNombreCliente();
    int getNumPersonas();
    string getPreferenciaMenu();
    string getSituacionMesa();
    bool getFinalizado();
    void setFinalizado(bool estado);
    void restablecerMesasAsignadas();
    Mesa* getMesaAsignada1();
    Mesa* getMesaAsignada2();
    void mostrarPedido();

protected:

private:

    string nombreCliente;
    int numeroPersonas;
    string preferenciaMenu;
    string situacionMesa;
    bool finalizado;
    Mesa* mesa[2];


};

#endif // PEDIDO_H
