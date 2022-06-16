#ifndef _SOCKET_H_
#define _SOCKET_H_

#include "winsock2.h"

class ClientSocket {
public:
    static WSADATA wsaData;
    static SOCKET sck;
    static sockaddr_in server;
    static char sendBuff[512];
    static char recvBuff[512];
    static bool isStarted;
    static int empezarSocket();
    static int terminarSocket();
    static int mandarMensaje(const char* mensaje);
    static int recibirMensaje();

    static char* getRecvBuff();
};

#endif