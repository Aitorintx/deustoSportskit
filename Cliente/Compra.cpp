#include "Compra.h"
#include "string.h"
#include <iostream>

using namespace std;

Compra::Compra(int idCompra, Producto** listaProductos, Cliente* cliente, int numProductos){
    this->idCompra=idCompra;
    this->listaProductos=listaProductos;
    for (int i = 0; i < numProductos; i++)
    {
        this->listaProductos[i]==listaProductos[i];
    }
    this->cliente=cliente;
    this->numProductos=numProductos;
    this->precioTotal=0.0;
}

Compra::Compra(const Compra& c){
    this->idCompra=c.idCompra;
    this->listaProductos=c.listaProductos;
    for (int i = 0; i < c.numProductos; i++)
    {
        this->listaProductos[i]==c.listaProductos[i];
    }
    this->cliente=c.cliente;
    this->numProductos=c.numProductos;
    this->precioTotal=0.0;
}

Compra::~Compra(){
    delete[] listaProductos;
    delete cliente;
}

int Compra::getIdCompra() const{
    return this->idCompra;
}

Producto** Compra::getListaProductos() const{
    return this->listaProductos;
}

Producto* Compra::getProducto(int num) const{
    if(num<this->numProductos){
        return this->listaProductos[num];
    }
}

Cliente* Compra::getCliente() const{
    return this->cliente;
}

int Compra::getNumProductos() const{
    return this->numProductos;
}

float Compra::getPrecioTotal() const{
    return this->precioTotal;
}

void Compra::setPrecioTotal(float precio){
    this->precioTotal=precio;
}

void Compra::calcularPrecioTotal(){
    float precio=0.0;
    for (int i = 0; i < Compra::getNumProductos() ; i++)
    {
        precio+=Compra::getProducto(i)->getPrecio();
        
    }
    Compra::setPrecioTotal(precio);
    
}