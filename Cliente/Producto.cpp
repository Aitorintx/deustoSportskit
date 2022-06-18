#include "Producto.h"
#include "string.h"
#include <iostream>

using namespace std;

Producto::Producto(int id, const char* nombre, const char* tipo, float precio,int stock, int talla){
    this->id=id;
    this->nombre=new char[strlen(nombre) + 1];
    strcpy(this->nombre,nombre);
    this->tipo= new char[strlen(tipo) + 1];
    strcpy(this->tipo,tipo);
    this->precio=precio;
    this->stock=stock;
    this->talla=talla;
}

Producto::Producto(const Producto& p){
    this->id=p.id;
    this->nombre=new char[strlen(p.nombre) + 1];
    strcpy(this->nombre,p.nombre);
    this->tipo= new char[strlen(p.tipo) + 1];
    strcpy(this->tipo,p.tipo);
    this->precio=p.precio;
    this->stock=p.stock;
    this->talla=p.talla;
}

Producto::~Producto(){
    delete[] nombre;
    delete[] tipo;
}

int Producto::getId() const{
    return this->id;
}

char* Producto::getNombre() const{
    return this->nombre;
}

char* Producto::getTipo() const{
    return this->tipo;
}

float Producto::getPrecio() const{
    return this->precio;
}

int Producto::getStock() const{
    return this->stock;
}

int Producto::getTalla() const{
    return this->talla;
}

void Producto::setId(int id){
    this->id=id;
}

void Producto::setNombre(char* nombre){
    this->nombre=nombre;
}
void Producto::setTipo(char* tipo){
    if(strcmp(tipo,"Prenda")==0 | strcmp(tipo,"Calzado")==0){
        this->tipo=tipo;
    }
}
void Producto::setPrecio(float precio){
    this->precio=precio;
}
void Producto::setStock(int stock){
    this->stock=stock;
}
void Producto::setTalla(int talla){
    this->talla=talla;
}


void Producto::imprimirProductos(Producto** productos, int num){
    cout<<"Productos existentes ahora mismo en SportsKit:"<<endl;
    cout<<"----------------------------------------------"<<endl;
    cout<<"Seccion Prendas:"<<endl;
    for (int i = 0; i < num; i++)
    {
        if(strcmp(productos[i]->getTipo(),"Prenda")){
            cout<<"ID: "<<productos[i]->getId()<<" Nombre: "<<productos[i]->getNombre()<<" Talla: "<<productos[i]->getTalla()<<endl;
            cout<<"      Precio: "<<productos[i]->getPrecio()<<"\n"<<endl;
        }
    }
    cout<<"Seccion Calzado:"<<endl;
    for (int i = 0; i < num; i++)
    {
        if(strcmp(productos[i]->getTipo(),"Calzado")){
            cout<<"ID: "<<productos[i]->getId()<<" Nombre: "<<productos[i]->getNombre()<<" Talla: "<<productos[i]->getTalla()<<endl;
            cout<<"      Precio: "<<productos[i]->getPrecio()<<"\n"<<endl;
        }
    }
}

