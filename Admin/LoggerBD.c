#include <time.h>
#include <string.h>
#include <stdio.h>

#include "LoggerBD.h"


void loggerTxt(char* mensaje) {

    time_t tiempoRaw;
	struct tm* infoTiempo;

	time(&tiempoRaw);
	infoTiempo = localtime(&tiempoRaw);
	char* tiempo = asctime(infoTiempo);
	tiempo[strlen(tiempo) - 1] = '\0';

    FILE* fichero;
    fichero = fopen("LoggerBD.txt", "a");

    fprintf(fichero, "[%s]: %s \n", tiempo, mensaje);

	fclose(fichero);
}

