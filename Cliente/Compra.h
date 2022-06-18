#ifndef COMPRA_H_
#define COMPRA_H_

#include "Producto.h"
#include "ClienteVip.h"
class Compra{
    private:
        int idCompra;
        Producto** listaProductos;
        Cliente* cliente;
        int numProductos;
        float precioTotal;
    public: 
    Compra(int idCompra, Producto** listaProductos, Cliente* cliente, int numProductos);
    Compra(const Compra& c);
    ~Compra();

    int getIdCompra() const;
    Producto** getListaProductos() const;
    Producto* getProducto(int num) const;
    Cliente* getCliente() const;
    int getNumProductos() const;
    float getPrecioTotal() const;
    void setPrecioTotal(float precio);


    void calcularPrecioTotal();

    void static iniciarCliente(Cliente** listaCliente, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC);
    void static iniciarSesion(Cliente** listaCliente, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC);
    void static registrarCliente(Cliente** listaCliente, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC);
    void static pantallaInicio(Cliente** listaClientes, Cliente* c, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC);
    void static imprimirCompras(Cliente** listaClientes, Cliente* c, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC);
    void static realizarCompra(Cliente** listaClientes, Cliente* c, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC);
};
#endif