#include "Administrador.h"
#include "Productos.h"
#include "sqlite3.h"
#include "BaseDatos.h"
#include "LoggerBD.h"

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

    char sql[100];
    sprintf(sql, "SELECT MAX(idProducto) FROM Producto");
	
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int maximo = 0;
    if(result == SQLITE_ROW){
        maximo = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Calculado identificativo maximo de productos.");
	return maximo;
}


int eliminarProducto(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;

    char sql[100];
    sprintf(sql, "DELETE FROM Producto WHERE idProducto = %i", id);
	
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

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

	loggerTxt("Eliminado producto.");
	return SQLITE_OK;
}


int agregarProducto(sqlite3 *db, int id, char* tipo, char* nombre) {
    sqlite3_stmt *stmt;
	
	char sql[100];
	sprintf(sql, "INSERT INTO Producto VALUES (%i, '%s', '%s')", id, tipo, nombre);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Agregado producto nuevo.");
	return SQLITE_OK;
}

char obtenerTipoProducto (sqlite3 *db, int id) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT tipoProducto FROM Producto WHERE idProducto = %i", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	char* tipo;
	tipo = malloc(10*sizeof(char));
    if (result == SQLITE_ROW){
        strcpy(tipo, (char*)sqlite3_column_text(stmt, 0));
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return result;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Obtenido tipo producto");
	return tipo[0];				// C -> calzado		P -> prenda
}


int obtenerIdProducto (sqlite3 *db, char* nombre) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT idProducto FROM Producto WHERE nombreProducto = %s", nombre);
	
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int id = 0;
    if (result == SQLITE_ROW){
        id = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Obtenido identificador de producto");
	return id;	
}


bool existeProducto (sqlite3 *db, int id) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Producto WHERE idProducto = %i", id);
	
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
    int existe = 0;
    if (result == SQLITE_ROW){
        existe = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
    }
	bool respuesta;
	if (existe == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Comprobada existencia de producto.");
	return respuesta;	
}


bool existeProducto2 (sqlite3 *db, char* nombre) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Producto WHERE nombreProducto = %s", nombre);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
    int existe = 0;
    if (result == SQLITE_ROW){
        existe = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
	bool respuesta;
	if (existe == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Comprobada existencia de producto");
	return respuesta;	
}


int sizeProductos(sqlite3 *db){
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Producto");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int size = 0;
    if (result == SQLITE_ROW){
        size = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Calculado numero de productos");
	return size;
}


int mostrarProductos (sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
    sprintf(sql, "SELECT * FROM Producto");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int size = sizeProductos(db);

	int i=0;
	int id;
	char tipo[10];

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);
			strcpy(tipo, (char *) sqlite3_column_text(stmt, 1));
			if (strcmp(tipo, "Prenda") == 0) {
				Prenda prenda = obtenerPrenda (db, id);
				printf("%i: %s [%f] x %i. TALLA: %i \n", id, prenda.nombrePrenda, prenda.precioPrenda, prenda.stockPrenda, prenda.tallaPrenda);
			} else if (strcmp(tipo, "Calzado") == 0) {
				Calzado calzado = obtenerCalzado (db, id);
				printf("%i: %s [%f] x %i. TALLA: %i \n", id, calzado.nombreCalzado, calzado.precioCalzado, calzado.stockCalzado, calzado.tallaCalzado);
			}
			i++;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
	} while (i<size);

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Mostrados productos");
	return SQLITE_OK;
}


int eliminarProductos (sqlite3 *db) {
	sqlite3_stmt *stmt;

	eliminarTodasLasPrenda(db);
	eliminarTodasLosCalzados(db);

	char sql[100];
    sprintf(sql, "DELETE FROM Producto");

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

	loggerTxt("Eliminados todos los productos");
	return SQLITE_OK;

}



// -------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- PRENDA -------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------


