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
    Cliente*  clientes[]={c,cv};
    Producto* productos[]={p1,p2};
    Producto* producto1[]={p1};
    Producto* producto2[]={p2};
    Compra* cm1=new Compra(1, producto2, c, 1);
    Compra* cm2=new Compra(2, producto1, c, 1);
    Compra* compras[]={cm1,cm2};

    
    Compra::iniciarCliente(clientes,2,productos,2,compras,2);

    delete p1;
    delete p2;
    delete cv;
    delete c;
    delete cm1;
    delete cm2;
    
    
    

    return 0;
}
