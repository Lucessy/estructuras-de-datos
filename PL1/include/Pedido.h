#ifndef PEDIDO_H
#define PEDIDO_H


class Pedido
{
    public:
        Pedido();
        virtual ~Pedido();
        int getNumMesa();
        string getPreferenciaMenu();
        bool getFinalizado();

    protected:

    private:
        //No estoy muy segura de como poner estos atributos
        //porque los comparte con Reserva y Mesa :(

        //string nombreCliente;
        int numMesa[2];
        //int numero_Personas;
        string preferenciaMenu;
        //string situacion_Mesa;
        bool finalizado;
};

#endif // PEDIDO_H
