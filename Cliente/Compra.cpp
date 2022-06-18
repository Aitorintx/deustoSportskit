#include "Compra.h"
#include "string.h"
#include <iostream>

using namespace std;

Compra::Compra(int idCompra, Producto** listaProductos, Cliente* cliente, int numProductos){
    this->idCompra=idCompra;
    this->listaProductos=listaProductos;
    for (int i = 0; i < numProductos; i++)
    {
        this->listaProductos[i]==listaProductos[i];
    }
    this->cliente=cliente;
    this->numProductos=numProductos;
    this->precioTotal=0.0;
}

Compra::Compra(const Compra& c){
    this->idCompra=c.idCompra;
    this->listaProductos=c.listaProductos;
    for (int i = 0; i < c.numProductos; i++)
    {
        this->listaProductos[i]==c.listaProductos[i];
    }
    this->cliente=c.cliente;
    this->numProductos=c.numProductos;
    this->precioTotal=0.0;
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
    
}

void Compra::iniciarCliente(Cliente** listaClientes, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC){
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
        iniciarSesion(listaClientes, num, listaProductos, numP, listaCompras, numC);
    }else{
        registrarCliente(listaClientes, num, listaProductos, numP, listaCompras, numC);
    }
}

void Compra::iniciarSesion(Cliente** listaClientes, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC){
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
        
        if(strcmp(contrasena,con)==0 & strcmp(nombre,nom)==0){
            cout<<"Encantado de tenerte aqui otra vez "<< nom << "!"<<endl;
            Cliente* c= listaClientes[numero];
            pantallaInicio(listaClientes,c,num,listaProductos,numP,listaCompras,numC);
            numero=0;
            break;
        }
        numero++;

    }
    while(numero<num);
    if(numero==num){
        cout<<"El nombre de usuario o la contrasena son incorrectas. Por favor intentelo de nuevo"<<endl;
        cout<<"----------------------------------------------------------------------------------"<<endl;
        iniciarSesion(listaClientes,num, listaProductos, numP, listaCompras, numC);
    }
    
}

void Compra::registrarCliente(Cliente** listaClientes,int num, Producto** productos, int numP, Compra** compras, int numC){
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
        iniciarCliente(listaCliente,num, productos, numP, compras, numC);
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
        iniciarCliente(listaCliente,num, productos, numP, compras, numC);
        
    }

}
void Compra::pantallaInicio(Cliente** listaClientes, Cliente* cliente, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC){
    int opcion;
    char* res=new char[100];
    char* res1=new char[2];
    do{
    cout<<"Sportskit"<<endl;
    cout<<"---------"<<endl;
    cout<<"1.Ver todos los productos de la tienda."<<endl;
    cout<<"2.Hacer una nueva compra."<<endl;
    cout<<"3.Ver las compras hechas."<<endl;
    cout<<"0.Salir."<<endl;
    cout<<"Que desea hacer?";
    cin>> opcion;
    }while (0>opcion | opcion>3); 
    
    if(opcion==0){
        do
        {
            cout<<"Estas seguro que quieres abandonar? S/N"<<endl;
            cin>>res;
        } while (strcmp(res,"S")!=0 & strcmp(res,"N")!=0);
        
        if(strcmp(res,"S")==0){
            Compra::iniciarCliente(listaClientes, num, listaProductos, numP, listaCompras, numC);
        }else{
            Compra::pantallaInicio(listaClientes,cliente,num,listaProductos, numP, listaCompras, numC);
        }
        
    }else if(opcion==1){
        Producto::imprimirProductos(listaProductos,numP);
        do{
            cout<<"Si desea volver a la pantalla de inicio pulse 0: ";
            cin>>res1;
        }while(strcmp(res1,"0")!=0);
        if (strcmp(res1,"0")==0)
        {
            Compra::pantallaInicio(listaClientes,cliente,num,listaProductos, numP, listaCompras, numC);
        }
        
    }else if(opcion==2){
        Producto* p=new Producto(0,"","",0,0,0);
        Producto* prods[]={p};
        int tamanyo=0;
        realizarCompra(listaClientes,cliente,num,listaProductos, numP, listaCompras, numC,prods, tamanyo);
    }else{
        imprimirCompras(listaClientes,cliente,num,listaProductos, numP, listaCompras, numC);
    }
    
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
            Compra::pantallaInicio(listaClientes,cliente,num,listaProductos, numP, listaCompras, numC);
        }
    
}

void Compra::realizarCompra(Cliente** listaClientes, Cliente* cliente, int num, Producto** listaProductos, int numP, Compra** listaCompras, int numC, Producto** prods, int tamanyo){
    int res;
    char* res1=new char[100];
    int ultId= listaCompras[numC-1]->getIdCompra();
    Producto** ps;
    Producto::imprimirProductos(listaProductos,numP);
    cout<<"Inserta el ID del producto que desees comprar:";
    cin>>res;
    for (int i = 0; i < numP; i++)
    {
        if (listaProductos[i]->getId()==res)
        {
            tamanyo++;
            if(tamanyo==1){
                
                prods[tamanyo-1]->setId(listaProductos[i]->getId());
                prods[tamanyo-1]->setNombre(listaProductos[i]->getNombre());
                prods[tamanyo-1]->setTipo(listaProductos[i]->getTipo());
                prods[tamanyo-1]->setPrecio(listaProductos[i]->getPrecio());
                prods[tamanyo-1]->setStock(listaProductos[i]->getStock());
                prods[tamanyo-1]->setTalla(listaProductos[i]->getTalla());
            }else{
                ps=new Producto*[tamanyo];
                for (int j = 0; j < tamanyo-1; j++)
                {
                    ps[j]=prods[j];
                }
                ps[tamanyo-1]=listaProductos[i]; 
            }
            
        }
    }
    if(tamanyo==0){
        cout<<"Compra fallida"<<endl;
        Compra::pantallaInicio(listaClientes,cliente,num,listaProductos, numP, listaCompras, numC);
    }else{
        do{
            cout<<"Deseas anyadir un nuevo producto a la compra? S/N";
            cin>>res1;
        }while(strcmp(res1,"S")!=0 & strcmp(res1,"N")!=0);
        
        if(strcmp(res1,"S")==0 & tamanyo==1){
            realizarCompra(listaClientes,cliente, num, listaProductos, numP, listaCompras, numC,prods, tamanyo);
        }else if(strcmp(res1,"S")==0 & tamanyo!=1){
            realizarCompra(listaClientes,cliente, num, listaProductos, numP, listaCompras, numC,ps, tamanyo);
        }else if(strcmp(res1,"N")==0 & tamanyo==1){
            numC++;
            Compra** compras=new Compra*[numC];
            for (int i = 0; i < numC-1; i++)
            {
                compras[i]=listaCompras[i];
            }
            
            int id=ultId++;
            Compra* c=new Compra(id,prods,cliente,tamanyo);
            compras[numC-1]=c;
            cout<<"Compra realizada con exito. Muchas gracias!"<<endl;
            Compra::pantallaInicio(listaClientes,cliente,num,listaProductos, numP, compras, numC);
            
        }else{
            numC++;
            Compra** compras=new Compra*[numC];
            for (int i = 0; i < numC-1; i++)
            {
                compras[i]=listaCompras[i];
            }
            
            int id=ultId++;
            Compra* c=new Compra(id,ps,cliente,tamanyo);
            compras[numC-1]=c;
            cout<<"Compra realizada con exito. Muchas gracias!"<<endl;
            Compra::pantallaInicio(listaClientes,cliente,num,listaProductos, numP, compras, numC);
        }
    }
    
    
   
    

    
    
}