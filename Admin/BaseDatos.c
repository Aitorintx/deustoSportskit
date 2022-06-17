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

	return maximo;
}


int eliminarProducto(sqlite3 *db, int id){
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
		return 0;
	}

	return SQLITE_OK;
}


int agregarProducto(sqlite3 *db, int id, char* tipo, char* nombre) {
    sqlite3_stmt *stmt;
	
	char sql[100];
	sprintf(sql, "INSERT INTO Producto VALUES (%i, %s, %s)", id, tipo, nombre);
	
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
		return 0;
	}

	result = sqlite3_step(stmt);
	char* tipo;
	tipo = malloc(10*sizeof(char));
    if (result == SQLITE_ROW){
        strcpy(tipo, (char*)sqlite3_column_text(stmt, 0));
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
		return 0;
	}

	result = sqlite3_step(stmt);
    int existe = 0;
    if (result == SQLITE_ROW){
        existe = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
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
		return 0;
	}

	return respuesta;	
}


bool existeProducto2 (sqlite3 *db, char* nombre) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Producto WHERE nombreProducto = %s", nombre);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int existe = 0;
    if (result == SQLITE_ROW){
        existe = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
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
		return 0;
	}

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
		return 0;
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
				printf("%i: %s [%f] x %i. TALLA: %i", id, prenda.nombrePrenda, prenda.precioPrenda, prenda.stockPrenda, prenda.tallaPrenda);
			} else if (strcmp(tipo, "Calzado") == 0) {
				Calzado calzado = obtenerCalzado (db, id);
				printf("%i: %s [%f] x %i. TALLA: %i", id, calzado.nombreCalzado, calzado.precioCalzado, calzado.stockCalzado, calzado.tallaCalzado);
			}
			i++;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
			return 0;
		}
	} while (i<size);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
}

void eliminarProductos (sqlite3 *db) {
	sqlite3_stmt *stmt;

	eliminarTodasLasPrenda(db);
	eliminarTodasLosCalzados(db);

	char sql[100];
    sprintf(sql, "DELETE FROM Producto");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	printf("SQL query prepared (DELETE)\n");

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

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

	return prenda;
}


int agregarPrenda (sqlite3 *db, int id, char* nom, float precio, int stock, float talla) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "INSERT INTO Prenda VALUES (%i, %s, %f, %i, %f)", id, nom, precio, stock, talla);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
}


int subirStockPrenda (sqlite3 *db, int id, int cant) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "UPDATE Prenda SET stockPrenda = stockPrenda + %i WHERE idPrenda = %i", cant, id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
}


int eliminarPrenda (sqlite3 *db, int id) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "DELETE Prenda WHERE idPrenda = %i", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
}


int eliminarTodasLasPrenda(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "DELETE FROM Prenda");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
}


bool existePrenda (sqlite3 *db, int idPrenda) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Prenda WHERE idPrenda = %i", idPrenda);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int existe = 0;
    if (result == SQLITE_ROW){
        existe = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
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
		return 0;
	}

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

	return calzado;
}


int agregarCalzado(sqlite3 *db, int id, char* nom, float precio, int stock, float talla) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "INSERT INTO Calzado VALUES (%i, %s, %f, %i, %f)", id, nom, precio, stock, talla);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
}


int subirStockCalzado (sqlite3 *db, int id, int cant) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "UPDATE Calzado SET stockCalzado = stockCalzado + %i WHERE idCalzado = %i", cant, id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
}


int eliminarCalzado(sqlite3 *db, int id) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "DELETE Calzado WHERE idCalzado = %i", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
}


int eliminarTodasLosCalzados(sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "DELETE FROM Calzado");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error deleting data\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (DELETE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
}


bool existeCalzados(sqlite3 *db, int idCalzado) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Calzado WHERE idCalzado = %i", idPrenda);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int existe = 0;
    if (result == SQLITE_ROW){
        existe = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
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
		return 0;
	}

	return respuesta;
}




// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- CLIENTES -------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------

/**
Comprador obtenerComprador (sqlite3 *db, int id) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT * FROM Comprador WHERE idComprador = %i", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int telefono, esVip;
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

	return prenda;
}
**/

int sizeClientes (sqlite3 *db){
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

	return size;
}


int mostrarClientes (sqlite3 *db) {
	sqlite3_stmt *stmt;

	char sql[100];
    sprintf(sql, "SELECT * FROM Comprador");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	int size = sizeClientes (db);

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
				printf("%i: %s [%f] x %i. TALLA: %i", id, prenda.nombrePrenda, prenda.precioPrenda, prenda.stockPrenda, prenda.tallaPrenda);
			} else if (strcmp(tipo, "Calzado") == 0) {
				Calzado calzado = obtenerCalzado (db, id);
				printf("%i: %s [%f] x %i. TALLA: %i", id, calzado.nombreCalzado, calzado.precioCalzado, calzado.stockCalzado, calzado.tallaCalzado);
			}
			i++;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
			return 0;
		}
	} while (i<size);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}
}


int showAllUsuarios(sqlite3 *db) {
	sqlite3_stmt *stmt;
	sqlite3_open("bbdd.db",&db);

	char sql[100];

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

	return admin;
}


int existeAdmin(sqlite3 *db, int id) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Administrador WHERE idAdmin = %d", id);
	
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
    int existe = 0;
    if (result == SQLITE_ROW){
        existe = sqlite3_column_int(stmt, 0);
    } else{
        printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
        return 0;
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
		return 0;
	}

	return respuesta;	
}





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

/**
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

**/