#include "..\Admin\BaseDatos.h"
#include "..\Admin\Productos.h"
#include "..\Admin\sqlite3.h"
#include "..\Admin\LoggerBD.h"

#include <winsock2.h>
#include <stdio.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000


int main(){
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

    // Cargar clientes
    
	Producto** productos = cargarProductos(db);
	
	
    
    WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];

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
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);
	printf("Waiting for incoming messages from client... \n");


	Comprador** compradores = cargarCompradoresNormales(db);
	CompradorVip** compradoresVIP = cargarCompradoresVIP(db);
	Compra** compras = cargarCompras(db);

	
	int numVIP=sizeCompradoresVip(db);
	int numComprador=sizeCompradores(db)-numVIP;
	int numProds=sizeProductos(db);
	int numCompras=sizeCompras(db);
	int numRealCompras=sizeComprasReales(db);
	int idMaxCompras=maxIdCompra(db);
	int idMaxComp=maxIdComprador(db);
	

	int punteroIDC=0;
	int punteroIDCV=0;
	int punteroNombresC=0;
	int punteroNombreCV=0;
	int	puntTelC=0;
	int puntTelCV=0;
	int puntCorC=0;
	int puntCorCV=0;
	int puntDirC=0;
	int puntDirCV=0;
	int puntContraC=0;
	int puntContraCV=0;
	int puntNivel=0;

	int puntIDP=0;
	int puntNomP=0;
	int puntTipo=0;
	int puntPrecio=0;
	int puntStock=0;
	int puntTalla=0;

	int puntIDC=0;
	int puntIDProd=0;
	int puntidComprador=0;
	int puntPrecioCompra=0;

	char* message = (char*)malloc(50);
	char* message2= (char*)malloc(50);
	char* message3= (char*)malloc(50);
	char* nombre;
	char* dir;
	char* cor;
	char* con;
	char* tel;
	char* niv;
	char* com;
	char* pro;
	char* cli;
	char* pre;

    
	do {
		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		if (bytes > 0) {
			if(strcmp(recvBuff, "Numero de Clientes") == 0){
  				char numC[10];
  				sprintf(numC, "%d", numComprador);
				printf("%i", numComprador);
				strcpy(sendBuff, numC);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("NUMERO CLIENTES NORMALES: %s \n", numC);
			}

			if(strcmp(recvBuff, "Numero de Clientes VIP") == 0){
				char numCV[10];
  				sprintf(numCV, "%d", numVIP);
				printf("%i", numVIP);
				strcpy(sendBuff, numCV);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("NUMERO CLIENTES VIP: %s \n", sendBuff);
			}

			if(strcmp(recvBuff, "Numero de Productos") == 0){
				char numP[10];
  				sprintf(numP, "%d", numProds);
				printf("%i", numProds);
				strcpy(sendBuff, numP);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("NUMERO DE PRODUCTOS: %s \n", sendBuff);
			}

			if(strcmp(recvBuff, "Numero de Compras") == 0){
				char numC[10];
  				sprintf(numC, "%d", numCompras);
				printf("%i", numCompras);
				strcpy(sendBuff, numC);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("NUMERO DE COMPRAS: %s \n", sendBuff);
			}


			if(strcmp(recvBuff, "Quiero el ID de los Clientes") == 0){
  				char idC[10];
  				sprintf(idC, "%i", compradores[punteroIDC]->idComprador);
				strcpy(sendBuff, idC);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("ID CLIENTE: %s \n", sendBuff);
				punteroIDC++;
			}

			if(strcmp(recvBuff, "Quiero el ID de los Clientes VIP") == 0){
  				char idCV[10];
  				sprintf(idCV, "%i", compradoresVIP[punteroIDCV]->idCompradorVIP);
				strcpy(sendBuff, idCV);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("ID CLIENTE VIP: %s \n", sendBuff);
				punteroIDCV++;
			}
			if(strcmp(recvBuff, "Quiero Los Nombres de los Clientes") == 0){
				strcpy(sendBuff, compradores[punteroNombresC]->nombreComprador);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("NOMBRE CLIENTE: %s \n", sendBuff);
				punteroNombresC++;
			}
			if(strcmp(recvBuff, "Quiero Los Nombres de los Clientes VIP") == 0){
				strcpy(sendBuff, compradoresVIP[punteroNombreCV]->nombreCompradorVIP);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("NOMBRE CLIENTE VIP: %s \n", sendBuff);
				punteroNombreCV++;
			}
			if(strcmp(recvBuff, "Quiero el telefono de los clientes") == 0){
  				char telC[20];
  				sprintf(telC, "%i", compradores[puntTelC]->telefono);
				strcpy(sendBuff, telC);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("TLF CLIENTE: %s \n", sendBuff);
				puntTelC++;
			}
			if(strcmp(recvBuff, "Quiero el telefono de los clientes VIP") == 0){
  				char telCV[20];
  				sprintf(telCV, "%i", compradoresVIP[puntTelCV]->telefono);
				strcpy(sendBuff, telCV);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("TLF CLIENTE VIP: %s \n", sendBuff);
				puntTelCV++;
			}
			if(strcmp(recvBuff, "Quiero los CORREOS de los Clientes") == 0){
				strcpy(sendBuff, compradores[puntCorC]->correo);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("CORREO CLIENTE: %s \n", sendBuff);
				puntCorC++;
			}
			if(strcmp(recvBuff, "Quiero los CORREOS de los Clientes VIP") == 0){
				strcpy(sendBuff, compradoresVIP[puntCorCV]->correo);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("CORREO CLIENTE VIP: %s \n", sendBuff);
				puntCorCV++;
			}
			if(strcmp(recvBuff, "Quiero las direcciones de los Clientes") == 0){
				strcpy(sendBuff, compradores[puntDirC]->direccion);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("DIR CLIENTE: %s \n", sendBuff);
				puntDirC++;
			}
			if(strcmp(recvBuff, "Quiero las direcciones de los Clientes VIP") == 0){
				strcpy(sendBuff, compradoresVIP[puntDirCV]->direccion);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("DIR CLIENTE VIP: %s \n", sendBuff);
				puntDirCV++;
			}
			if(strcmp(recvBuff, "Quiero Las Contraseñas de los Clientes") == 0){
				strcpy(sendBuff, compradores[puntContraC]->contrasena);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("CONTRASENA CLIENTE: %s \n", sendBuff);
				puntContraC++;
			}
			if(strcmp(recvBuff, "Quiero Las Contraseñas de los Clientes VIP") == 0){
				strcpy(sendBuff, compradoresVIP[puntContraCV]->contrasena);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("CONTRASENA CLIENTE VIP: %s \n", sendBuff);
				puntContraCV++;
			}
			if(strcmp(recvBuff, "Quiero Los Niveles de los Clientes VIP") == 0){
				strcpy(sendBuff, compradoresVIP[puntNivel]->nivel);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("NIVEL CLIENTE VIP: %s \n", sendBuff);
				puntNivel++;
			}
			if(strcmp(recvBuff, "Quiero el ID de los Productos") == 0){
  				char idP[10];
  				sprintf(idP, "%i", productos[puntIDP]->idProducto);
				strcpy(sendBuff, idP);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("ID PRODUCTO: %s \n", sendBuff);
				puntIDP++;
			}
			if(strcmp(recvBuff, "Quiero el Nombre de los Productos") == 0){
				strcpy(sendBuff, productos[puntNomP]->nombreProducto);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("NOMBRE PRODUCTO: %s \n", sendBuff);
				puntNomP++;
			}
			if(strcmp(recvBuff, "Quiero el Tipo de los Productos") == 0){
				strcpy(sendBuff, productos[puntTipo]->tipoProducto);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("TIPO PRODUCTO: %s \n", sendBuff);
				puntTipo++;
			}
			if(strcmp(recvBuff, "Quiero el precio de los Productos") == 0){
  				char precP[10];
  				sprintf(precP, "%f", productos[puntPrecio]->precioProducto);
				strcpy(sendBuff, precP);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("PRECIO PRODUCTO: %s \n", sendBuff);
				puntPrecio++;
			}
			if(strcmp(recvBuff, "Quiero el Stock de los Productos") == 0){
  				char stock[10];
  				sprintf(stock, "%i", productos[puntStock]->stockProducto);
				strcpy(sendBuff, stock);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("STOCK PRODUCTO: %s \n", sendBuff);
				puntStock++;
			}
			if(strcmp(recvBuff, "Quiero la talla de los Productos") == 0){
  				char talla[10];
  				sprintf(talla, "%i", productos[puntTalla]->tallaProducto);
				strcpy(sendBuff, talla);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("TALLA PRODUCTO: %s \n", sendBuff);
				puntTalla++;
			}
			if(strcmp(recvBuff, "Quiero el ID de las Compras") == 0){
  				char idP[10];
  				sprintf(idP, "%i", compras[puntIDC]->idCompra);
				strcpy(sendBuff, idP);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("ID COMPRA: %s \n", sendBuff);
				puntIDC++;
			}
			if(strcmp(recvBuff, "Quiero el ID del Producto") == 0){
  				char idP[10];
  				sprintf(idP, "%i", compras[puntIDProd]->idProducto);
				strcpy(sendBuff, idP);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("ID PRODUCTO COMPRADO: %s \n", sendBuff);
				puntIDProd++;
			}
			if(strcmp(recvBuff, "Quiero el ID del Comprador") == 0){
  				char idP[10];
  				sprintf(idP, "%i", compras[puntidComprador]->idComprador);
				strcpy(sendBuff, idP);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("ID COMPRADOR: %s \n", sendBuff);
				puntidComprador++;
			}
			if(strcmp(recvBuff, "Quiero el MAX ID de la Compra") == 0){
  				char idP[10];
  				sprintf(idP, "%i", idMaxCompras);
				strcpy(sendBuff, idP);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("MAX ID COMPRA: %s \n", sendBuff);
			}
			if(strcmp(recvBuff, "Quiero el numero Real de Compras") == 0){
  				char idP[10];
  				sprintf(idP, "%i", numRealCompras);
				strcpy(sendBuff, idP);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("NUM REAL COMPRAS: %s \n", sendBuff);
			}

			strncpy(message, recvBuff, 6);
			if (strcmp(message, "Nombre") == 0){
				
				nombre = (char*)malloc(sizeof(strlen(recvBuff) + 1 -6));

				for(int i = 6; i<strlen(recvBuff); i++){
					nombre[i-6] = recvBuff[i];
				}		
			}

			if (strcmp(message, "Telefo") == 0){
				
				tel = (char*)malloc(sizeof(strlen(recvBuff) + 1 -6));

				for(int i = 6; i<strlen(recvBuff); i++){
					tel[i-6] = recvBuff[i];
				}		
				
			}

			if (strcmp(message, "Correo") == 0){
				
				cor = (char*)malloc(sizeof(strlen(recvBuff) + 1 -6));

				for(int i = 6; i<strlen(recvBuff); i++){
					cor[i-6] = recvBuff[i];
				}		
				
			}

			if (strcmp(message, "Direcc") == 0){
				
				dir = (char*)malloc(sizeof(strlen(recvBuff) + 1 -6));

				for(int i = 6; i<strlen(recvBuff); i++){
					dir[i-6] = recvBuff[i];
				}		
			}


			if (strcmp(message, "Contra") == 0){
				
				con = (char*)malloc(sizeof(strlen(recvBuff) + 1 -6));

				for(int i = 6; i<strlen(recvBuff); i++){
					con[i-6] = recvBuff[i];
				}		

				idMaxComp++;
				agregarComprador(db,idMaxComp,nombre,atoi(tel),cor,dir,con,0);
				printf("Nuevo Cliente Agregado a la Base de Datos:\n");
				printf("----------------------------------------\n");
				printf("ID: %i NOMBRE: %s(%i) CORREO: %s DIRECCION: %s CONTRA: %s\n",idMaxCompras,nombre,atoi(tel),cor,dir,con);
				
				
			}

			strncpy(message2, recvBuff, 4);
			if (strcmp(message2, "NomV") == 0){
				
				nombre = (char*)malloc(sizeof(strlen(recvBuff) + 1 -4));

				for(int i = 4; i<strlen(recvBuff); i++){
					nombre[i-4] = recvBuff[i];
				}		
			}

			if (strcmp(message2, "TelV") == 0){
				
				tel = (char*)malloc(sizeof(strlen(recvBuff) + 1 -4));

				for(int i = 4; i<strlen(recvBuff); i++){
					tel[i-4] = recvBuff[i];
				}		
				
			}

			if (strcmp(message2, "CorV") == 0){
				
				cor = (char*)malloc(sizeof(strlen(recvBuff) + 1 -4));

				for(int i = 4; i<strlen(recvBuff); i++){
					cor[i-4] = recvBuff[i];
				}		
				
			}

			if (strcmp(message2, "DirV") == 0){
				
				dir = (char*)malloc(sizeof(strlen(recvBuff) + 1 -4));

				for(int i = 4; i<strlen(recvBuff); i++){
					dir[i-4] = recvBuff[i];
				}		
			}


			if (strcmp(message2, "ConV") == 0){
				
				con = (char*)malloc(sizeof(strlen(recvBuff) + 1 -4));

				for(int i = 4; i<strlen(recvBuff); i++){
					con[i-4] = recvBuff[i];
				}		
			}

			if (strcmp(message2, "NivV") == 0){
				
				niv = (char*)malloc(sizeof(strlen(recvBuff) + 1 -4));

				for(int i = 4; i<strlen(recvBuff); i++){
					niv[i-4] = recvBuff[i];
				}		

				
				agregarCompradorVIP(db,idMaxCompras,nombre,atoi(tel),cor,dir,con,niv);
				printf("Nuevo Cliente VIP Agregado a la Base de Datos:\n");
				printf("----------------------------------------\n");
				printf("ID: %i NOMBRE: %s(%i) CORREO: %s DIRECCION: %s NIVEL: %s CONTRA: %s\n",idMaxCompras,nombre,atoi(tel),cor,dir,niv,con);
				
			}

			strncpy(message3, recvBuff, 3);
			if (strcmp(message3, "Com") == 0){
				
				com = (char*)malloc(sizeof(strlen(recvBuff) + 1 -3));

				for(int i = 3; i<strlen(recvBuff); i++){
					com[i-3] = recvBuff[i];
				}		
			}

			if (strcmp(message3, "Pro") == 0){
				
				pro = (char*)malloc(sizeof(strlen(recvBuff) + 1 -3));

				for(int i = 3; i<strlen(recvBuff); i++){
					pro[i-3] = recvBuff[i];
				}		
			}

			if (strcmp(message3, "Cli") == 0){
				
				cli = (char*)malloc(sizeof(strlen(recvBuff) + 1 -3));

				for(int i = 3; i<strlen(recvBuff); i++){
					cli[i-3] = recvBuff[i];
				}		
			}

			if (strcmp(message3, "Pre") == 0){
				
				pre = (char*)malloc(sizeof(strlen(recvBuff) + 1 -3));

				for(int i = 3; i<strlen(recvBuff); i++){
					pre[i-3] = recvBuff[i];
				}		
				agregarCompra(db,atoi(com),atoi(pro),atoi(cli),atof(pre));
				printf("Nueva Compra Agregada\n");
				printf("---------------------------------\n");
				printf("ID: %i IDPROD: %i IDCLIENTE: %i IDPREC: %f\n",atoi(com),atoi(pro),atoi(cli),atof(pre));
			}
  
			



			
			if (strcmp(recvBuff, "Terminar") == 0){
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

}