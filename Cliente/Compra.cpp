#include "Compra.h"
#include "string.h"
#include "LoggerCliente.h"
#include <iostream>

using namespace std;

Compra::Compra(int idCompra, Producto** listaProductos, Cliente* cliente, int numProductos){
    this->idCompra=idCompra;
    this->listaProductos=listaProductos;
    for (int i = 0; i < numProductos; i++)
    {
        this->listaProductos[i]=listaProductos[i];
    }
    this->cliente=cliente;
    this->numProductos=numProductos;
    this->precioTotal=0.0;
    loggerTxt("Compra nueva", cliente->getId());
}

Compra::Compra(const Compra& c){
    this->idCompra=c.idCompra;
    this->listaProductos=c.listaProductos;
    for (int i = 0; i < c.numProductos; i++)
    {
        this->listaProductos[i]=c.listaProductos[i];
    }
    this->cliente=c.cliente;
    this->numProductos=c.numProductos;
    this->precioTotal=0.0;
    loggerTxt("Compra nueva", c.getCliente()->getId());
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

    loggerTxt("Se ha calculado el precio total de una compra", this->getCliente()->getId());
}




void Compra::imprimirCompras(Cliente** listaClientes, Cliente* cliente, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC){
    int numero=0;
    int indice=1;
    char* res1=new char[100];
    float precio;
    for (int i = 0; i < numC; i++)
    {
        if(listaCompras[i]->getCliente()==cliente){
            int indice2=1;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Compra "<<indice<<":"<<endl;
            for (int j = 0; j < listaCompras[i]->getNumProductos(); j++)
            {
                cout<<"Producto "<<indice2<<": Nombre->"<<listaCompras[i]->getProducto(j)->getNombre()<<" Talla->"<<listaCompras[i]->getProducto(j)->getTalla()<<endl;
                indice2++;
            }
            listaCompras[i]->calcularPrecioTotal();
            precio=listaCompras[i]->getPrecioTotal();
            listaCompras[i]->getCliente()->calculoPrecioFinal(precio);
            indice++; 
            numero++;

            loggerTxt("Se ha imprimido compras", cliente->getId());
        }
    }

    if(numero==0){
        cout<<"Todavia no has realizado ninguna compra"<<endl;
    }

    do{
        cout<<"Si desea volver a la pantalla de inicio pulse 0: ";
        cin>>res1;
    }while(strcmp(res1,"0")!=0);
    if (strcmp(res1,"0")==0)
    {
        
    }
    
}



