
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Productos.h"
#include "BaseDatos.h"
#include "sqlite3.h"
#include "LoggerBD.h"
#include "Administrador.h"


int main () {

    printf("Hasta aqui todo correcto PARTE 0 \n");

    sqlite3 *db;
    int result;

	//  Abrir conexion con la base de datos
    result = sqlite3_open("bbdd.db", &db);
    if (result != SQLITE_OK) {
		printf("Error al establecer conexion con la base de datos\n");
		return result;
	} else {
        printf("Database opened\n");
        printf("Conexion establecida con la base de datos\n") ;
    }

    printf("\n");

    Administrador administtador = {-1, "nada", "nada"};


   recargarProdFichero (db, administtador);


    printf("\n");

    result = sqlite3_close(db);
    if (result != SQLITE_OK) {
        printf("Error closing database\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    } else {
        printf("Database closed\n");
        loggerTxt("Base de datos cerrada\n");
    }


    return 0;

}
