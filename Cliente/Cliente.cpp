#include "Cliente.h"
#include "string.h"
#include "LoggerCliente.h"
#include <iostream>

using namespace std;

Cliente::Cliente(const char* nombre, int id, int tel, const char* correo, const char* dir, const char* contra){
    this->nombre=new char [strlen(nombre) +1];
    strcpy(this->nombre,nombre);
    this->id=id;
    this->tel=tel;
    this->correo=new char [strlen(correo) +1];
    strcpy(this->correo,correo);
    this->dir=new char [strlen(dir) +1];
    strcpy(this->dir,dir);
    this->contra=new char [strlen(contra) +1];
    strcpy(this->contra,contra);
    loggerTxt("Nuevo cliente registrado", id);
}

Cliente::Cliente(const Cliente& c){
    this->nombre=new char [strlen(c.nombre) +1];
    strcpy(this->nombre,c.nombre);
    this->id=c.id;
    this->tel=c.tel;
    this->correo=new char [strlen(c.correo) +1];
    strcpy(this->correo,c.correo);
    this->dir=new char [strlen(c.dir) +1];
    strcpy(this->dir,c.dir);
    this->contra=new char [strlen(c.contra) +1];
    strcpy(this->contra,c.contra);
    loggerTxt("Nuevo cliente registrado", c.id);
}

Cliente::~Cliente(){
    delete[] nombre;
    delete[] correo;
    delete[] dir;
    delete[] contra;
    loggerTxt("Cliente eliminado", id);
}

char* Cliente::getNombre() const{
    return this->nombre;
}

int Cliente::getId() const{
    return this->id;
}

int Cliente::getTel() const{
    return this->tel;
}

char* Cliente::getCorreo() const {
    return this->correo;
}

char* Cliente::getDir() const{
    return this->dir;
}

char* Cliente::getContra() const{
    return this->contra;
}

void Cliente::calculoPrecioFinal(float precio){
    cout<<"Por ser cliente NO VIP no tienes rebaja en el precio\n Precio Final: "<< precio <<endl;
}


