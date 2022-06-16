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
	sqlite3_open("bdd.db", &db);

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
void eliminarTodasLasPrenda(sqlite3 *db, int idPrenda)
{
	sqlite3_stmt *stmt;

	char sql[] = "Borrar todas las prendas !";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (DELETE)\n");

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (DELETE)\n");

	return SQLITE_OK;
}

void eliminarPrenda(sqlite3 *db, int idPrenda){
    sqlite3_stmt *stmt;
    sqlite3_open("bbdd.db", &db);

    char sql[100];
    sprintf(sql, "DELETE FROM Prenda WHERE idPrenda = %i", idPrenda);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

    sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void agregarPrenda(sqlite3 *db, int idPrenda, char* nombrePrenda, float precioPrenda, int stockPrenda, int tallaPrenda) 
{
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);
	
	char sql[100];
	sprintf(sql, "INSERT INTO Prenda VALUES (%i, %s, %f, %i ,%i)", idPrenda, nombrePrenda, precioPrenda, stockPrenda, tallaPrenda);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);

}

bool existePrenda (sqlite3 *db, int idPrenda)
{
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);

	char sql[100];
	int existe;
	sprintf(sql, "SELECT COUNT(*) FROM Prenda WHERE idProducto = %i", idPrenda);
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
// -------------------------------------------------- CALZADO --------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------

void eliminarTodasLosCalzados(sqlite3 *db, int idCalzado)
{
	sqlite3_stmt *stmt;

	char sql[] = "Borrar todos los calzados !";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (DELETE)\n");

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (DELETE)\n");

	return SQLITE_OK;
}

void eliminarCalzados(sqlite3 *db, int idCalzado){
    sqlite3_stmt *stmt;
    sqlite3_open("bbdd.db", &db);

    char sql[100];
    sprintf(sql, "DELETE FROM Prenda WHERE idCalzado = %i", idCalzado);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

    sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void agregarCalzados(sqlite3 *db, int idCalzado, char* nombreCalzado, float precioCalzado, int stockCalzado, int tallaCalzado) 
{
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);
	
	char sql[100];
	sprintf(sql, "INSERT INTO Prenda VALUES (%i, %s, %f, %i ,%i)", idCalzado, nombreCalzado, precioCalzado,stockCalzado, tallaCalzado);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);

}

bool existeCalzados(sqlite3 *db, int idCalzado)
{
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);

	char sql[100];
	int existe;
	sprintf(sql, "SELECT COUNT(*) FROM Prenda WHERE idCalzado = %i", idCalzado);
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
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- USUARIOS -------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
int showAllUsuarios(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[] = "select id, name from usuario";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (SELECT)\n");

	int id;
	char name[100];

	printf("\n");
	printf("\n");
	printf("Showing usuarios:\n");
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);
			strcpy(name, (char *) sqlite3_column_text(stmt, 1));
			printf("ID: %d Name: %s\n", id, name);
		}
	} while (result == SQLITE_ROW);

	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return SQLITE_OK;
}
/*
void eliminarUsuarios(sqlite3 *db, int idCalzado){
    sqlite3_stmt *stmt;
    sqlite3_open("bbdd.db", &db);

    char sql[100];
    sprintf(sql, "DELETE FROM Prenda WHERE idPrenda = %i", idCalzado);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

    sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void agregarUsuarios(sqlite3 *db, int idCalzado, char* nombreCalzado, float precioCalzado, int stockCalzado, int tallaCalzado) 
{
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);
	
	char sql[100];
	sprintf(sql, "INSERT INTO Prenda VALUES (%i, %s, %f, %i ,%i)", idCalzado, nombreCalzado, precioCalzado,stockCalzado, tallaCalzado);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);

}

bool existeUsuario(sqlite3 *db, int idCalzado)
{
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);

	char sql[100];
	int existe;
	sprintf(sql, "SELECT COUNT(*) FROM Prenda WHERE idProducto = %i", idCalzado);
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
*/



// -------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------ ADMINISTRADOR ----------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------

/*
void eliminarCalzados(sqlite3 *db, int idCompra){
    sqlite3_stmt *stmt;
    sqlite3_open("bbdd.db", &db);

    char sql[100];
    sprintf(sql, "DELETE FROM compra WHERE idCompra = %i", idCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

    sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void agregarCalzados(sqlite3 *db, int idCompra, int idProducto, int idComprador, int cantidad, float precioCompra) 
{
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);
	
	char sql[100];
	sprintf(sql, "INSERT INTO compra VALUES (%i, %s, %f, %i ,%i)", idCompra, idProducto, idComprador,cantidad, precioCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);

}
*/





// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- CLIENTE -------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
/*
void eliminarCalzados(sqlite3 *db, int idCompra){
    sqlite3_stmt *stmt;
    sqlite3_open("bbdd.db", &db);

    char sql[100];
    sprintf(sql, "DELETE FROM compra WHERE idCompra = %i", idCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

    sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void agregarCalzados(sqlite3 *db, int idCompra, int idProducto, int idComprador, int cantidad, float precioCompra) 
{
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);
	
	char sql[100];
	sprintf(sql, "INSERT INTO compra VALUES (%i, %s, %f, %i ,%i)", idCompra, idProducto, idComprador,cantidad, precioCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);

}
*/








// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- COMPRAS --------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
int showAllCompras(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[] = "select id, name from COMPRAS";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (SELECT)\n");

	int id;
	char name[100];

	printf("\n");
	printf("\n");
	printf("Showing COMPRAS:\n");
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);
			strcpy(name, (char *) sqlite3_column_text(stmt, 1));
			printf("ID: %d Name: %s\n", id, name);
		}
	} while (result == SQLITE_ROW);

	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return SQLITE_OK;
}



void eliminarTodasLasCompras(sqlite3 *db, int idCompra)
{
	sqlite3_stmt *stmt;

	char sql[] = "Borrar todos las compras !";

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (DELETE)\n");

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (DELETE)\n");

	return SQLITE_OK;
}


void eliminarCalzados(sqlite3 *db, int idCompra){
    sqlite3_stmt *stmt;
    sqlite3_open("bbdd.db", &db);

    char sql[100];
    sprintf(sql, "DELETE FROM compra WHERE idCompra = %i", idCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

    sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);
}

void agregarCalzados(sqlite3 *db, int idCompra, int idProducto, int idComprador, int cantidad, float precioCompra) 
{
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db", &db);
	
	char sql[100];
	sprintf(sql, "INSERT INTO compra VALUES (%i, %s, %f, %i ,%i)", idCompra, idProducto, idComprador,cantidad, precioCompra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
	sqlite3_close(db);

}

