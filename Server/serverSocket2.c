#include "BaseDatos.h"
#include "Productos.h"
#include "sqlite3.h"
#include "LoggerBD.h"

#include <winsock2.h>
#include <stdio.h>
#include <stdbool.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000


WSADATA wsaData;
SOCKET conn_socket;
SOCKET comm_socket;
struct sockaddr_in server;
struct sockaddr_in client;
char sendBuff[512], recvBuff[512];


char** iniciarCliente (sqlite3 *db) {

	char** infoCliente = (char**)malloc(sizeof(char*)*3);
	infoCliente[0] = (char*)malloc(sizeof(char)*60);
	infoCliente[1] = (char*)malloc(sizeof(char)*20);
	infoCliente[2] = (char*)malloc(sizeof(char)*6);
    
    strcpy(sendBuff, "Correo: ");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);

    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: [CORREO] %s \n", recvBuff);
	strcpy(infoCliente[0], recvBuff);

	strcpy(sendBuff, "Contrasena: ");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);

    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: [CONTRASENA] %s \n", recvBuff);
	strcpy(infoCliente[1], recvBuff);

	bool existe = existeCompradorIniciar(db, infoCliente[0], infoCliente[1]);
	if (existe == false) {
		strcpy(infoCliente[2], "NADA");
	} else {
		bool tipo = obtenerTipoCompradorCorreo(db, infoCliente[0]);
		if (tipo == false) {
			strcpy(infoCliente[2], "NOVIP");
		} else {
			strcpy(infoCliente[2], "VIP");
		}
	}

    return infoCliente;
}


char** registrarCliente (sqlite3 *db) {

	char** infoCliente = (char**)malloc(sizeof(char*)*7);
	infoCliente[0] = (char*)malloc(sizeof(char)*10);		// id
	infoCliente[1] = (char*)malloc(sizeof(char)*30);		// nombre
	infoCliente[2] = (char*)malloc(sizeof(char)*10);		// telefono
	infoCliente[3] = (char*)malloc(sizeof(char)*60);		// correo
	infoCliente[4] = (char*)malloc(sizeof(char)*50);		// direccion
	infoCliente[5] = (char*)malloc(sizeof(char)*20);		// contrasena
	infoCliente[6] = (char*)malloc(sizeof(char)*15);		// nivel

	int id = maxIdComprador (db);
	id++;
	sprintf(infoCliente[0], "%i", id);
    
	// Nombre
    strcpy(sendBuff, "Nombre: ");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);

    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: [NOMBRE] %s \n", recvBuff);
	strcpy(infoCliente[1], recvBuff);

	// Telefono
	strcpy(sendBuff, "Telefono: ");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);

    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: [TELEFONO] %s \n", recvBuff);
	strcpy(infoCliente[2], recvBuff);

	// Correo
	strcpy(sendBuff, "Correo: ");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);

    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: [CORREO] %s \n", recvBuff);
	strcpy(infoCliente[3], recvBuff);

	// Direccion
	strcpy(sendBuff, "Direccion: ");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);

    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: [DIRECCION] %s \n", recvBuff);
	strcpy(infoCliente[4], recvBuff);

	// Contrasena
	strcpy(sendBuff, "Contrasena: ");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);

    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: [CONTRASENA] %s \n", recvBuff);
	strcpy(infoCliente[5], recvBuff);

	// vip
	strcpy(sendBuff, "??Desea ser vip? (S/N) ");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);

    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: [VIP] %s \n", recvBuff);

	if (strcmp(recvBuff, "S") == 0) {
		
		strcpy(sendBuff, "Nivel: (standar/premium)");
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);

    	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		printf("Data received: [NIVEL] %s \n", recvBuff);
		strcpy(infoCliente[6], recvBuff);
		
	} else {
		strcpy(infoCliente[6], "NADA");
	}

    return infoCliente;
}


