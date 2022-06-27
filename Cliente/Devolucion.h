#ifndef DEVOLUCION_H_
#define DEVOLUCION_H_

#include "Producto.h"
#include "ClienteVip.h"

class Devolucion {
    private:
        int idDevolucion;
        int idCompra;
        Producto* producto;
        Cliente* cliente;

    public: 
        Devolucion(int idDevolucion, int idCompra, Producto* producto, Cliente* cliente);
        Devolucion(const Devolucion& d);
        ~Devolucion();

        int getIdDevolucion() const;
        void setIdDevolucion(const int idDevolucion);
        int getIdCompra() const;
        void setIdCompra(const int idCompra);
        Producto* getProducto() const;
        void setProducto(Producto* producto);
        Cliente* getCliente() const;
        void setCliente(Cliente* cliente);

};


#endif

