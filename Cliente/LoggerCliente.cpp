#include <iostream>
#include <time.h>
#include <string.h>
#include <fstream>

using namespace std;

#include "LoggerCliente.h"


void loggerTxt(char* mensaje, int idCliente) {

    time_t tiempoRaw;
	struct tm* tiempo;

	time(&tiempoRaw);
	tiempo = localtime(&tiempoRaw);
	char* hora = asctime(tiempo);
	hora[strlen(hora) - 1] = '\0';

	ofstream fichero;
	fichero.open("LoggerCliente.txt", ios::app | ios::out);
	fichero << "[" << hora << "] (CLIENTE: " << idCliente << "): " << mensaje << endl;
	fichero.close();

}



