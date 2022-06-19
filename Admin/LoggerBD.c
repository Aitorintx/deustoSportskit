#include <time.h>
#include <string.h>
#include <stdio.h>

#include "LoggerBD.h"


void loggerTxt(char* mensaje) {

    time_t tiempoRaw;
	struct tm* tiempo;

	time(&tiempoRaw);
	tiempo = localtime(&tiempoRaw);
	char* hora = asctime(tiempo);
	hora[strlen(hora) - 1] = '\0';

    FILE* fichero;
    fichero = fopen("LoggerBD.txt", "a");

    fprintf(fichero, "[%s] BASE DE DATOS: %s \n", hora, mensaje);

	fclose(fichero);
}

