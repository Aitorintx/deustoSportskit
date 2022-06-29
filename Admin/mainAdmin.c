#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Administrador.h"
#include "Productos.h"
#include "BaseDatos.h"
#include "sqlite3.h"
#include "LoggerBD.h"


int main () {

    printf("=========================== \n");
    printf("GESTION DE SPORTKIT \n");
    printf("========================== \n");
    printf("\n");


    printf("Bienvenido al programa de administracion de SportKit \n");

    printf("1. Iniciar sesion como administrador \n");
    printf("Pulsar 0 para salir \n");
    printf("\n");

    int respuesta;

    do {
	    printf("Opción: \n");
        scanf("%i", &respuesta);
    } while (!(respuesta == 0 || respuesta == 1));

    if (respuesta == 0) {

        printf("¡Que pase un buen dia! \n");

    } else {

        sqlite3 *db;

        int result = sqlite3_open("bbdd.db", &db);
        if (result != SQLITE_OK) {
            printf("Error opening database\n");
            return result;
        } else {
            printf("Database opened\n");
            loggerTxt("Base de datos abierta\n");
        }

        printf("\n");
        
        Administrador administrador = iniciarAdmin (db);

        // Si el identificativo del administrador es igual a -1, significa que es un impostor
        if (administrador.idAdmin != -1) {
            ventanaAdmin (db, administrador);
        }

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

}