Prenda obtenerPrenda (sqlite3 *db, int id) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT * FROM Prenda WHERE idPrenda = %i",id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int iden, stock, talla;
	char *nombre;
	float  precio;
	nombre = malloc(100*sizeof(char));
	Prenda prenda;

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		iden = (int)sqlite3_column_int(stmt, 0);
		strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
		precio = (float)sqlite3_column_double(stmt, 2);
		stock = (int)sqlite3_column_int(stmt, 3);
		talla = (int)sqlite3_column_int(stmt, 4);
	} else{
		printf("Error selecting data\n");
		iden = -1;
		strcpy(nombre, "nada");
		precio = 0.0;
		stock = 0;
		talla = 0;
	}

	prenda.idPrenda = iden;
	prenda.nombrePrenda = nombre;
	prenda.precioPrenda = precio;
	prenda.stockPrenda = stock;
	prenda.tallaPrenda = talla;

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Obtenido prenda");
	return prenda;
}


int agregarPrenda (sqlite3 *db, int id, char* nom, float precio, int stock, float talla) {
    sqlite3_stmt *stmt;

	agregarProducto(db, id, "Prenda", nom);

	char sql[100];
	sprintf(sql, "INSERT INTO Prenda VALUES (%i, '%s', %f, %i, %f)", id, nom, precio, stock, talla);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Agregada prenda nueva");
	return SQLITE_OK;
}


int subirStockPrenda (sqlite3 *db, int id, int cant) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "UPDATE Prenda SET stockPrenda = stockPrenda + %i WHERE idPrenda = %i", cant, id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	
	loggerTxt("Recargar prenda");
	return SQLITE_OK;
}


int eliminarPrenda (sqlite3 *db, int id) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "DELETE Prenda WHERE idPrenda = %i", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

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

	loggerTxt("Eliminada prenda");
	return SQLITE_OK;
}


int eliminarTodasLasPrenda(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "DELETE FROM Prenda");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

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

	loggerTxt("Eliminadas todas las prendas");
	return SQLITE_OK;
}


bool existePrenda (sqlite3 *db, int idPrenda) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Prenda WHERE idPrenda = %i", idPrenda);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return false;
	}

	result = sqlite3_step(stmt);
    int existe = 0;
    if (result == SQLITE_ROW){
        existe = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return false;
    }
	bool respuesta;
	if (existe == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return false;
	}

	loggerTxt("Comprobada existencia de prenda");
	return respuesta;
}


// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- CALZADO --------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------

Calzado obtenerCalzado (sqlite3 *db, int id) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT * FROM Calzado WHERE idCalzado = %i",id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int iden, stock, talla;
	char *nombre;
	float  precio;
	nombre = malloc(100*sizeof(char));
	Calzado calzado;

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		iden = (int)sqlite3_column_int(stmt, 0);
		strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
		precio = (float)sqlite3_column_double(stmt, 2);
		stock = (int)sqlite3_column_int(stmt, 3);
		talla = (int)sqlite3_column_int(stmt, 4);
	} else{
		printf("Error selecting data\n");
		iden = -1;
		strcpy(nombre, "nada");
		precio = 0.0;
		stock = 0;
		talla = 0;
	}

	calzado.idCalzado = iden;
	calzado.nombreCalzado = nombre;
	calzado.precioCalzado = precio;
	calzado.stockCalzado = stock;
	calzado.tallaCalzado = talla;

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Obtenido calzado");
	return calzado;
}


int agregarCalzado(sqlite3 *db, int id, char* nom, float precio, int stock, float talla) {
	sqlite3_stmt *stmt;

	agregarProducto(db, id, "Calzado", nom);

	char sql[100];
	sprintf(sql, "INSERT INTO Calzado VALUES (%i, '%s', %f, %i, %f)", id, nom, precio, stock, talla);


	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Agregado calzado nuevo");
	return SQLITE_OK;
}


int subirStockCalzado (sqlite3 *db, int id, int cant) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "UPDATE Calzado SET stockCalzado = stockCalzado + %i WHERE idCalzado = %i", cant, id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Recargado calzado");
	return SQLITE_OK;
}


