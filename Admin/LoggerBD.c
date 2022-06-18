#include <time.h>
#include <string.h>
#include <stdio.h>

#include "LoggerBD.h"


void loggerTxt(char* mensaje) {

    time_t tiempoRaw;
	struct tm* infoTiempo;

	time(&tiempoRaw);
	infoTiempo = localtime(&tiempoRaw);
	char* stringTiempo = asctime(infoTiempo);
	stringTiempo[strlen(stringTiempo) - 1] = '\0';

    FILE* fichero;
    fichero = fopen("LoggerBD.txt", "w");

    fprintf(fichero, "[%s]: %s \n", stringTiempo, mensaje);

	fclose(fichero);
}

