#ifndef PEDIDO_H
#define PEDIDO_H


class Pedido
{
    public:
        Pedido();
        virtual ~Pedido();
        int get_num_Mesa();
        string get_preferencia_Menu();
        bool get_finalizado();

    protected:

    private:
        //No estoy muy segura de como poner estos atributos
        //porque los comparte con Reserva y Mesa :(

        //string nombreCliente;
        int num_Mesa[2];
        //int numero_Personas;
        string preferencia_Menu;
        //string situacion_Mesa;
        bool finalizado;
};

#endif // PEDIDO_H