int eliminarCalzado(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "DELETE Calzado WHERE idCalzado = %i", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

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

	loggerTxt("Eliminado calzado");
	return SQLITE_OK;
}


int eliminarTodasLosCalzados(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "DELETE FROM Calzado");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

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

	loggerTxt("Eliminados todos los calzados");
	return SQLITE_OK;
}


bool existeCalzados(sqlite3 *db, int idCalzado) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Calzado WHERE idCalzado = %i", idCalzado);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return false;
	}

	result = sqlite3_step(stmt);
    int existe = 0;
    if (result == SQLITE_ROW){
        existe = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return false;
    }
	bool respuesta;
	if (existe == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return false;
	}

	loggerTxt("Comprobada existencia de calzado");
	return respuesta;
}




// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- USUARIOS -------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------


// -------------------------------------------------- COMPRADOR ------------------------------------------------------


int maxIdComprador (sqlite3 *db) {
    sqlite3_stmt *stmt;

    char sql[100];
    sprintf(sql, "SELECT MAX(idComprador) FROM Comprador");
	
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int maximo = 0;
    if(result == SQLITE_ROW){
        maximo = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Calculado identificativo maximo de comprador");
	return maximo;
}


bool obtenerTipoComprador (sqlite3 *db, int id) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT esVip FROM Comprador WHERE idComprador = %i", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return false;
	}

	int esVip;
	bool respuesta;

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		esVip = (int)sqlite3_column_int(stmt, 0);
		if (esVip == 0) {
			respuesta = false;
		} else {
			respuesta = true;
		}
	} else{
		respuesta = false;
		printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return false;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return false;
	}

	loggerTxt("Obtenido tipo de comprador");
	return respuesta;
}



Comprador obtenerComprador (sqlite3 *db, int id) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT * FROM Comprador WHERE idComprador = %i", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int telefono, iden;
	char *nombre, *correo, *direccion, *contrasena;
	nombre = malloc(20*sizeof(char));
	correo = malloc(50*sizeof(char));
	direccion = malloc(60*sizeof(char));
	contrasena = malloc(20*sizeof(char));
	Comprador comprador;

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		iden = (int)sqlite3_column_int(stmt, 0);
		strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
		telefono = (int)sqlite3_column_double(stmt, 2);
		strcpy(correo, (char*)sqlite3_column_text(stmt, 3));
		strcpy(contrasena, (char*)sqlite3_column_text(stmt, 4));
	} else{
		iden = -1;
		strcpy(nombre, "nada");
		telefono = 0;
		strcpy(correo, "nada");
		strcpy(contrasena, "nada");
		printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	comprador.idComprador = iden;
	comprador.nombreComprador = nombre;
	comprador.telefono = telefono;
	comprador.correo = correo;
	comprador.contrasena = contrasena;

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Obtenido comprador");
	return comprador;
}


CompradorVip obtenerCompradorVIP (sqlite3 *db, int id) {
    sqlite3_stmt *stmt;

	Comprador comprador = obtenerComprador(db, id);

	char sql[100];
	sprintf(sql, "SELECT * FROM CompradorVip WHERE idCompradorVIP = %i", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int iden;
	char *nivel;
	nivel = malloc(10*sizeof(char));
	CompradorVip compradorVip;

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		iden = (int)sqlite3_column_int(stmt, 0);
		strcpy(nivel, (char*)sqlite3_column_text(stmt, 1));
	} else{
		iden = -1;
		strcpy(nivel, "standard");
		printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	compradorVip.idCompradorVIP = iden;
	compradorVip.nombreCompradorVIP = comprador.nombreComprador;
	compradorVip.telefono = comprador.telefono;
	compradorVip.correo = comprador.correo;
	compradorVip.contrasena = comprador.contrasena;

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Obtenido comprador VIP");
	return compradorVip;
}


int sizeComprador (sqlite3 *db){
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Comprador");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int size = 0;
    if (result == SQLITE_ROW){
        size = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Obtenido numero de compradores");
	return size;
}


int mostrarCompradores (sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
    sprintf(sql, "SELECT idComprador, esVip FROM Comprador");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int size = sizeComprador (db);

	int i=0;
	int id;
	int esVip;

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);
			esVip = sqlite3_column_int(stmt, 1);
			if (esVip == 0) {
				Comprador comprador = obtenerComprador(db, id);
				printf("%i: %s. [%i]", id, comprador.nombreComprador, comprador.telefono);
			} else if (esVip == 1) {
				CompradorVip comprador = obtenerCompradorVIP(db, id);
				printf("%i: %s. [%i]. VIP: %s", id, comprador.nombreCompradorVIP, comprador.telefono, comprador.nivel);
			}
			i++;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
	} while (i<size);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Mostrados compradores");
	return SQLITE_OK;
}


