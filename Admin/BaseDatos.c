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

Producto obtenerProductos (sqlite3 *db, int id) {
	sqlite3_stmt *stmt;

	char sql[100];
    sprintf(sql, "SELECT * FROM Producto WHERE idProducto = %i", id);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int size = sizeProductos(db);

	int i=0;
	char* tipo;
	tipo=malloc(sizeof(char)*30);
	char* nombre;
	nombre = malloc(sizeof(char)*50);
	float precio;
	int stock;
	int talla;

	Producto producto;

	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {
		strcpy(tipo, (char *) sqlite3_column_text(stmt, 1));
		strcpy(nombre, (char *) sqlite3_column_text(stmt, 2));
		precio = sqlite3_column_int(stmt, 3);
		stock = sqlite3_column_int(stmt, 4);
		talla = sqlite3_column_int(stmt, 5);

		Producto pr = {id, tipo, nombre, precio, stock, talla};
		producto = pr;

	} else{
		printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Mostrados productos");
	return producto;
}


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


int agregarProducto(sqlite3 *db, int id, char* tipo, char* nombre, float precio, int stock, int talla) {
    sqlite3_stmt *stmt;
	
	char sql[200];
	sprintf(sql, "INSERT INTO Producto VALUES (%i, '%s', '%s', %f, %i, %i)", id, tipo, nombre, precio, stock, talla);

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
	char* tipo = (char*)malloc(sizeof(char)*10);
    if (result == SQLITE_ROW){
		strcpy(tipo, (char *) sqlite3_column_text(stmt, 0));
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
	sprintf(sql, "SELECT idProducto FROM Producto WHERE nombreProducto = '%s'", nombre);
	
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
	sprintf(sql, "SELECT COUNT(*) FROM Producto WHERE nombreProducto = '%s'", nombre);

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
	char* tipo;
	tipo = malloc(sizeof(char)*30);
	char* nombre;
	nombre = malloc(sizeof(char)*50);
	float precio;
	int stock;
	int talla;

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);
			strcpy(tipo, (char *) sqlite3_column_text(stmt, 1));
			strcpy(nombre, (char *) sqlite3_column_text(stmt, 2));
			precio = sqlite3_column_int(stmt, 3);
			stock = sqlite3_column_int(stmt, 4);
			talla = sqlite3_column_int(stmt, 5);
			printf("%i: %s: %s [%f] x %i. TALLA: %i \n", id, tipo, nombre, precio, stock, talla);
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


int subirStock (sqlite3 *db, int id, int cant) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "UPDATE Producto SET stockProducto = stockProducto + %i WHERE idProducto = %i", cant, id);

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
	
	loggerTxt("Recargado producto");
	return SQLITE_OK;
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


bool obtenerTipoCompradorCorreo (sqlite3 *db, char* correo) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT esVip FROM Comprador WHERE correo = '%s'", correo);

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
		strcpy(direccion, (char*)sqlite3_column_text(stmt, 3));
		strcpy(correo, (char*)sqlite3_column_text(stmt, 4));
		strcpy(contrasena, (char*)sqlite3_column_text(stmt, 5));
	} else{
		iden = -1;
		strcpy(nombre, "nada");
		telefono = 0;
		strcpy(direccion, "nada");
		strcpy(correo, "nada");
		strcpy(contrasena, "nada");
		printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	comprador.idComprador = iden;
	comprador.nombreComprador = nombre;
	comprador.telefono = telefono;
	comprador.direccion = direccion;
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


Comprador obtenerCompradorCorreo (sqlite3 *db, char* correo) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT * FROM Comprador WHERE correo = '%s'", correo);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int telefono, iden;
	char *nombre, *direccion, *contrasena;
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
		strcpy(direccion, (char*)sqlite3_column_text(stmt, 3));
		strcpy(contrasena, (char*)sqlite3_column_text(stmt, 5));
	} else{
		iden = -1;
		strcpy(nombre, "nada");
		telefono = 0;
		strcpy(direccion, "nada");
		strcpy(correo, "nada");
		strcpy(contrasena, "nada");
		printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	comprador.idComprador = iden;
	comprador.nombreComprador = nombre;
	comprador.telefono = telefono;
	comprador.direccion = direccion;
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

	char *nivel;
	nivel = malloc(15*sizeof(char));
	CompradorVip compradorVip;

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		strcpy(nivel, (char*)sqlite3_column_text(stmt, 1));
	} else{
		id = -1;
		strcpy(nivel, "standard");
		printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	compradorVip.idCompradorVIP = id;
	compradorVip.nombreCompradorVIP = comprador.nombreComprador;
	compradorVip.telefono = comprador.telefono;
	compradorVip.direccion = comprador.direccion;
	compradorVip.correo = comprador.correo;
	compradorVip.contrasena = comprador.contrasena;
	compradorVip.nivel = nivel;

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Obtenido comprador VIP");
	return compradorVip;
}


