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


void verProductos() {

	strcpy(sendBuff, "VER PRODUCTOS");
	send(s, sendBuff, sizeof(sendBuff), 0);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;

	while (strcmp(recvBuff, "Esos son los productos") != 0) {
		recv(s, recvBuff, sizeof(recvBuff), 0);
		cout << "Data received: " << recvBuff << endl;
	}

}


void comprar () {

	strcpy(sendBuff, "QUIERO COMPRAR");
	send(s, sendBuff, sizeof(sendBuff), 0);


	// ***********************
	// RECIBIR EL CLIENTE DATO A DATO
	// ***********************

	int id;
	char* nombre = new char[30];
	int telefono;
	char* correo = new char[60];
	char* direccion = new char[50];
	char* contrasena = new char[20];
	char* vip = new char[15];

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: [id] " << recvBuff << endl;
	id = atoi(recvBuff);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: [nombre] " << recvBuff << endl;
	strcpy(nombre, recvBuff);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: [telefono] " << recvBuff << endl;
	telefono = atoi(recvBuff);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: [correo] " << recvBuff << endl;
	strcpy(correo, recvBuff);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: [direccion] " << recvBuff << endl;
	strcpy(direccion, recvBuff);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: [contrasena] " << recvBuff << endl;
	strcpy(contrasena, recvBuff);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: [vip] " << recvBuff << endl;
	strcpy(vip, recvBuff);

	// CREAMOS CLIENTES

	Cliente* cliente;
	ClienteVip* clienteVip;
	if (strcmp(vip, "NOVIP") == 0) {
		cliente = new Cliente (nombre, id, telefono, correo, direccion, contrasena);
	} else {
		clienteVip = new ClienteVip (nombre, id, telefono, correo, direccion, contrasena, vip);
	}


	// ***********************
	// EMPEZAMOS CON LA COMPRA
	// ***********************


	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;

	int comprar;
	cin >> comprar;

	sprintf(sendBuff, "%i", comprar);
	send(s, sendBuff, sizeof(sendBuff), 0);

	// RECIBIMOS CUANTO CUESTA EL PRODUCTO EN PRINCIPIO O SI NO EXISTE

	float precio;
	recv(s, recvBuff, sizeof(recvBuff), 0);

	if (strcmp(recvBuff, "No existe este producto") == 0) {

		cout << "Data received: " << recvBuff << endl;

	} else {
 
		cout << "Data received: [PRECIO] " << recvBuff << endl;
		precio = atoi(recvBuff);


		// ********************************
		// MANDAR EL PRECIO CON EL METODO DE HERENCIA
		// *******************************+

		if (strcmp(vip, "NOVIP") == 0) {
			precio = cliente->calculoPrecioFinal(precio);
		} else {
			precio = clienteVip->calculoPrecioFinal(precio);
		}

		sprintf(sendBuff, "%i", precio);
		send(s, sendBuff, sizeof(sendBuff), 0);


		recv(s, recvBuff, sizeof(recvBuff), 0);
		cout << "Data received: " << recvBuff << endl;

	}

}


void funcionComprar () {

	verProductos();

	char respuesta;

	do {

		cout << "??Te interesa alguno de los productos? (S/N)" << endl;
		cin >> respuesta;

		if (respuesta == 'S') {

			comprar();

		} 
		
	} while (respuesta != 'S');
	
}


void verMisCompras() {

	strcpy(sendBuff, "VER MIS COMPRAS");
	send(s, sendBuff, sizeof(sendBuff), 0);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;

	if (strcmp(recvBuff, "Todavia no has realizado ninguna compra en sportKit") != 0) {
		while (strcmp(recvBuff, "Esas son tus compras") != 0) {
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout << "Data received: " << recvBuff << endl;
		}
	}

}


