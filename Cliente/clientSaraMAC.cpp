#include "ClienteVip.h"
#include "Compra.h"

#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int s = 0, valread;
struct sockaddr_in serv_addr;
char *hello = "Hello from client";
char buffer[1024] = {0};
char sendBuff[512], recvBuff[512];

using namespace std;


void verProductos() {

	strcpy(sendBuff, "VER PRODUCTOS");
	send(s, sendBuff, strlen(sendBuff), 0);

	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;

	while (strcmp(recvBuff, "Esos son los productos") != 0) {
		recv(s, recvBuff, strlen(recvBuff), 0);
		cout << "Data received: " << recvBuff << endl;
	}

}


void comprar () {

	strcpy(sendBuff, "QUIERO COMPRAR");
	send(s, sendBuff, strlen(sendBuff), 0);


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

	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: [id] " << recvBuff << endl;
	id = atoi(recvBuff);

	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: [nombre] " << recvBuff << endl;
	strcpy(nombre, recvBuff);

	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: [telefono] " << recvBuff << endl;
	telefono = atoi(recvBuff);

	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: [correo] " << recvBuff << endl;
	strcpy(correo, recvBuff);

	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: [direccion] " << recvBuff << endl;
	strcpy(direccion, recvBuff);

	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: [contrasena] " << recvBuff << endl;
	strcpy(contrasena, recvBuff);

	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: [vip] " << recvBuff << endl;
	strcpy(vip, recvBuff);

	// CREAMOS CLIENTES

	Cliente* cliente;
	ClienteVip* clienteVip;
	if (strcmp(vip, "NOVIP") == 0) {
		cliente = new Cliente(nombre, id, telefono, correo, direccion, contrasena);
	} else {
		clienteVip = new ClienteVip (nombre, id, telefono, correo, direccion, contrasena, vip);
	}


	// ***********************
	// EMPEZAMOS CON LA COMPRA
	// ***********************


	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;

	int comprar;
	cin >> comprar;

	sprintf(sendBuff, "%i", comprar);
	send(s, sendBuff, strlen(sendBuff), 0);

	// RECIBIMOS CUANTO CUESTA EL PRODUCTO EN PRINCIPIO O SI NO EXISTE

	float precio;
	recv(s, recvBuff, strlen(recvBuff), 0);

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
		send(s, sendBuff, strlen(sendBuff), 0);


		recv(s, recvBuff, strlen(recvBuff), 0);
		cout << "Data received: " << recvBuff << endl;

	}

}


void funcionComprar () {

	verProductos();

	char respuesta;

	do {

		cout << "¿Te interesa alguno de los productos? (S/N)" << endl;
		cin >> respuesta;

		if (respuesta == 'S') {

			comprar();

		} 
		
	} while (respuesta != 'S');
	
}


void verMisCompras() {

	strcpy(sendBuff, "VER MIS COMPRAS");
	send(s, sendBuff, strlen(sendBuff), 0);

	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;

	if (strcmp(recvBuff, "Todavia no has realizado ninguna compra en sportKit") != 0) {
		while (strcmp(recvBuff, "Esas son tus compras") != 0) {
			recv(s, recvBuff, strlen(recvBuff), 0);
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
		send(s, sendBuff, strlen(sendBuff), 0);
    } else if (respuesta == 2) {
        verMisCompras();
		strcpy(sendBuff, "TERMINAR");
		send(s, sendBuff, strlen(sendBuff), 0);
    } else {
        strcpy(sendBuff, "TERMINAR");
		send(s, sendBuff, strlen(sendBuff), 0);
    }

}


int iniciarSesionCliente() {

	strcpy(sendBuff, "INICIAR CLIENTE");
	send(s, sendBuff, strlen(sendBuff), 0);

	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char correo[60];
	cin >> correo;
	strcpy(sendBuff, correo);
	send(s, sendBuff, strlen(sendBuff), 0);

	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char contrasena[20];
	cin >> contrasena;
	strcpy(sendBuff, contrasena);
	send(s, sendBuff, strlen(sendBuff), 0);

	recv(s, recvBuff, strlen(recvBuff), 0);
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
	send(s, sendBuff, strlen(sendBuff), 0);

	// Nombre
	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char nombre[30];
	cin >> nombre;
	strcpy(sendBuff, nombre);
	send(s, sendBuff, strlen(sendBuff), 0);

	// Telefono
	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	int tel;
	cin >> tel;
	sprintf(sendBuff, "%i", tel);
	send(s, sendBuff, strlen(sendBuff), 0);

	// Correo
	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char correo[60];
	cin >> correo;
	strcpy(sendBuff, correo);
	send(s, sendBuff, strlen(sendBuff), 0);

	// Direccion
	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char dir[50];
	cin >> dir;
	strcpy(sendBuff, dir);
	send(s, sendBuff, strlen(sendBuff), 0);

	// Contrasena
	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char contra[20];
	cin >> contra;
	strcpy(sendBuff, contra);
	send(s, sendBuff, strlen(sendBuff), 0);

	// vip
	recv(s, recvBuff, strlen(recvBuff), 0);
	cout << "Data received: " << recvBuff << endl;
	char deci[2];
	cin >> deci;
	strcpy(sendBuff, deci);
	send(s, sendBuff, strlen(sendBuff), 0);

	if (strcmp(deci, "S") == 0) {
		recv(s, recvBuff, strlen(recvBuff), 0);
		cout << "Data received: " << recvBuff << endl;
		char nivel[15];
		cin >> nivel;
		strcpy(sendBuff, nivel);
		send(s, sendBuff, strlen(sendBuff), 0);
	}
	
	recv(s, recvBuff, strlen(recvBuff), 0);
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
			send(s, sendBuff, strlen(sendBuff), 0);
		} else {
			menuIniciado();
		}
    } else if (respuesta == 2) {
        registrarCliente();
		menuIniciado();
    } else {
        strcpy(sendBuff, "TERMINAR");
		send(s, sendBuff, strlen(sendBuff), 0);
    }

}



int main() {

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	

    //SEND AND RECEIVE

	menuPrincipal();



    return 0;
}