CompradorVip obtenerCompradorVIPCorreo (sqlite3 *db, char* correo) {
    sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT * FROM CompradorVip WHERE correo = '%s'", correo);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int id;
	char *nivel;
	nivel = malloc(15*sizeof(char));
	CompradorVip compradorVip;

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		id = sqlite3_column_int(stmt, 0);
		strcpy(nivel, (char*)sqlite3_column_text(stmt, 1));
	} else{
		id = -1;
		strcpy(nivel, "standard");
		printf("Error selecting data\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	Comprador comprador = obtenerComprador(db, id);

	compradorVip.idCompradorVIP = id;
	compradorVip.nombreCompradorVIP = comprador.nombreComprador;
	compradorVip.telefono = comprador.telefono;
	compradorVip.direccion = comprador.direccion;
	compradorVip.correo = comprador.correo;
	compradorVip.contrasena = comprador.contrasena;
	compradorVip.nivel = nivel;

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Obtenido comprador VIP");
	return compradorVip;
}


int sizeCompradores (sqlite3 *db){
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

	int size = sizeCompradores (db);

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
				printf("%i: %s. [%i] \n", id, comprador.nombreComprador, comprador.telefono);
			} else if (esVip == 1) {
				CompradorVip compradorV = obtenerCompradorVIP(db, id);
				printf("%i: %s. [%i]. VIP: %s \n", id, compradorV.nombreCompradorVIP, compradorV.telefono, compradorV.nivel);
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

		loggerTxt("Eliminado comprador.");
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


int agregarComprador (sqlite3 *db, int id, char* nombre, int telefono, char* correo, char* direccion, char* contrasena, int esVip) {
	sqlite3_stmt *stmt;
	
	char sql[150];
	sprintf(sql, "INSERT INTO Comprador VALUES (%i, '%s', %i, '%s', '%s', '%s', %i)", id, nombre, telefono, correo, direccion, contrasena, esVip);
	
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

	loggerTxt("Agregado comprador nuevo");
	return SQLITE_OK;

}


int agregarCompradorVIP (sqlite3 *db, int id, char* nombre, int telefono, char* correo, char* direccion, char* contrasena, char* nivel)  {
	sqlite3_stmt *stmt;

	agregarComprador (db, id, nombre, telefono, correo, direccion, contrasena, 1);
	
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


bool existeCompradorIniciar (sqlite3 *db, char* correo, char* contrasena) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Comprador WHERE correo = '%s' AND contrasena = '%s'", correo, contrasena);

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


int sizeComprasReales(sqlite3* db){
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(DISTINCT idCompra) FROM Compra ");

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


bool existeCompra (sqlite3 *db, int idCompra, int idProducto, int idComprador) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT COUNT(*) FROM Compra WHERE idCompra = %i AND idProducto = %i AND idComprador = %i", idCompra, idProducto, idComprador);
	
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

	loggerTxt("Comprobada existencia de compra.");
	return respuesta;	
}


int eliminarCompra (sqlite3 *db, int idCompra, int idProducto, int idComprador) {
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "DELETE FROM Compra WHERE idCompra = %i AND idProducto = %i AND idComprador = %i", idCompra, idProducto, idComprador);

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

	loggerTxt("Eliminada compra.");
	return SQLITE_OK;
}




// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------- SERVER --------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------


Producto** cargarProductos (sqlite3 *db) {

	sqlite3_stmt *stmt;

	Producto** productos;
	int numProductos = sizeProductos(db);
	productos = (Producto**) malloc(sizeof(Producto*)*numProductos);

	for (int i = 0; i < numProductos; i++) {
		productos[i] = (Producto*)malloc(sizeof(Producto));
	}

	char sql[100];
    sprintf(sql, "SELECT * FROM Producto");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int id;

	for (int i = 0; i < numProductos; i++) {

		result = sqlite3_step(stmt);

		if (result == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);

			Producto pr = obtenerProductos (db, id);
			//printf("Producto %i: %s\n", pr.idProducto, pr.nombreProducto);

			productos[i]->idProducto = pr.idProducto;
			productos[i]->tipoProducto = malloc(strlen(pr.tipoProducto)+1);
			strcpy(productos[i]->tipoProducto, pr.tipoProducto);
			productos[i]->nombreProducto = malloc(strlen(pr.nombreProducto)+1);
			strcpy(productos[i]->nombreProducto, pr.nombreProducto);
			productos[i]->precioProducto = pr.precioProducto;
			productos[i]->stockProducto = pr.stockProducto;
			productos[i]->tallaProducto = pr.tallaProducto;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
	} 

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Creados arrays de prendas y calzados.");
	return productos;

}


Compra** cargarComprasId (sqlite3 *db, int idCompra) {

    sqlite3_stmt *stmt;

	Compra** compras;
	int numCompras = sizeComprasId(db, idCompra);
	compras = (Compra**) malloc(sizeof(Compra*)*numCompras);

	for (int i = 0; i < numCompras; i++) {
		compras[i] = (Compra*)malloc(sizeof(Compra));
	}

	char sql[100];
    sprintf(sql, "SELECT * FROM Compra WHERE idCompra = %i", idCompra);

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int idProd;
	int idComprador;
	float precio;

	for (int i = 0; i < numCompras; i++) {

		result = sqlite3_step(stmt);
		
		if (result == SQLITE_ROW) {
			idProd = sqlite3_column_int(stmt, 1);
			idComprador = sqlite3_column_int(stmt, 2);
			precio = sqlite3_column_double(stmt, 3);

			compras[i]->idCompra = idCompra;
			compras[i]->idProducto = idProd;
			compras[i]->idComprador = idComprador;
			compras[i]->precioCompra = precio;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
	}

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Creados arrays de prendas y calzados.");
	return compras;

}


Compra** cargarCompras (sqlite3 *db) {

    sqlite3_stmt *stmt;

	Compra** compras;
	int numCompras = sizeCompras(db);
	compras = (Compra**) malloc(sizeof(Compra*)*numCompras);

	for (int i = 0; i < numCompras; i++) {
		compras[i] = (Compra*)malloc(sizeof(Compra));
	}

	char sql[100];
    sprintf(sql, "SELECT * FROM Compra");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int idCompra;
	int idProd;
	int idComprador;
	float precio;

	for (int i = 0; i < numCompras; i++) {

		result = sqlite3_step(stmt);
		
		if (result == SQLITE_ROW) {
			idCompra = sqlite3_column_int(stmt, 0);
			idProd = sqlite3_column_int(stmt, 1);
			idComprador = sqlite3_column_int(stmt, 2);
			precio = sqlite3_column_double(stmt, 3);

			compras[i]->idCompra = idCompra;
			compras[i]->idProducto = idProd;
			compras[i]->idComprador = idComprador;
			compras[i]->precioCompra = precio;

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
	}

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Creados arrays de compras.");
	return compras;

}


Comprador** cargarCompradores (sqlite3 *db) {

    sqlite3_stmt *stmt;

	Comprador** compradores;
	int numCompradores = sizeCompradores(db);
	compradores=(Comprador**) malloc(sizeof(Comprador*)*numCompradores);
	
	for (int i = 0; i < numCompradores; i++) {
		compradores[i]=(Comprador*)malloc(sizeof(Comprador));
	}

	char sql[100];
    sprintf(sql, "SELECT * FROM Comprador");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int id;

	for (int i = 0; i < numCompradores; i++) {

		result = sqlite3_step(stmt);
		
		if (result == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);

			Comprador com = obtenerComprador(db, id);

			compradores[i]->idComprador = id;
			compradores[i]->nombreComprador = malloc(strlen(com.nombreComprador)+1);
			strcpy(compradores[i]->nombreComprador, com.nombreComprador);
			compradores[i]->telefono = com.telefono;
			compradores[i]->correo = malloc(strlen(com.correo)+1);
			strcpy(compradores[i]->correo, com.correo);
			compradores[i]->direccion = malloc(strlen(com.direccion)+1);
			strcpy(compradores[i]->direccion, com.direccion);

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
	}

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Creados arrays de compradores.");
	return compradores;

}


Comprador** cargarCompradoresNormales (sqlite3 *db) {

    sqlite3_stmt *stmt;

	Comprador** compradores;
	int numCompradores = sizeCompradores(db) - sizeCompradoresVip(db);
	compradores=(Comprador**) malloc(sizeof(Comprador*)*numCompradores);
	
	for (int i = 0; i < numCompradores; i++) {
		compradores[i]=(Comprador*)malloc(sizeof(Comprador));
	}

	char sql[100];
    sprintf(sql, "SELECT * FROM Comprador WHERE esVip = 0");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int id;

	for (int i = 0; i < numCompradores; i++) {

		result = sqlite3_step(stmt);
		
		if (result == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);

			Comprador com = obtenerComprador(db, id);

			compradores[i]->idComprador = id;
			compradores[i]->nombreComprador = malloc(strlen(com.nombreComprador)+1);
			strcpy(compradores[i]->nombreComprador, com.nombreComprador);
			compradores[i]->telefono = com.telefono;
			compradores[i]->correo = malloc(strlen(com.correo)+1);
			strcpy(compradores[i]->correo, com.correo);
			compradores[i]->direccion = malloc(strlen(com.direccion)+1);
			strcpy(compradores[i]->direccion, com.direccion);
			compradores[i]->contrasena = malloc(strlen(com.contrasena)+1);
			strcpy(compradores[i]->contrasena, com.contrasena);

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
	}

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Creados arrays de compradores normales.");
	return compradores;

}



CompradorVip** cargarCompradoresVIP (sqlite3 *db) {

    sqlite3_stmt *stmt;

	CompradorVip** compradores;
	int numCompradores = sizeCompradoresVip(db);
	compradores = (CompradorVip**) malloc(sizeof(CompradorVip*)*numCompradores);

	for (int i = 0; i < numCompradores; i++) {
		compradores[i]=(CompradorVip*)malloc(sizeof(CompradorVip));
	}

	char sql[100];
    sprintf(sql, "SELECT * FROM Comprador WHERE esVip = 1");

	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	int id;

	for (int i = 0; i < numCompradores; i++) {

		result = sqlite3_step(stmt);
		
		if (result == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);

			CompradorVip com = obtenerCompradorVIP(db, id);

			compradores[i]->idCompradorVIP = id;
			compradores[i]->nombreCompradorVIP = malloc(strlen(com.nombreCompradorVIP)+1);
			strcpy(compradores[i]->nombreCompradorVIP, com.nombreCompradorVIP);
			compradores[i]->telefono = com.telefono;
			compradores[i]->correo = malloc(strlen(com.correo)+1);
			strcpy(compradores[i]->correo, com.correo);
			compradores[i]->direccion = malloc(strlen(com.direccion)+1);
			strcpy(compradores[i]->direccion, com.direccion);
			compradores[i]->contrasena = malloc(strlen(com.contrasena)+1);
			strcpy(compradores[i]->contrasena, com.contrasena);
			compradores[i]->nivel = malloc(strlen(com.nivel)+1);
			strcpy(compradores[i]->nivel, com.nivel);

		} else{
			printf("Error selecting data\n");
			printf("%s\n", sqlite3_errmsg(db));
		}
	}

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	loggerTxt("Creados arrays de compradores vip.");
	return compradores;

}