int eliminarComprador (sqlite3 *db, int id){
    sqlite3_stmt *stmt;

	bool esVip = obtenerTipoComprador(db, id);

	char sql[100];

	if (esVip == true) {
    	sprintf(sql, "DELETE FROM CompradorVip WHERE idCompradorVIP = %i", id);

		int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
		if (result != SQLITE_OK) {
			printf("Error preparing statement (DELETE)\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}

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

		return SQLITE_OK;
	}

    sprintf(sql, "DELETE FROM Comprador WHERE idComprador = %i", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

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

	loggerTxt("Eliminado comprador");
	return SQLITE_OK;
}


int agregarComprador (sqlite3 *db, int id, char* nombre, int telefono, char* correo, char* direccion, char* contrasena) {
	sqlite3_stmt *stmt;
	
	char sql[100];
	sprintf(sql, "INSERT INTO Comprador VALUES (%i, '%s', %i, '%s', '%s', '%s')", id, nombre, telefono, correo, direccion, contrasena);
	
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

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

	loggerTxt("Agregado comprador nuevo");
	return SQLITE_OK;

}


int agregarCompradorVIP (sqlite3 *db, int id, char* nombre, int telefono, char* correo, char* direccion, char* contrasena, char* nivel)  {
	sqlite3_stmt *stmt;

	agregarComprador (db, id, nombre, telefono, correo, direccion, contrasena);
	
	char sql[100];
	sprintf(sql, "INSERT INTO CompradorVip VALUES (%i, '%s')", id, nivel);
	
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

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

	loggerTxt("Agregado comprador VIP nuevo");
	return SQLITE_OK;
}


bool existeComprador (sqlite3 *db, int id) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Comprador WHERE idComprador = %i", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return false;
	}

	result = sqlite3_step(stmt);
    int existe = 0;
    if (result == SQLITE_ROW){
        existe = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return false;
    }
	bool respuesta;
	if (existe == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return false;
	}

	loggerTxt("Comprobada existencia de comprador");
	return respuesta;
}



// -------------------------------------------------------------------------------------------------------------------


Administrador obtenerAdmin(sqlite3 *db, int id) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT * FROM Administrador WHERE idAdmin = %d", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	char *nombre, *contrasena;
	nombre = malloc(20*sizeof(char));
	contrasena = malloc(20*sizeof(char));
	Administrador admin;

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		strcpy(nombre, (char*)sqlite3_column_text(stmt, 1));
		strcpy(contrasena, (char*)sqlite3_column_text(stmt, 2));
	} else{
		printf("Error selecting data\n");
		strcpy(nombre, "nada");
		strcpy(contrasena, "nada");
	}

	admin.idAdmin = id;
	admin.nombreAdmin = nombre;
	admin.contrasena = contrasena;

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Obtenido administrador");
	return admin;
}


