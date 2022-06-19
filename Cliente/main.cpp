#include "ClienteVip.h"
#include "Compra.h"
#include <iostream>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

WSADATA wsaData;
SOCKET s;
struct sockaddr_in server;
char sendBuff[512], recvBuff[512];
using namespace std;

int numClientes(){
    int numeroClientes;
    

    strcpy(sendBuff, "Numero de Clientes");
	send(s, sendBuff, sizeof(sendBuff), 0);
    recv(s, recvBuff, sizeof(recvBuff), 0);
	cout<<"Data received: " << recvBuff<<endl;
	numeroClientes = atol(recvBuff);
    return numeroClientes;
}
int numClientesVIP(){
    int numeroClientesVip;
    strcpy(sendBuff, "Numero de Clientes VIP");
	send(s, sendBuff, sizeof(sendBuff), 0);
    recv(s, recvBuff, sizeof(recvBuff), 0);
	cout<<"Data received: " << recvBuff<<endl;
	numeroClientesVip = atol(recvBuff);
}
Cliente** rellenarListaClientes(){
    int numeroClientes=numClientes();
    int numeroClientesVip=numClientesVIP();
    Cliente** listaClientes=new Cliente*[numeroClientes + numeroClientesVip];
    if(numeroClientes>0){
        for (int i = 0; i < numeroClientes; i++)
        {
            strcpy(sendBuff, "Quiero el ID de los Clientes");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* idC;
			idC = new char[20];
			int idCliente;
			strcpy(idC, recvBuff);
			idCliente = atoi(idC);

            strcpy(sendBuff, "Quiero Los Nombres de los Clientes");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* nombre;
			nombre = new char[20];
			strcpy(nombre, recvBuff);

            strcpy(sendBuff, "Quiero el telefono de los clientes");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* tel;
			tel = new char[20];
			int telefono;
			strcpy(tel, recvBuff);
			telefono = atoi(tel);

            strcpy(sendBuff, "Quiero los CORREOS de los Clientes");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* correo;
			correo = new char[20];
			strcpy(correo, recvBuff);


            strcpy(sendBuff, "Quiero las direcciones de los Clientes");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* dir;
			dir = new char[20];
			strcpy(dir, recvBuff);

            strcpy(sendBuff, "Quiero Las Contraseñas de los Clientes");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* contra;
			contra = new char[20];
			strcpy(contra, recvBuff);
            Cliente* c=new Cliente(nombre,idCliente,telefono,correo,dir,contra);
            listaClientes[i]=c;
        }
    }

    if(numeroClientesVip>0){
            for (int i = numeroClientes; i < numeroClientesVip; i++)
        {
            strcpy(sendBuff, "Quiero el ID de los Clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* idC;
			idC = new char[20];
			int idCliente;
			strcpy(idC, recvBuff);
			idCliente = atoi(idC);

            strcpy(sendBuff, "Quiero Los Nombres de los Clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* nombre;
			nombre = new char[20];
			strcpy(nombre, recvBuff);

            strcpy(sendBuff, "Quiero el telefono de los clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* tel;
			tel = new char[20];
			int telefono;
			strcpy(tel, recvBuff);
			telefono = atoi(tel);

            strcpy(sendBuff, "Quiero los CORREOS de los Clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* correo;
			correo = new char[20];
			strcpy(correo, recvBuff);


            strcpy(sendBuff, "Quiero las direcciones de los Clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* dir;
			dir = new char[20];
			strcpy(dir, recvBuff);

            strcpy(sendBuff, "Quiero Las Contraseñas de los Clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* contra;
			contra = new char[20];
			strcpy(contra, recvBuff);

            strcpy(sendBuff, "Quiero Los Niveles de los Clientes VIP");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* nivel;
			nivel = new char[20];
			strcpy(nivel, recvBuff);
            ClienteVip* cv=new ClienteVip(nombre,idCliente,telefono,correo,dir,contra,nivel);
            listaClientes[i]=cv;
        }
    }
    return listaClientes;
}
int numProductos(){
    int numeroProductos;

    strcpy(sendBuff, "Numero de Productos");
	send(s, sendBuff, sizeof(sendBuff), 0);
    recv(s, recvBuff, sizeof(recvBuff), 0);
	cout<<"Data received: " << recvBuff<<endl;
	numeroProductos = atol(recvBuff);
    return numeroProductos;
}

Producto** rellenarListaProductos(){
    int numeroProductos=numProductos();
    Producto** listaProductos=new Producto*[numeroProductos];

    if(numeroProductos>0){
        for (int i = 0; i < numeroProductos; i++)
        {
            strcpy(sendBuff, "Quiero el ID de los Productos");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* idP;
			idP = new char[20];
			int idProd;
			strcpy(idP, recvBuff);
			idProd = atoi(idP);

            strcpy(sendBuff, "Quiero el Nombre de los Productos");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

            char* nombre;
            nombre=new char[20];
            strcpy(nombre,recvBuff);

            strcpy(sendBuff, "Quiero el Tipo de los Productos");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

            char* tipo;
            tipo=new char[20];
            strcpy(tipo,recvBuff);

            strcpy(sendBuff, "Quiero el precio de los Productos");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* prec;
			prec = new char[20];
			float precio;
			strcpy(prec, recvBuff);
			precio = atoi(prec);

            strcpy(sendBuff, "Quiero el Stock de los Productos");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* st;
			st = new char[20];
			int stock;
			strcpy(st, recvBuff);
			stock = atoi(st);

            strcpy(sendBuff, "Quiero la talla de los Productos");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* talla;
			talla = new char[20];
			int Talla;
			strcpy(talla, recvBuff);
			Talla = atoi(talla);

            Producto* p=new Producto(idProd,nombre,tipo,precio,stock,Talla);
            listaProductos[i]=p;

        }
        
    }
    return listaProductos;
}

int numCompras(){
    int numeroCompras;
    strcpy(sendBuff, "Numero de Compras");
	send(s, sendBuff, sizeof(sendBuff), 0);
    recv(s, recvBuff, sizeof(recvBuff), 0);
	cout<<"Data received: " << recvBuff<<endl;
	numeroCompras = atol(recvBuff);
    return numeroCompras;
}

Compra** rellenarListaCompra(){
    int numeroCompras=numCompras();
    Compra** listaCompras=new Compra*[numeroCompras];
    if(numeroCompras>0){
        for (int i = 0; i < numeroCompras; i++)
        {
            strcpy(sendBuff, "Quiero el ID de las Compras");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* idC;
			idC = new char[20];
			int idCompra;
			strcpy(idC, recvBuff);
			idCompra = atoi(idC);

            int numProds;
            Producto** listaProds=new Producto*[numProds];
            strcpy(sendBuff, "Numero de Productos en Compras");
	        send(s, sendBuff, sizeof(sendBuff), 0);
            recv(s, recvBuff, sizeof(recvBuff), 0);
	        cout<<"Data received: " << recvBuff<<endl;
	        numProds = atol(recvBuff);
            if(numProds>0){
                for (int j = 0; j < numProds; j++)
                {
                    strcpy(sendBuff, "Quiero el ID de los Productos en Compras");
                    send(s, sendBuff, sizeof(sendBuff), 0);
                    recv(s, recvBuff, sizeof(recvBuff), 0);
                    cout<<"Data received: " << recvBuff<<endl;

                    char* idP;
                    idP = new char[20];
                    int idProd;
                    strcpy(idP, recvBuff);
                    idProd = atoi(idP);

                    strcpy(sendBuff, "Quiero el Nombre de los Productos en Compras");
                    send(s, sendBuff, sizeof(sendBuff), 0);
                    recv(s, recvBuff, sizeof(recvBuff), 0);
                    cout<<"Data received: " << recvBuff<<endl;

                    char* nombre;
                    nombre=new char[20];
                    strcpy(nombre,recvBuff);

                    strcpy(sendBuff, "Quiero el Tipo de los Productos en Compras");
                    send(s, sendBuff, sizeof(sendBuff), 0);
                    recv(s, recvBuff, sizeof(recvBuff), 0);
                    cout<<"Data received: " << recvBuff<<endl;

                    char* tipo;
                    tipo=new char[20];
                    strcpy(tipo,recvBuff);

                    strcpy(sendBuff, "Quiero el precio de los Productos en Compras");
                    send(s, sendBuff, sizeof(sendBuff), 0);
                    recv(s, recvBuff, sizeof(recvBuff), 0);
                    cout<<"Data received: " << recvBuff<<endl;

                    char* prec;
                    prec = new char[20];
                    float precio;
                    strcpy(prec, recvBuff);
                    precio = atoi(prec);

                    strcpy(sendBuff, "Quiero el Stock de los Productos en Compras");
                    send(s, sendBuff, sizeof(sendBuff), 0);
                    recv(s, recvBuff, sizeof(recvBuff), 0);
                    cout<<"Data received: " << recvBuff<<endl;

                    char* st;
                    st = new char[20];
                    int stock;
                    strcpy(st, recvBuff);
                    stock = atoi(st);

                    strcpy(sendBuff, "Quiero la talla de los Productos en Compras");
                    send(s, sendBuff, sizeof(sendBuff), 0);
                    recv(s, recvBuff, sizeof(recvBuff), 0);
                    cout<<"Data received: " << recvBuff<<endl;

                    char* talla;
                    talla = new char[20];
                    int Talla;
                    strcpy(talla, recvBuff);
                    Talla = atoi(talla);

                    Producto* p=new Producto(idProd,nombre,tipo,precio,stock,Talla);
                    listaProds[i]=p;
                }
            }

            Cliente* cl;

            strcpy(sendBuff, "Quiero el precio de las Compras");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* prec;
			prec = new char[20];
			float precio;
			strcpy(prec, recvBuff);
			precio = atoi(prec);
            
            Compra* c=new Compra(idCompra,listaProds,cl,numProds);
            c->setPrecioTotal(precio);
            listaCompras[i]=c;
            

        }
        
    }
}

int main()
{
    

	cout<<"Initialising Winsock..."<<endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout<<"Failed. Error Code :"<< WSAGetLastError()<<endl;
		return -1;
	}

	cout<<"Initialised."<<endl;

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout<<"Could not create socket :"<<WSAGetLastError()<<endl;
		WSACleanup();
		return -1;
	}

	cout<<"Socket created."<<endl;

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		cout<<"Connection error: "<< WSAGetLastError()<<endl;
		closesocket(s);
		WSACleanup();
		return -1;
	}

	cout<<"Connection stablished with: "<< inet_ntoa(server.sin_addr)<<
			ntohs(server.sin_port)<< endl;
            
    //Recibir y mandar info

    Cliente** listaClientes=rellenarListaClientes();
    Producto** listaProductos=rellenarListaProductos();
    Compra** listaCompra=rellenarListaCompra();
    int numCl=numClientes() + numClientesVIP();
    int numP=numProductos();
    int numC=numCompras();
  
    
	

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

    
	Compra::iniciarCliente(listaClientes,numCl,listaProductos,numP,listaCompra,numC);
	
    

    delete p1;
    delete p2;
    delete cv;
    delete c;
    delete cm1;
    delete cm2;
    
    
    

    return 0;
}
