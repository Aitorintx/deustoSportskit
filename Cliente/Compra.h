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
};
#endif