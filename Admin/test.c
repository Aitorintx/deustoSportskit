
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

    /**
    Producto pr = obtenerProductos (db, 4);
    printf("Hasta aqui todo correcto PARTE medio \n");
    printf("Producto %i: %s \n", pr.idProducto, pr.nombreProducto);

    printf("El id producto mas grande es %i\n", maxIdProducto(db));

    agregarProducto(db, 8, "CALZADO", "Zapatillas molonas", 55, 5, 40);
    
    eliminarProducto(db, 8);

    printf("El producto 7 es %c\n", obtenerTipoProducto(db, 7));
    
    printf("Hay un total de %i productos \n", sizeProductos(db));

    mostrarProductos(db);

    subirStock(db, 6, 5);
    mostrarProductos(db);
    

    printf("El comprador maximo es % i\n", maxIdComprador(db));

    if (obtenerTipoComprador(db, 1)) {
        printf("El comprador 1 es VIP \n");
    } else {
        printf("El comprador 1 no es VIP\n");
    }

    Comprador comprador = obtenerComprador(db, 1);
    printf("Comprador %i: %s\n", comprador.idComprador, comprador.nombreComprador);

    printf("En total hay %i compradores\n", sizeComprador(db));

    mostrarCompradores(db);
    **/

    agregarComprador(db, 3, "Persona", 76543, "persona@deusto.es", "Calle principal", "Contraaa", 0);
    mostrarCompradores(db);



    /**
    Producto** productos;
	cargarProductos(db, productos);

    printf("Hasta aqui todo correcto PARTE 2 \n");

    printf("Producto %i: %s\n", productos[0]->idProducto, productos[0]->nombreProducto);
    printf("Producto %i: %s\n", productos[1]->idProducto, productos[1]->nombreProducto);
    printf("Producto %i: %s\n", productos[2]->idProducto, productos[2]->nombreProducto);
    printf("Producto %i: %s\n", productos[3]->idProducto, productos[3]->nombreProducto);

    
    for (int i = 0; i < sizeProductos(db); i++) {
        printf("Producto %i: %s\n", productos[i]->idProducto, productos[i]->nombreProducto);
    }
    **/

    printf("Hasta aqui todo correcto PARTE 2 \n");


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
