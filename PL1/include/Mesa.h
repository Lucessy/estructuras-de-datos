#ifndef MESA_H
#define MESA_H


class Mesa
{
    public:
        Mesa();
        Mesa(int num_mesa,int capacidad,string situacion_Mesa);
        virtual ~Mesa();
        int get_num_mesa();
        int get_capacidad();
        string get_situacion_Mesa();

    protected:

    private:
        int num_mesa;
        int capacidad;
        string situacion_Mesa;
};

#endif // MESA_H
