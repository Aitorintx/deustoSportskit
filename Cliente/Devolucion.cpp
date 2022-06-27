#include "Devolucion.h"
#include "string.h"
#include "LoggerCliente.h"
#include "Compra.h"
#include "Producto.h"
#include "ClienteVip.h"

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



void Devolucion::imprimirComprasHechas(Compra** compras, int num, Cliente* cliente, Devolucion** listaDevolucion, int numD) {

    int cuantasCom;
    for (int i = 0; i < num; i++) {
        if (compras[i]->getCliente() == cliente) {

            for (int j = 0; j < numD; j++) {
                for (int a = 0; a < compras[i]->getNumProductos(); a++) {

                    if (!(listaDevolucion[j]->getIdCompra() == compras[i]->getIdCompra()) && !(listaDevolucion[j]->getProducto() == compras[i]->getProducto(a)) && !(listaDevolucion[j]->getCliente() == cliente)) {
                        cuantasCom++;
                    }
                }
            }
        }
    }

    int count = 0;
    Compra** comprasHechas = new Compra*[cuantasCom];
    for (int i = 0; i < num; i++) {
        if (compras[i]->getCliente() == cliente) {

            for (int j = 0; j < numD; j++) {
                for (int a = 0; a < compras[i]->getNumProductos(); a++) {

                    if (!(listaDevolucion[j]->getIdCompra() == compras[i]->getIdCompra()) && !(listaDevolucion[j]->getProducto() == compras[i]->getProducto(a)) && !(listaDevolucion[j]->getCliente() == cliente)) {
                        comprasHechas[count] = compras[i];
                        count++;
                    }
                }
            }
        }
    }


    if (cuantasCom == 0) {
        cout << "No has hechos compras hasta hora" << endl;
    } else {

        cout << "Compras hechas hasta ahora en SportsKit:" << endl;
        cout << "----------------------------------------------" << endl;
        for (int i = 0; i < cuantasCom; i++) {
            for (int j = 0; i < comprasHechas[i]->getNumProductos(); j++) {
                cout << "Compra: " << comprasHechas[i]->getIdCompra() << "[" << comprasHechas[i]->getProducto(j)->getId() << ": " << 
                    comprasHechas[i]->getProducto(j)->getNombre() << "] TOTAL: " << comprasHechas[i]->getPrecioTotal() << "€" << endl;
            }
        }
    }

}



void Devolucion::realizarDevolucion(Cliente** listaClientes, Cliente* cliente, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC, Devolucion** listaDevolucion, int numD, Producto** prods, int tamanyo){
    
    int idCompra;
    int idProducto;
    imprimirComprasHechas(listaCompras, numC, cliente, listaDevolucion, numD);

    cout << "Inserta el ID de la compra que desees devolver:";
    cin >> idCompra;

    cout << "Inserta el ID del producto que desees devolver:";
    cin >> idProducto;

    
    
    
}



