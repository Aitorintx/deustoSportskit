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
    virtual void calculoPrecioFinal(int precio);

};
#endif