bool existeAdmin(sqlite3 *db, int id) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Administrador WHERE idAdmin = %d", id);
	
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
    int existe = 0;
    if (result == SQLITE_ROW){
        existe = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
	bool respuesta;
	if (existe == 0) {
		respuesta = false;
	} else {
		respuesta = true;
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Comprobada existencia de administrador");
	return respuesta;	
}



// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- COMPRAS --------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------


int maxIdCompra (sqlite3 *db) {
    sqlite3_stmt *stmt;

    char sql[100];
    sprintf(sql, "SELECT MAX(idCompra) FROM Compra");
	
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int maximo = 0;
    if(result == SQLITE_ROW){
        maximo = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Calculado identificativo maximo de compra.");
	return maximo;
}


int agregarCompra (sqlite3 *db, int idCompra, int idProducto, int idComprador, float precioCompra) {
    sqlite3_stmt *stmt;
	
	char sql[100];
	sprintf(sql, "INSERT INTO Compra VALUES (%i, %i, %i, %f)", idCompra, idProducto, idComprador, precioCompra);
	
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Agregada compra nueva");
	return SQLITE_OK;
}


int sizeCompras(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Compra");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int size = 0;
    if (result == SQLITE_ROW){
        size = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Calculado numero de compras");
	return size;
}


int mostrarCompras (sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
    sprintf(sql, "SELECT * FROM Compra");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int size = sizeCompras(db);
	int i = 0;

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			int idCompra = sqlite3_column_int(stmt, 0);
			int idProducto = sqlite3_column_int(stmt, 1);
			int idComprador = sqlite3_column_int(stmt, 2);
			float precio = sqlite3_column_int(stmt, 3);
			printf("%i: %i [Comprador: %i]. %f€ \n", idCompra, idProducto, idComprador, precio);
			
			i++;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
	} while (i<size);

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Mostradas compras");
	return SQLITE_OK;
}

/**
int mostrarComprasComprador (sqlite3 *db, int idCompra, int idComprador) {
	sqlite3_stmt *stmt;

	char sql[100];
	if (idCompra == -1) {
    	sprintf(sql, "SELECT * FROM Compra WHERE idComprador = %i", idComprador);
	} else {
		sprintf(sql, "SELECT * FROM Compra WHERE idComprador = %i AND idCompra = %i", idComprador, idCompra);
	}

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int size = sizeCompras(db);
	int i = 0;

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			int idCompra = sqlite3_column_int(stmt, 0);
			int idProducto = sqlite3_column_int(stmt, 1);
			int idComprador = sqlite3_column_int(stmt, 2);
			float precio = sqlite3_column_float(stmt, 3);
			printf("%i: %i [Comprador: %i]. %f€ \n", idCompra, idProducto, idComprador, precio);
			
			i++;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
	} while (i<size);

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Mostradas compras concretas");
	return SQLITE_OK;
}
**/



// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- SERVER --------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------


int sizePrendas(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Prenda");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int size = 0;
    if (result == SQLITE_ROW){
        size = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Calculado numero de prendas");
	return size;
}


int sizeCalzados(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Calzado");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int size = 0;
    if (result == SQLITE_ROW){
        size = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Calculado numero de calzados");
	return size;
}


int cargarProductos (sqlite3 *db, Prenda** prendas, Calzado** calzados, int* numPrendas, int* numCalzado, int* numProductos) {

    sqlite3_stmt *stmt;

	*numProductos = sizeProductos(db);
	*numPrendas = sizePrendas(db);
	*numCalzado = sizeCalzados(db);

	int countP = 0;
	int countC = 0;


	char sql[100];
    sprintf(sql, "SELECT * FROM Producto");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int i=0;
	int id;
	char tipo[10];

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);
			strcpy(tipo, (char *) sqlite3_column_text(stmt, 1));
			if (strcmp(tipo, "Prenda") == 0) {
				Prenda prenda = obtenerPrenda (db, id);
				prendas[countP] = &prenda;
				countP++;
			} else if (strcmp(tipo, "Calzado") == 0) {
				Calzado calzado = obtenerCalzado (db, id);
				calzados[countC] = &calzado;
				countC++;
			}
			i++;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
	} while (i < (*numProductos));

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Creados arrays de prendas y calzados.");
	return SQLITE_OK;

}


int sizeCompras(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Compra");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int size = 0;
    if (result == SQLITE_ROW){
        size = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Calculado numero de compras");
	return size;
}


int cargarCompras (sqlite3 *db, Compra** compras) {

    sqlite3_stmt *stmt;

	int *numCompras = sizeCompras(db);

	int count = 0;


	char sql[100];
    sprintf(sql, "SELECT * FROM Compra");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int i=0;
	int idCompra;
	int idProd;
	int idComprador;
	float precio;

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			idCompra = sqlite3_column_int(stmt, 0);
			idProd = sqlite3_column_int(stmt, 1);
			idComprador = sqlite3_column_int(stmt, 2);
			precio = sqlite3_column_int(stmt, 3);

			Compra compra = {idCompra, idProd, idComprador, precio};
			compras[count] = &compra;
			i++;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
	} while (i < (*numCompras));

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Creados arrays de prendas y calzados.");
	return SQLITE_OK;

}


int sizeCompradores(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Comprador WHERE esVip = 0");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int size = 0;
    if (result == SQLITE_ROW){
        size = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Calculado numero de prendas");
	return size;
}


int sizeCompradoresVip(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM CompradorVip");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int size = 0;
    if (result == SQLITE_ROW){
        size = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Calculado numero de calzados");
	return size;
}


int cargarProductos (sqlite3 *db, Comprador** compradores, CompradorVip** compradoresVip, int* numCompradores, int* numCompradoresVip) {

    sqlite3_stmt *stmt;

	*numCompradores = sizeCompradores(db);
	*numCompradoresVip = sizeCompradoresVip(db);

	int countC = 0;
	int countCV = 0;


	char sql[100];
    sprintf(sql, "SELECT * FROM Comprador");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int i=0;
	int id;
	char* nombre;
	nombre = malloc(sizeof(char)*25);
	int telefono;
	char* correo;
	correo = malloc(sizeof(char)*50);
	char* direccion;
	direccion = malloc(sizeof(char)*50);
	int esVip;
	char* nivel;
	nivel = malloc(sizeof(char)*10);
	char tipo[10];

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);
			strcpy(nombre, (char *) sqlite3_column_text(stmt, 1));
			telefono = sqlite3_column_int(stmt, 2);
			strcpy(correo, (char *) sqlite3_column_text(stmt, 3));
			strcpy(direccion, (char *) sqlite3_column_text(stmt, 4));
			esVip = sqlite3_column_int(stmt, 5);
			if (esVip == 0) {
				Comprador comprador = {id, nombre, telefono, correo, direccion};
				compradores[countC] = &comprador;
				countC++;
			} else {
				CompradorVip compradorVip = obtenerCompradorVIP (db, id);
				compradoresVip[countCV] = &compradorVip;
				countCV++;
			}
			i++;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
	} while (i < (*numCompradores + *numCompradoresVip));

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Creados arrays de prendas y calzados.");
	return SQLITE_OK;

}


int sizeComprasId (sqlite3 *db, int idCompra) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Compra WHERE idCompra = %i", idCompra);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int size = 0;
    if (result == SQLITE_ROW){
        size = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	loggerTxt("Calculado numero de compras");
	return size;
}


int cargarComprasId (sqlite3 *db, Compra** compras, int* numCompras, int idCompra) {

    sqlite3_stmt *stmt;

	*numCompras = sizeComprasId(db, idCompra);

	int count = 0;


	char sql[100];
    sprintf(sql, "SELECT * FROM Compra WHERE idCompra = %i", idCompra);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int i=0;
	int idCompra;
	int idProd;
	int idComprador;
	float precio;

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			idCompra = sqlite3_column_int(stmt, 0);
			idProd = sqlite3_column_int(stmt, 1);
			idComprador = sqlite3_column_int(stmt, 2);
			precio = sqlite3_column_int(stmt, 3);

			Compra compra = {idCompra, idProd, idComprador, precio};
			compras[count] = &compra;
			i++;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
	} while (i < (*numCompras));

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	loggerTxt("Creados arrays de prendas y calzados.");
	return SQLITE_OK;

}




