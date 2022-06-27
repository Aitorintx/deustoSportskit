#include "Devolucion.h"
#include "string.h"
#include "LoggerCliente.h"
#include <iostream>

using namespace std;

Devolucion::Devolucion(int idDevolucion, int idCompra, Producto* producto, Cliente* cliente) {
    this->idDevolucion = idDevolucion;
    this->idCompra = idCompra;
    this->producto = producto;
    this->cliente = cliente;
    loggerTxt("Devolucion nueva", cliente->getId());
}

Devolucion::Devolucion(const Devolucion& d) {
    this->idDevolucion = d.idDevolucion;
    this->idCompra = d.idCompra;
    this->producto = d.producto;
    this->cliente = d.cliente;
    loggerTxt("Devolucion nueva", d.getCliente()->getId());
}

Devolucion::~Devolucion() {}


int Devolucion::getIdDevolucion() const {
    return this->idDevolucion;
}

void Devolucion::setIdDevolucion(const int idDevolucion) {
    this->idDevolucion = idDevolucion;
}

int Devolucion::getIdCompra() const {
    return this->idCompra;
}

void Devolucion::setIdCompra(const int idCompra) {
    this->idCompra = idCompra;
}

Producto* Devolucion::getProducto() const {
    return this->producto;
}

void Devolucion::setProducto(Producto* producto) {
    this->producto = producto;
}

Cliente* Devolucion::getCliente() const {
    return this->cliente;
}

void Devolucion::setCliente(Cliente* cliente) {
    this->cliente = cliente;
}