void verComprasCliente (sqlite3 *db, int idCliente) {

	// Obtener las compras del cliente
	Compra** compras = cargarCompras (db);
	int numCompras = sizeCompras(db);

	int count = 0;
	for (int i = 0; i < numCompras; i++) {
		if (compras[i]->idComprador == idCliente) {
			count++;
		}
	}

	Compra** comprasHechas = (Compra**)malloc(sizeof(Compra*)*count);
	for (int i = 0; i < count; i++) {
		comprasHechas[i] = (Compra*)malloc(sizeof(Compra));
	}

	int a = 0;
	for (int i = 0; i < numCompras; i++) {
		if (compras[i]->idComprador == idCliente) {
			comprasHechas[a] = compras[i];
			a++;
		}
	}


	// Ensenar compras
	if (count == 0) {
		strcpy(sendBuff, "Todavia no has realizado ninguna compra en sportKit");
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: %s \n", sendBuff);
	} else {
		for (int i = 0; i < count; i++) {
			sprintf(sendBuff, "%i: %s (%ieuros)", comprasHechas[i]->idCompra, (obtenerProductos (db, comprasHechas[i]->idProducto).nombreProducto), comprasHechas[i]->precioCompra);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			printf("Data sent: %s \n", sendBuff);
		}
		strcpy(sendBuff, "Esas son tus compras");
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: %s \n", sendBuff);
	}

}


void verProductos (sqlite3 *db) {

	Producto** productos = cargarProductos(db);
	int numProductos = sizeProductos(db);

	strcpy(sendBuff, "Productos disponibles en SportKit");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Data sent: %s \n", sendBuff);


	// Ensenar compras
	for (int i = 0; i < numProductos; i++) {
		sprintf(sendBuff, "%i: %s [talla: %i] (%i euros)", productos[i]->idProducto, productos[i]->nombreProducto, productos[i]->tallaProducto, productos[i]->precioProducto);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: %s \n", sendBuff);
	}

	strcpy(sendBuff, "Esos son los productos");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Data sent: %s \n", sendBuff);
	
}


void comprar (sqlite3 *db, int idCompra, int idCliente, bool esVip) {

	// ***********************
	// MANDAR EL CLIENTE DATO A DATO
	// ***********************

	int idComp;

	if (!esVip) {
		Comprador comprador = obtenerComprador(db, idCliente);

		idComp = comprador.idComprador;

		sprintf(sendBuff, "%i", idCliente);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [ID] %s \n", sendBuff);

		strcpy(sendBuff, comprador.nombreComprador);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [NOMBRE] %s \n", sendBuff);

		sprintf(sendBuff, "%i", comprador.telefono);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [TELEFONO] %s \n", sendBuff);

		strcpy(sendBuff, comprador.correo);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [CORREO] %s \n", sendBuff);

		strcpy(sendBuff, comprador.direccion);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [DIRECCION] %s \n", sendBuff);

		strcpy(sendBuff, comprador.contrasena);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [CONTRASENA] %s \n", sendBuff);

		strcpy(sendBuff, "NOVIP");
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: %s \n", sendBuff);

	} else {
		CompradorVip comprador = obtenerCompradorVIP(db, idCliente);

		idComp = comprador.idCompradorVIP;

		sprintf(sendBuff, "%i", idCliente);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [ID] %s \n", sendBuff);

		strcpy(sendBuff, comprador.nombreCompradorVIP);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [NOMBRE] %s \n", sendBuff);

		sprintf(sendBuff, "%i", comprador.telefono);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [TELEFONO] %s \n", sendBuff);

		strcpy(sendBuff, comprador.correo);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [CORREO] %s \n", sendBuff);

		strcpy(sendBuff, comprador.direccion);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [DIRECCION] %s \n", sendBuff);

		strcpy(sendBuff, comprador.contrasena);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [CONTRASENA] %s \n", sendBuff);

		strcpy(sendBuff, comprador.nivel);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [NIVEL] %s \n", sendBuff);
	}

	// ***********************
	// EMPEZAMOS CON LA COMPRA
	// ***********************

	int idProd;

	strcpy(sendBuff, "Introduce el identificativo del producto que desea comprar.");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Data sent: %s \n", sendBuff);

	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: %s \n", recvBuff);
	idProd = atoi(recvBuff);

	bool existe = existeProducto (db, idProd);

	if (existe) {

		// MANDAMOS CUANTO CUESTA EL PRODUCTO EN PRINCIPIO

		Producto prod = obtenerProductos(db, idProd);

		sprintf(sendBuff, "%f", prod.precioProducto);
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: [PRECIO] %s \n", sendBuff);


		// ***********************
		// RECIBIMOS CUANTO NOS COSTARA
		// ***********************

		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		printf("Data received: %s \n", recvBuff);

		// *****************************
		// HACER LA COMPRA CON LA BD
		// *****************************

		int result = agregarCompra (db, idCompra, idProd, idComp, prod.precioProducto);

		if (result == SQLITE_OK) {
			strcpy(sendBuff, "Compra hecha");
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		} else {
			strcpy(sendBuff, "Ha habido un error");
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		}

	} else {

		strcpy(sendBuff, "No existe este producto");
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);

	}
	
}


