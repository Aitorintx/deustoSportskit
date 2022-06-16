#ifndef BASEDATOS_H_
#define BASEDATOS_H_


#include <stdbool.h>

// ------------------------------------------------- PRODUCTOS -------------------------------------------------------

int maxIdProducto (sqlite3 *db);
void eliminarProducto(sqlite3 *db, int id);
void agregarProducto(sqlite3 *db, int id, char* tipo, char* nombre);
char obtenerTipoProducto (sqlite3 *db, int id);
int obtenerIdProducto (sqlite3 *db, char* nombre);
bool existeProducto (sqlite3 *db, int id);
bool existeProducto2 (sqlite3 *db, char* nombre);





// ------------------------------------------------- ADMINISTRADOR -------------------------------------------------------

Administrador obtenerAdmin(sqlite3 *db, int id);
int existeAdmin(sqlite3 *db, int id);


#endif