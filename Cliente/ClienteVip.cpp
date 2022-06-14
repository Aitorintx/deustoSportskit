#include "ClienteVip.h"
#include "string.h"
#include <iostream>

using namespace std;

ClienteVip::ClienteVip(const char* nombre, int id, int tel, const char* correo, const char* dir, const char* contra, const char* nivel): Cliente(nombre,id,tel,correo,dir,contra){
    this->nivel=new char[strlen(nivel) + 1];
}

ClienteVip::ClienteVip(const ClienteVip& cv) : Cliente(cv){
    this->nivel=new char[strlen(cv.nivel) + 1];
}

ClienteVip::~ClienteVip(){
    delete[] nivel;
}

char* ClienteVip::getNivel() const{
    return this->nivel;
}

void ClienteVip::calculoPrecioFinal(int precio){
    char* nivel = this->nivel;
    if(nivel=="standar"){
        precio=precio*0.95;
        cout<<"Por ser cliente STANDAR tienes un descuento del 5%\nPrecio Final: "<< precio<<endl;
    }else{
        precio=precio*0.85;
        cout<<"Por ser cliente STANDAR tienes un descuento del 15%\nPrecio Final: "<< precio<<endl;
        
    }

}