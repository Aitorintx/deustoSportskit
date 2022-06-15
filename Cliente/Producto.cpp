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

