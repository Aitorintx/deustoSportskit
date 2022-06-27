#ifndef DEVOLUCION_H_
#define DEVOLUCION_H_

#include "Producto.h"
#include "ClienteVip.h"
#include "Compra.h"

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

        void imprimirComprasHechas(Compra** compras, int num, Cliente* cliente, Devolucion** listaDevolucion, int numD);
        void realizarDevolucion(Cliente** listaClientes, Cliente* cliente, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC, Devolucion** listaDevolucion, int numD, Producto** prods, int tamanyo);

};


#endif