int main() {
    sqlite3 *db;
    int result;

	//  Abrir conexion con la base de datos
    result = sqlite3_open("bbdd.db", &db);
    if (result != SQLITE_OK) {
		printf("Error al establecer conexion con la base de datos\n");
		return result;
	} else {
        printf("Conexion establecida con la base de datos\n") ;
    }
	

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n");

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}


	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));



	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);
	printf("Waiting for incoming messages from client... \n");

	Comprador comprador = {-1, "nada", 0, "nada", "nada", "nada"};
	CompradorVip compradorVip = {-1, "nada", 0, "nada", "nada", "nada", "nada"};
	bool esVip;

	int idCompra = maxIdCompra(db) + 1;

    // SEND AND RECEIVE
	do {
		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);

		if (bytes > 0) {

			printf("Data received: %s \n", recvBuff);
			
			if (strcmp(recvBuff, "INICIAR CLIENTE") == 0) {

  				char** infoCliente = iniciarCliente(db);
				
				if (strcmp(infoCliente[2], "NADA") == 0) {

					strcpy(sendBuff, "ERROR");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Data sent: %s \n", sendBuff);

					break;

				} else if (strcmp(infoCliente[2], "NOVIP") == 0) {

					strcpy(sendBuff, "Bienvenido");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Data sent: %s \n", sendBuff);

					esVip = false;
					comprador = obtenerCompradorCorreo (db, infoCliente[0]);
					
				}  else {

					strcpy(sendBuff, "Bienvenido");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Data sent: %s \n", sendBuff);

					esVip = true;
					compradorVip = obtenerCompradorVIPCorreo (db, infoCliente[0]);

				}

			} 

			if (strcmp(recvBuff, "REGISTRAR CLIENTE") == 0) {
				
  				char** infoCliente = registrarCliente(db);

				strcpy(sendBuff, "Bienvenido");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);

				if (strcmp(infoCliente[6], "NADA") == 0) {
					esVip = false;
					agregarComprador (db, atoi(infoCliente[0]), infoCliente[1], atoi(infoCliente[2]), infoCliente[3], infoCliente[4], infoCliente[5], 0);
					comprador = obtenerComprador (db, atoi(infoCliente[0]));
				} else {
					esVip = true;
					agregarCompradorVIP (db, atoi(infoCliente[0]), infoCliente[1], atoi(infoCliente[2]), infoCliente[3], infoCliente[4], infoCliente[5], infoCliente[6]);
					compradorVip = obtenerCompradorVIP (db, atoi(infoCliente[0]));
				}

			}

			if (strcmp(recvBuff, "VER MIS COMPRAS") == 0) {
				
				if (esVip) {
  					verComprasCliente (db, compradorVip.idCompradorVIP);
				} else {
					verComprasCliente (db, comprador.idComprador);
				}

			}

			if (strcmp(recvBuff, "VER PRODUCTOS") == 0) {
				
				verProductos (db);

			}

			if (strcmp(recvBuff, "QUIERO COMPRAR") == 0) {
				
				if (esVip) {
					comprar (db, idCompra, compradorVip.idCompradorVIP, true);
				} else {
					comprar (db, idCompra, comprador.idComprador, false);
				}

			}

			
			if (strcmp(recvBuff, "TERMINAR") == 0) {
				break;
			}
				
		}
		 
	} while (true);

	result = sqlite3_close(db);
    if (result != SQLITE_OK) {
        printf("Error closing database\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    } else {
        printf("Database closed\n");
        loggerTxt("Base de datos cerrada\n");
    }


	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();


}