void menuIniciado() {

	int respuesta;

	cout << "\n" << endl;
    cout << "- BIENVENIDO A SPORTKIT -" << endl;
    cout << "-------------------------" << endl;
    cout << "1. Comprar" << endl;
    cout << "2. Ver mis compras" << endl;
    cout << "0. Salir" << endl;
    cout << "\n" << endl;
    cout << "Introduzca opcion" << endl;

    cin >> respuesta;

	if (respuesta == 1) {
		funcionComprar();
		strcpy(sendBuff, "TERMINAR");
		send(s, sendBuff, sizeof(sendBuff), 0);
    } else if (respuesta == 2) {
        verMisCompras();
		strcpy(sendBuff, "TERMINAR");
		send(s, sendBuff, sizeof(sendBuff), 0);
    } else {
        strcpy(sendBuff, "TERMINAR");
		send(s, sendBuff, sizeof(sendBuff), 0);
    }

}


int iniciarSesionCliente() {

	strcpy(sendBuff, "INICIAR CLIENTE");
	send(s, sendBuff, sizeof(sendBuff), 0);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char correo[60];
	cin >> correo;
	strcpy(sendBuff, correo);
	send(s, sendBuff, sizeof(sendBuff), 0);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char contrasena[20];
	cin >> contrasena;
	strcpy(sendBuff, contrasena);
	send(s, sendBuff, sizeof(sendBuff), 0);

	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;

	int answer;
	if (strcmp(recvBuff, "ERROR") == 0) {
		answer = 0;
	} else {
		answer = 1;
	}

	return answer;

}


void registrarCliente() {

	strcpy(sendBuff, "REGISTRAR CLIENTE");
	send(s, sendBuff, sizeof(sendBuff), 0);

	// Nombre
	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char nombre[30];
	cin >> nombre;
	strcpy(sendBuff, nombre);
	send(s, sendBuff, sizeof(sendBuff), 0);

	// Telefono
	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	int tel;
	cin >> tel;
	sprintf(sendBuff, "%i", tel);
	send(s, sendBuff, sizeof(sendBuff), 0);

	// Correo
	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char correo[60];
	cin >> correo;
	strcpy(sendBuff, correo);
	send(s, sendBuff, sizeof(sendBuff), 0);

	// Direccion
	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char dir[50];
	cin >> dir;
	strcpy(sendBuff, dir);
	send(s, sendBuff, sizeof(sendBuff), 0);

	// Contrasena
	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char contra[20];
	cin >> contra;
	strcpy(sendBuff, contra);
	send(s, sendBuff, sizeof(sendBuff), 0);

	// vip
	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char deci[2];
	cin >> deci;
	strcpy(sendBuff, deci);
	send(s, sendBuff, sizeof(sendBuff), 0);

	if (strcmp(deci, "S") == 0) {
		recv(s, recvBuff, sizeof(recvBuff), 0);
		cout << "Data received: " << recvBuff << endl;
		char nivel[15];
		cin >> nivel;
		strcpy(sendBuff, nivel);
		send(s, sendBuff, sizeof(sendBuff), 0);
	}
	
	recv(s, recvBuff, sizeof(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	

}


void menuPrincipal() {
    
    int respuesta;

	cout << "----------------------" << endl;
    cout << "------ SPORTKIT ------" << endl;
    cout << "----------------------" << endl;
    cout << "1. Iniciar sesion" << endl;
    cout << "2. Registrarse" << endl;
    cout << "0. Salir" << endl;
    cout << "\n" << endl;
    cout << "Introduzca opcion" << endl;

    cin >> respuesta;

    if (respuesta == 1) {
        int seguir = iniciarSesionCliente();
		if (seguir == 0) {
			strcpy(sendBuff, "TERMINAR");
			send(s, sendBuff, sizeof(sendBuff), 0);
		} else {
			menuIniciado();
		}
    } else if (respuesta == 2) {
        registrarCliente();
		menuIniciado();
    } else {
        strcpy(sendBuff, "TERMINAR");
		send(s, sendBuff, sizeof(sendBuff), 0);
    }

}



int main() {

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

	cout << "Connection stablished with: " << inet_ntoa(server.sin_addr) << ntohs(server.sin_port) << endl;
            
	

    //SEND AND RECEIVE

	menuPrincipal();

	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();


    return 0;
}
