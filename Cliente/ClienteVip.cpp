#include "ClienteVip.h"
#include "string.h"
#include "LoggerCliente.h"
#include <iostream>

using namespace std;

ClienteVip::ClienteVip(const char* nombre, int id, int tel, const char* correo, const char* dir, const char* contra, const char* nivel): Cliente(nombre,id,tel,correo,dir,contra){
    this->nivel=new char[strlen(nivel) + 1];
    strcpy(this->nivel,nivel);
}

ClienteVip::ClienteVip(const ClienteVip& cv) : Cliente(cv){
    this->nivel=new char[strlen(cv.nivel) + 1];
    strcpy(this->nivel,cv.nivel);
}

ClienteVip::~ClienteVip(){
    delete[] nivel;
}

char* ClienteVip::getNivel() const{
    return this->nivel;
}

void ClienteVip::calculoPrecioFinal(float precio){
    char* nivel = new char[200];
    nivel = this->nivel;
    if(strcmp(nivel,"standar")==0){
        precio=precio*0.95;
        cout<<"Por ser cliente STANDAR tienes un descuento del 5%\nPrecio Final: "<< precio<<endl;
    }else if(strcmp(nivel,"plus")==0){
        precio=precio*0.85;
        cout<<"Por ser cliente PLUS tienes un descuento del 15%\nPrecio Final: "<< precio<<endl;
        
    }

    loggerTxt("Calculado precio final de cliente VIP", this->getId());
}

void ClienteVip::iniciarCliente(Cliente** listaClientes, int num){
    int opcion;
    cout<<"Bienvenido a DeustoSportskit"<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"1. Iniciar Sesión"<<endl;
    cout<<"2. Registrarse"<<endl;
    cout<<"0.Abandonar"<<endl;
    cout<<"¿Qué desea hacer?: ";
    cin>>opcion;
    while(0>opcion | opcion>2){
        cout<<"La opcion introducida no se puede aceptar"<<endl;
        cout<<"-----------------------------------------"<<endl;
        cout<<"1. Iniciar Sesión"<<endl;
        cout<<"2. Registrarse"<<endl;
        cout<<"0.Abandonar"<<endl;
        cout<<"¿Qué desea hacer?: ";
        cin>>opcion;
    };
    if(opcion==0){
        cout<<"Esperemos que vuelvas pronto :)"<<endl;
    }else if(opcion==1){
        iniciarSesion(listaClientes, num);
    }else{
        registrarCliente(listaClientes, num);
    }
}

void ClienteVip::iniciarSesion(Cliente** listaClientes, int num){
    char* contrasena= new char[100];
    char* nombre= new char[100];
    int numero=0;
    
    
    cout<<"Introduce el nombre de usuario:";
    cin>>nombre;
    cout << endl;
    cout<<"Introduce la contrasena:";
    cin>>contrasena;
    cout << endl;
    
    do{
        char* nom=listaClientes[numero]->getNombre();
        char* con= listaClientes[numero]->getContra();
        numero++;
        if(strcmp(contrasena,con)==0 & strcmp(nombre,nom)==0){
            cout<<"Encantado de tenerte aqui otra vez "<< nom << "!"<<endl;
            numero=0;
            break;
        }
        // *****************************************+
        // loggerTxt("Cliente ha iniciado sesion", id)
    }
    while(numero<num);
    if(numero==num){
        cout<<"El nombre de usuario o la contrasena son incorrectas. Por favor intentelo de nuevo"<<endl;
        cout<<"----------------------------------------------------------------------------------"<<endl;
        iniciarSesion(listaClientes,num);
    }
    
}

void ClienteVip::registrarCliente(Cliente** listaClientes,int num){
    int id=listaClientes[num-1]->getId();
    id++;
    char* nombre=new char[100];
    int tel;  
    char* correo=new char[100];
    char* dir=new char[200];
    char* contra=new char[100];
    char* contraRep=new char[100];
    char* aceptar=new char[2];
    char* vip=new char[100];
    cout<<"Introduzca Nombre de Usuario:";
    cin>>nombre;
    cout<<"Introduzca Telefono:";
    cin>>tel;
    cout<<"Introduzca Correo:";
    cin>>correo;
    cout<<"Introduzca Direccion:";
    cin>>dir;
    do{
        cout<<"AVISO! Mientras no sean iguales no podrás seguir!"<<endl;
        cout<<"Introduzca Contrasena:";
        cin>>contra;
        cout<<"Repita Contrasena:";
        cin>>contraRep;
    }while(strcmp(contra,contraRep)!=0);

    do{
        cout<<"Deseas hacerte VIP? S/N:";
        cin>>aceptar;
    }while(strcmp(aceptar,"S")!=0 & strcmp(aceptar,"N")!=0);

    if(strcmp(aceptar,"N")==0){
        Cliente* c=new Cliente(nombre, id, tel, correo, dir, contra);
        num++;
        Cliente** listaCliente=new Cliente*[num];
        for (int i = 0; i < num-1; i++)
        {
            listaCliente[i]=listaClientes[i];
        }
        
        listaCliente[num-1]=c;
        cout<<"Registro Completado con Exito"<<endl;
        cout<<"Muchas gracias por contar con nosotros!"<<endl;
        iniciarCliente(listaCliente,num);
        // *****************************************+
        // loggerTxt("Cliente se ha registrado", id)
    }else if (strcmp(aceptar,"S")==0){
        do{
            cout<<"AVISO! Debera de escribir los nombres tal y como los pone ahí, en caso contrario no podra seguir con el regisro!"<<endl;
            cout<<"Niveles de cliente vip\n-standar(Descuento del 5%)\n-plus(Descuento del 15%)\n Que nivel VIP desea escoger?"<<endl;
            cin>>vip;
        }while(strcmp(vip,"standar")!=0 & strcmp(vip,"plus")!=0);
        
        ClienteVip* cv= new ClienteVip(nombre, id, tel, correo, dir, contra, vip);
        num++;
        Cliente** listaCliente=new Cliente*[num];
        for (int i = 0; i < num-1; i++)
        {
            listaCliente[i]=listaClientes[i];
        }
        listaCliente[num-1]=cv;
        cout<<"Registro Completado con Exito"<<endl;
        cout<<"Muchas gracias por contar con nosotros!"<<endl;
        iniciarCliente(listaCliente,num);
        
        
    }

}
