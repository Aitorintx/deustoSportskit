#include "..\Admin\BaseDatos.h"
#include "..\Admin\productos.h"
#include "..\Admin\sqlite3.h"

#include <winsock2.h>
#include <stdio.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
int main(){
    sqlite3 *db;
    int result;

	//  Abrir conexion con la base de datos
    result = sqlite3_open("../Admin/bbdd.db", &db);
    if (result != SQLITE_OK) {
		printf("Error al establecer conexion con la base de datos\n");
		return result;
	} else {
        printf("Conexion establecida con la base de datos\n") ;
    }

    // Cargar clientes
    Compra** compras;
    cargarCompras(db,compras);
	
    
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

	int numComprador=sizeComprador(db);
	int numVIP=sizeCompradoresVip(db);
	int numProds=sizeProductos(db);
	int numCompras=sizeCompras(db);
    int numProductosC=sizeComprasId(db);
	do {
		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		if (bytes > 0) {
			if(strcmp(recvBuff, "Numero de Clientes") == 0){
  				char numC[10];
  				sprintf(numC, "%d", numComprador);
				printf("%i", numComprador);
				strcpy(sendBuff, numC);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", numC);
			}

			if(strcmp(recvBuff, "Numero de Clientes VIP") == 0){
				char numCV[10];
  				sprintf(numCV, "%d", numVIP);
				printf("%i", numVIP);
				strcpy(sendBuff, numCV);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
			}

			if(strcmp(recvBuff, "Numero de Productos") == 0){
				char numP[10];
  				sprintf(numP, "%d", numProds);
				printf("%i", numProds);
				strcpy(sendBuff, numP);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
			}

			if(strcmp(recvBuff, "Numero de Compras") == 0){
				char numC[10];
  				sprintf(numC, "%d", numCompras);
				printf("%i", numCompras);
				strcpy(sendBuff, numC);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
			}

            if(strcmp(recvBuff, "Numero de Productos en Compras") == 0){
				char numCP[10];
  				sprintf(numCP, "%d", numCompras);
				printf("%i", numCompras);
				strcpy(sendBuff, numC);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
			}

			if(strcmp(recvBuff, "Quiero Las Contrasenas") == 0){
  				strcpy(sendBuff, usuarios[contContra]->contrasena);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contContra++;
			}

			if(strcmp(recvBuff, "Quiero Los DineroMax") == 0){
  				char numU[10];
  				sprintf(numU, "%f", usuarios[contDineroMax]->dineroMax);
				strcpy(sendBuff, numU);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contDineroMax++;
			}

			if(strcmp(recvBuff, "Quiero Las Partidas") == 0){
  				char numU[10];
  				sprintf(numU, "%i", usuarios[contPartidas]->partidas);
				strcpy(sendBuff, numU);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contPartidas++;
			}

			if(strcmp(recvBuff, "Quiero Las Wins") == 0){
  				char numU[10];
  				sprintf(numU, "%i", usuarios[contWins]->wins);
				strcpy(sendBuff, numU);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contWins++;
			}

			if(strcmp(recvBuff, "Quiero Los Equipos") == 0){
				strcpy(sendBuff, equipos[cont1]);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				cont1++;
			}
			//	Partidos
			if(strcmp(recvBuff, "Quiero Los CodPartido") == 0){
  				char numU[10];
  				sprintf(numU, "%i", partidos[contCodPartido].codPartido);
				strcpy(sendBuff, numU);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contCodPartido++;
			}

			if(strcmp(recvBuff, "Quiero Las Jornadas") == 0){
  				char numU[10];
  				sprintf(numU, "%i", partidos[contJornada].jornada);
				strcpy(sendBuff, numU);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contJornada++;
			}

			if(strcmp(recvBuff, "Quiero Los EquipoLocal") == 0){
  				char numU[10];
  				sprintf(numU, "%i", partidos[contEquipoLocal].local);
				strcpy(sendBuff, numU);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contEquipoLocal++;
			}

			if(strcmp(recvBuff, "Quiero Los EquipoVisitante") == 0){
  				char numU[10];
  				sprintf(numU, "%i", partidos[contEquipoVisitante].visitante);
				strcpy(sendBuff, numU);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				contEquipoVisitante++;
			}

			if (strcmp(recvBuff, "Quiero Las Probabilidades") == 0){
				char* numero;
				numero = (char*)malloc(sizeof(char)*10);
				gcvt(probabilidades[cont2], 4, numero);
				strcpy(sendBuff, numero);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				cont2++;		
			}
			
			
			strncpy(mensaje, recvBuff, 7);
			if (strcmp(mensaje, "Usuario") == 0){
				strUser = (char*)malloc(sizeof(strlen(recvBuff) + 1 -7));

				for(int i = 7; i<strlen(recvBuff); i++){
					strUser[i-7] = recvBuff[i];
				}		
			}

			if (strcmp(mensaje, "Contras") == 0){
				strPass = (char*)malloc(sizeof(strlen(recvBuff) + 1 -7));

				for(int i = 7; i<strlen(recvBuff); i++){
					strPass[i-7] = recvBuff[i];
				}

				Usuario u = {strUser, strPass, 0, 0, 0};
				printf(strPass);
				guardarUsuarioDB(db, &u);
						
			}

			
			//strncpy(mensaje1, recvBuff, 6);
			for(int i = 0; i<6; i++){
					mensaje1[i] = recvBuff[i];
				}	
			printf("%s",mensaje1);
			if (strcmp(mensaje1, "Dinero") == 0){
				float din;
				dinero = (char*)malloc(sizeof(strlen(recvBuff) + 1 -6));

				for(int i = 6; i<strlen(recvBuff); i++){
					dinero[i-6] = recvBuff[i];
				}		
				din = atof(dinero);
			}

			if (strcmp(mensaje1, "CodUsu") == 0){

				codUsu = (char*)malloc(sizeof(strlen(recvBuff) + 1 -6));

				for(int i = 6; i<strlen(recvBuff); i++){
					codUsu[i-6] = recvBuff[i];
				}
				printf("%s", codUsu);
				
			}

			
			if (strcmp(recvBuff, "Bye") == 0){
				break;
			}
				
			}
		 
	} while (true);
}