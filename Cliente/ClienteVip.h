#ifndef CLIENTEVIP_H_
#define CLIENTEVIP_H_

#include "Cliente.h"

class ClienteVip : public Cliente
{
    private:
    char* nivel;
    public: 
    ClienteVip(const char* nombre, int id, int tel, const char* correo, const char* dir, const char* contra, const char* nivel);
    ClienteVip(const ClienteVip& cv);
    virtual ~ClienteVip();

    char* getNivel() const;
    virtual float calculoPrecioFinal(float precio);

    void static iniciarCliente(Cliente** listaCliente, int num);
    void static iniciarSesion(Cliente** listaCliente, int num);
    void static registrarCliente(Cliente** listaCliente, int num);
    

};
#endif