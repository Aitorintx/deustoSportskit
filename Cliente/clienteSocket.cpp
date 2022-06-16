#include "clienteSocket.h"
#include <iostream>
#include <string.h>

using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

WSADATA ClientSocket::wsaData;
SOCKET ClientSocket::sck;
sockaddr_in ClientSocket::server;
char ClientSocket::sendBuff[512];
char ClientSocket::recvBuff[512];
bool ClientSocket::isStarted = false;

int ClientSocket::empezarSocket() {
	// Inicializacion
	cout << "Initialising Winsock..." << endl;
	if (WSAStartup(MAKEWORD(2, 2), &ClientSocket::wsaData) != 0) {
		cout << "Failed. Error Code : " << (double) WSAGetLastError() << endl;
		return -1;
	}
	cout << "Initialised." << endl;

	// Creacion
	if ((ClientSocket::sck = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout << "Could not create socket: " << (double) WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "Socket created." << endl;

	ClientSocket::server.sin_addr.s_addr = inet_addr(SERVER_IP);
	ClientSocket::server.sin_family = AF_INET;
	ClientSocket::server.sin_port = htons(SERVER_PORT);

	// Conexion
	if (connect(ClientSocket::sck, (struct sockaddr*)&ClientSocket::server, sizeof(ClientSocket::server)) == SOCKET_ERROR) {
		cout << "Connection error: " << (double) WSAGetLastError() << endl;
		closesocket(ClientSocket::sck);
		WSACleanup();
		return -1;
	}

	cout << "Connection stablished with: " << inet_ntoa(ClientSocket::server.sin_addr) << (double) ntohs(ClientSocket::server.sin_port);
	ClientSocket::isStarted = true;
	return 0;
}

int ClientSocket::terminarSocket() {
	if (ClientSocket::isStarted == true) {
		closesocket(ClientSocket::sck);
		WSACleanup();
		return 0;
	}
	
	return -1;
}
int ClientSocket::mandarMensaje(const char* mensaje) {
	if (ClientSocket::isStarted == true) {
		cout << "Enviando mensaje: " << mensaje << endl;
		strcpy(ClientSocket::sendBuff, mensaje);
		send(ClientSocket::sck, ClientSocket::sendBuff, sizeof(ClientSocket::sendBuff), 0);

		return 0;
	}
	return -1;
	
}
int ClientSocket::recibirMensaje() {
	if (ClientSocket::isStarted == true) {
		cout << "Recibiendo mensaje" << endl;
		recv(ClientSocket::sck, ClientSocket::recvBuff, sizeof(ClientSocket::recvBuff), 0);
		cout << "Mensaje recibido: " << ClientSocket::recvBuff << endl;

		return 0;
	}
	
	return -1;
}

char* ClientSocket::getRecvBuff() {
	return ClientSocket::recvBuff;
}
