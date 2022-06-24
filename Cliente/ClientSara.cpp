// Client side C/C++ program to demonstrate Socket programming
#include "ClienteVip.h"
#include "Cliente.h"
#include "Compra.h"

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080


char sendBuff[512], recvBuff[512];
int s = 0, valread;
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

int numComprasReal(){
	strcpy(sendBuff, "Quiero el numero Real de Compras");
	send(s, sendBuff, sizeof(sendBuff), 0);
	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout<<"Data received: " << recvBuff<<endl;

	char* nRC;
	nRC = new char[20];
	int nRealC;
	strcpy(nRC, recvBuff);
	nRealC = atoi(nRC);
	return nRealC;
}

Compra** rellenarListaCompra(){
    int numeroCompras=numCompras();
    
	int listaFalsa[3][numeroCompras];
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

			strcpy(sendBuff, "Quiero el ID del Producto");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* idCP;
			idCP = new char[20];
			int idCompraP;
			strcpy(idCP, recvBuff);
			idCompraP = atoi(idCP);

			strcpy(sendBuff, "Quiero el ID del Comprador");
			send(s, sendBuff, sizeof(sendBuff), 0);
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout<<"Data received: " << recvBuff<<endl;

			char* idCC;
			idCC = new char[20];
			int idCompraC;
			strcpy(idCC, recvBuff);
			idCompraC = atoi(idCC);
			
            
			listaFalsa[0][i]=idCompra;
			listaFalsa[1][i]=idCompraP;
			listaFalsa[2][i]=idCompraC;
        }
		strcpy(sendBuff, "Quiero el MAX ID de la Compra");
		send(s, sendBuff, sizeof(sendBuff), 0);
		recv(s, recvBuff, sizeof(recvBuff), 0);
		cout<<"Data received: " << recvBuff<<endl;

		char* idMC;
		idMC = new char[20];
		int idMAXC;
		strcpy(idMC, recvBuff);
		idMAXC = atoi(idMC);


		
		int nRealC=numComprasReal();
		int contador=0;
		int contador1=0;
		int id;
		int numCl=numClientes() + numClientesVIP();
		int numP=numProductos();
		Cliente** listaClientes=rellenarListaClientes();
		Producto** listaProducto=rellenarListaProductos();
		Cliente* c;

		Compra** listaCompras=new Compra*[nRealC];
		
		
			for (int i = 0; i < idMAXC; i++)
			{
				for (int j = 0; j < numeroCompras; j++)
				{
					if(listaFalsa[1][j]==i){
					contador++;
					}
				}
				Producto** listaProds=new Producto*[contador];
				for (int j = 0; j < contador; j++)
				{
					for (int k = 0; k < numeroCompras; k++)
					{
						if(listaFalsa[1][k]==i){
							for (int l = 0; l < numP; l++)
							{
								if(listaFalsa[2][k]==listaProducto[l]->getId()){
									listaProds[j]=listaProducto[l];
								}
							}
							for(int l=0; l<numCl;l++){
								if(listaFalsa[3][k]==listaClientes[l]->getId()){
									c=listaClientes[l];
								}
							}
						
						}
					}
				
				}
			
				Compra* compra=new Compra(i,listaProds,c,contador);
				listaCompras[contador1]=compra;
				contador1++;
			}
	
	}
        
}


int main() {
    
	struct sockaddr_in serv_addr;
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout <<"\n Socket creation error " << endl;
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
		cout << "\nInvalid address/ Address not supported " << endl;
		return -1;
	}

	if (connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		cout << "\nConnection Failed" << endl;
		return -1;
	}

	
    Cliente** listaClientes = rellenarListaClientes();
    Producto** listaProductos = rellenarListaProductos();
    Compra** listaCompra = rellenarListaCompra();
    int numCl = numClientes() + numClientesVIP();
    int numP = numProductos();
    int numC = numComprasReal();

	Compra::iniciarCliente(listaClientes,numCl,listaProductos,numP,listaCompra,numC);
	
    strcpy(sendBuff, "Terminar");
	send(s, sendBuff, sizeof(sendBuff), 0);

	exit(1);

}