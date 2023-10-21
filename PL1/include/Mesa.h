#ifndef MESA_H
#define MESA_H


class Mesa
{
    public:
        Mesa();
        Mesa(int numMesa,int capacidad,string situacionMesa);
        virtual ~Mesa();
        int getNumMesa();
        int getCapacidad();
        string getSituacionMesa();

    protected:

    private:
        int numMesa;
        int capacidad;
        string situacionMesa;
};

#endif // MESA_H
