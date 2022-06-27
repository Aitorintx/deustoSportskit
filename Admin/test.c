
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

    agregarComprador(db, 3, "Persona", 76543, "personadeusto.es", "Calle principal", "Contraaa", 0);
    mostrarCompradores(db);

    eliminarComprador(db, 3);
    mostrarCompradores(db);
    **/



    /**
    if (existeComprador(db, 1)) {
        printf("El comprador 1 SI existe \n");
    } else {
        printf("El comprador 1 NO existe \n");
    }

    Administrador admin = obtenerAdmin(db, 1);
    printf("Administrador %i: %s\n", admin.idAdmin, admin.nombreAdmin);

    if (existeAdmin(db, 1)) {
        printf("El admin 1 SI existe \n");
    } else {
        printf("El admin 1 NO existe \n");
    }


    printf("El id maximo de compra es : %i\n", maxIdCompra(db));

    printf("Hay un total de %i compras \n", sizeCompras(db));

    agregarCompra(db, 3, 1, 1, 40);
    mostrarCompras(db);


    printf("Hay un total de %i compras\n", sizeComprasReal(db));

    printf("Hay un total de %i compradores \n", sizeCompradores(db));
    printf("Hay un total de %i compradores vip \n", sizeCompradoresVip(db));
    **/


    /**
    Producto** productos = cargarProductos (db); 
    
    for (int i = 0; i < sizeProductos(db); i++) {
        printf("Producto %i: %s\n", productos[i]->idProducto, productos[i]->nombreProducto);
    }


    Compra** compras = cargarCompras (db); 
    
    for (int i = 0; i < sizeCompras(db); i++) {
        printf("Compra %i: producto %i, comprador %i\n", compras[i]->idCompra, compras[i]->idProducto, compras[i]->idComprador);
    }


    Compra** compras = cargarComprasId (db, 1); 
    
    for (int i = 0; i < sizeComprasId(db, 1); i++) {
        printf("Compra %i: producto %i, comprador %i\n", compras[i]->idCompra, compras[i]->idProducto, compras[i]->idComprador);
    }


    Comprador** compradores = cargarCompradores (db); 
    
    for (int i = 0; i < sizeCompradores(db); i++) {
        printf("Comprador %i: %s\n", compradores[i]->idComprador, compradores[i]->nombreComprador);
    }


    Comprador** compradores = cargarCompradoresNormales (db); 
    
    for (int i = 0; i < sizeCompradores(db)-sizeCompradoresVip(db); i++) {
        printf("Comprador %i: %s\n", compradores[i]->idComprador, compradores[i]->nombreComprador);
    }
    **/


    
    CompradorVip** compradores = cargarCompradoresVIP (db); 
    
    for (int i = 0; i < sizeCompradoresVip(db); i++) {
        printf("Comprador %s: [%s]. %s, %s \n", compradores[i]->nombreCompradorVIP, compradores[i]->nivel, compradores[i]->contrasena, compradores[i]->correo);
    }

    //Comprador ait = obtenerComprador(db, 1);
    //printf("Comprador %i: %s. %s. %s. [%s]\n", ait.idComprador, ait.nombreComprador, ait.direccion, ait.correo, ait.contrasena);
    

    /**
    Compra** compras;
	cargarCompras(db, compras);

    printf("Hasta aqui todo correcto PARTE 2 \n");

    printf("Compra %i\n", compras[0]->idCompra);
    printf("Compra %i\n", compras[1]->idCompra);
    printf("Compra %i\n", compras[2]->idCompra);
    printf("Compra %i\n", compras[3]->idCompra);

    
    for (int i = 0; i < sizeComprasReal(db); i++) {
        printf("Compra %i\n", compras[0]->idCompra);
    }
    **/


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
