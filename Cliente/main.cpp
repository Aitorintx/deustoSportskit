#include "ClienteVip.h"
#include "Compra.h"
#include <iostream>

using namespace std;

int main()
{
    Producto* p1=new Producto(1, "Chaqueta", "Prenda", 55.20, 20, 38);
    Producto* p2=new Producto(2, "Sneakers", "Calzado", 200.30, 10, 40);

	Cliente* c=new Cliente("Aitor",1,633091217,"aintxaustim@opendeusto.es","hola","12345");
    ClienteVip* cv=new ClienteVip("Sara",2,722,"sara.hernandez@opendeusto.es","hola","234","plus");

    Producto* productos[]={p1,p2};
    Compra* cm=new Compra(1, productos, cv, 2);
    

    cm->calcularPrecioTotal();
    float precio=cm->getPrecioTotal();
    cm->getCliente()->calculoPrecioFinal(precio);
    

    delete p1;
    delete p2;
    delete cv;
    delete c;
    delete cm;
    
    
    

    return 0;
}
