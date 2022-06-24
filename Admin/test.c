
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Productos.h"
#include "BaseDatos.h"
#include "sqlite3.h"
#include "LoggerBD.h"


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
        printf("Conexion establecida con la base de datos\n") ;
    }

    printf("Hasta aqui todo correcto PARTE 1 \n");

    Producto pr = obtenerProductos (db, 4);
    printf("Hasta aqui todo correcto PARTE medio \n");
    printf("Producto %i: %s \n", pr.idProducto, pr.nombreProducto);

    Producto** productos;
	cargarProductos(db, productos);

    printf("Hasta aqui todo correcto PARTE 2 \n");

    printf("Producto %i: %s\n", productos[0]->idProducto, productos[0]->nombreProducto);
    printf("Producto %i: %s\n", productos[1]->idProducto, productos[1]->nombreProducto);
    printf("Producto %i: %s\n", productos[2]->idProducto, productos[2]->nombreProducto);
    printf("Producto %i: %s\n", productos[3]->idProducto, productos[3]->nombreProducto);

    /**
    for (int i = 0; i < sizeProductos(db); i++) {
        printf("Producto %i: %s\n", productos[i]->idProducto, productos[i]->nombreProducto);
    }
    **/

    printf("Hasta aqui todo correcto PARTE 3 \n");


    return 0;

}
