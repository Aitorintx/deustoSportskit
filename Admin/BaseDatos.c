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

Prenda obtenerPrenda (sqlite3 *db, int id) {
	sqlite3_open("bbdd.db",&db);
    sqlite3_stmt *stmt;

	char sql[100];
	int iden, stock, talla;
	char *nombre;
	float  precio;
	nombre = malloc(100*sizeof(char));

	sprintf(sql, "SELECT * FROM Prenda WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_int(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	precio = (float)sqlite3_column_double(stmt, 2);
	stock = (int)sqlite3_column_int(stmt, 3);
	talla = (int)sqlite3_column_int(stmt, 4);

	Prenda prenda = {iden, nombre, precio, stock, talla};

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return prenda;
}


void agregarPrenda (sqlite3 *db, int id, char* nom, float precio, int stock, float talla) {
    sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db",&db);

	char sql[100];

	sprintf(sql, "INSERT INTO Prenda VALUES (%i, %s, %f, %i, %f)", id, nom, precio, stock, talla);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}


void subirStockPrenda (sqlite3 *db, int id, int cant) {
    sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db",&db);
	char sql[100];

	sprintf(sql, "UPDATE Prenda SET stockPrenda = stockPrenda + %i WHERE idProducto = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}


void eliminarPrenda (sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db",&db);

	char sql[100];
	sprintf(sql, "DELETE Prenda WHERE idProducto = %i", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}







// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- CALZADO --------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------

Calzado obtenerCalzado (sqlite3 *db, int id) {
	sqlite3_open("bbdd.db",&db);
    sqlite3_stmt *stmt;

	char sql[100];
	int iden, stock, talla;
	char *nombre;
	float  precio;
	nombre = malloc(100*sizeof(char));

	sprintf(sql, "SELECT * FROM Calzado WHERE idProducto = %i",id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	iden = (int)sqlite3_column_int(stmt, 0);
	strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
	precio = (float)sqlite3_column_double(stmt, 2);
	stock = (int)sqlite3_column_int(stmt, 3);
	talla = (int)sqlite3_column_int(stmt, 4);

	Calzado zapatilla = {iden, nombre, precio, stock, talla};

	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return zapatilla;
}


void agregarCalzado(sqlite3 *db, int id, char* nom, float precio, int stock, float talla) {
    sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db",&db);

	char sql[100];

	sprintf(sql, "INSERT INTO Calzado VALUES (%i, %s, %f, %i, %f)", id, nom, precio, stock, talla);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}


void subirStockCalzado (sqlite3 *db, int id, int cant) {
    sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db",&db);
	char sql[100];

	sprintf(sql, "UPDATE Calzado SET stockCalzado = stockCalzado + %i WHERE idProducto = %i", cant, id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}


void eliminarCalzado(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db",&db);

	char sql[100];
	sprintf(sql, "DELETE Calzado WHERE idProducto = %i", id);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}




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

	Administrador a = {id, nombre, contrasena};

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






