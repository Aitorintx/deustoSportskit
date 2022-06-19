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
	Producto** productos;
	cargarProductos(db,productos);
	Comprador** compradores;
	CompradorVip** compradoresVIP;
	cargarCompradores(db, compradores,compradoresVIP);
	
    
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
	int
    
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

            aif(strcmp(recvBuff, "Numero de Productos en Compras") == 0){
				char numCP[10];
  				sprintf(numCP, "%d", numCompras);
				printf("%i", numCompras);
				strcpy(sendBuff, numCP);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
			}

			if(strcmp(recvBuff, "Quiero el ID de los Clientes") == 0){
  				char idC[10];
  				sprintf(idC, "%i", compradores[punteroIDC]->idComprador);
				strcpy(sendBuff, idC);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				punteroIDC;
			}

			if(strcmp(recvBuff, "Quiero el ID de los Clientes VIP") == 0){
  				char idCV[10];
  				sprintf(idCV, "%i", compradoresVIP[punteroIDCV]->idComprador);
				strcpy(sendBuff, idCV);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				punteroIDCV;
			}
			if(strcmp(recvBuff, "Quiero Los Nombres de los Clientes") == 0){
				strcpy(sendBuff, compradores[punteroNombresC]->nombreComprador);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				punteroNombresC++;
			}
			if(strcmp(recvBuff, "Quiero Los Nombres de los Clientes VIP") == 0){
				strcpy(sendBuff, compradoresVIP[punteroNombresCV]->nombreComprador);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				punteroNombresCV++;
			}
			if(strcmp(recvBuff, "Quiero el telefono de los clientes") == 0){
  				char telC[20];
  				sprintf(telC, "%i", compradores[puntTelC]->telefono);
				strcpy(sendBuff, telC);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				puntTelC;
			}
			if(strcmp(recvBuff, "Quiero el telefono de los clientes VIP") == 0){
  				char telCV[20];
  				sprintf(telCV, "%i", compradoresVIP[puntTelCV]->telefono);
				strcpy(sendBuff, telCV);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				puntTelCV;
			}
			if(strcmp(recvBuff, "Quiero los CORREOS de los Clientes") == 0){
				strcpy(sendBuff, compradores[puntCorC]->correo);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				puntCorC++;
			}
			if(strcmp(recvBuff, "Quiero los CORREOS de los Clientes VIP") == 0){
				strcpy(sendBuff, compradoresVIP[puntCorCV]->correo);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				puntCorCV++;
			}
			if(strcmp(recvBuff, "Quiero las direcciones de los Clientes") == 0){
				strcpy(sendBuff, compradores[puntDirC]->direccion);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				puntDirC++;
			}
			if(strcmp(recvBuff, "Quiero las direcciones de los Clientes VIP") == 0){
				strcpy(sendBuff, compradoresVIP[puntDirCV]->direccion);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				puntDirCV++;
			}
			if(strcmp(recvBuff, "Quiero Las Contraseñas de los Clientes") == 0){
				strcpy(sendBuff, compradores[puntContraC]->contrasena);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				puntContraC++;
			}
			if(strcmp(recvBuff, "Quiero Las Contraseñas de los Clientes VIP") == 0){
				strcpy(sendBuff, compradoresVIP[puntContraCV]->contrasena);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				puntContraCV++;
			}
			if(strcmp(recvBuff, "Quiero Los Niveles de los Clientes VIP") == 0){
				strcpy(sendBuff, compradoresVIP[puntNivel]->nivel);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				puntNivel++;
			}
			if(strcmp(recvBuff, "Quiero el ID de los Productos") == 0){
  				char idP[10];
  				sprintf(idP, "%i", compradores[punteroIDC]->idComprador);
				strcpy(sendBuff, idC);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Data sent: %s \n", sendBuff);
				punteroID;
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