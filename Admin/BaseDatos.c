#include "Administrador.h"
#include "Productos.h"
#include "sqlite3.h"
#include "BaseDatos.h"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------- PRODUCTOS -------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------

int maxIdProducto (sqlite3 *db) {
    sqlite3_stmt *stmt;
    sqlite3_open("bbdd.db", &db);

    char sql[100];
    sprintf(sql, "SELECT MAX(idProducto) FROM Producto");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	int maximo = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return maximo;
}


void eliminarProducto(sqlite3 *db, int id){
    sqlite3_stmt *stmt;
    sqlite3_open("bbdd.db", &db);

    char sql[100];
    sprintf(sql, "DELETE FROM Producto WHERE idProducto = %i", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

    sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}


void agregarProducto(sqlite3 *db, int id, char* tipo, char* nombre) {
    sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);

	char sql[100];
	sprintf(sql, "INSERT INTO Producto VALUES (%i, %s, %s)", id, tipo, nombre);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}


char obtenerTipoProducto (sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);

	char sql[100];
	char* tipo;
	tipo = malloc(10*sizeof(char));

	sprintf(sql, "SELECT tipoProducto FROM Producto WHERE idProducto = %i", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	strcpy(tipo, (char*)sqlite3_column_text(stmt, 0));

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return tipo[0];				// C -> calzado		P -> prenda
}


int obtenerIdProducto (sqlite3 *db, char* nombre) {
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);

	char sql[100];
	int id;
	sprintf(sql, "SELECT idProducto FROM Producto WHERE nombreProducto = %s", nombre);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	id = (sqlite3_column_int(stmt, 0));

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return id;	
}


bool existeProducto (sqlite3 *db, int id) {
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);

	char sql[100];
	int existe;
	sprintf(sql, "SELECT COUNT(*) FROM Producto WHERE idProducto = %i", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	existe = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	bool respuesta;

	if (existe == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}
	sqlite3_close(db);

	return respuesta;	
}


bool existeProducto2 (sqlite3 *db, char* nombre) {
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);

	char sql[100];
	int existe;
	sprintf(sql, "SELECT COUNT(*) FROM Producto WHERE nombreProducto = %s", nombre);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	existe = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	bool respuesta;

	if (existe == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}
	sqlite3_close(db);
	return respuesta;	
}


// -------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- PRENDA -------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------








// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- CALZADO --------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------









// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- USUARIOS -------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------





// -------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------ ADMINISTRADOR ----------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------


Administrador obtenerAdmin(sqlite3 *db, int id) {
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db",&db);

	char sql[100];
	char *nombre, *contrasena;
	nombre = malloc(20*sizeof(char));
	contrasena = malloc(20*sizeof(char));
	sprintf(sql, "SELECT * FROM Administrador WHERE idAdmin = %d", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	strcpy(contrasena, (char*)sqlite3_column_text(stmt, 2));

	Administrador a = {nombre, id, contrasena};

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return a;
}

// HAY QUE LIBERAR MEMORIA TAMBIÉN AQUÍ?


int existeAdmin(sqlite3 *db, int id) {
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db",&db);

	char sql[100];
	int respuesta;
	sprintf(sql, "SELECT COUNT(*) FROM Administrador WHERE idAdmin = %d", id);
	sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);

	int size = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	if (size == 0) {
		respuesta = 0;
	} else {
		respuesta = 1;
	}

	sqlite3_close(db);

	return respuesta;
}


// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- CLIENTE -------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------









// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- COMPRAS --------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------






