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

// ------------------------ PRENDA ---------------------------

Prenda obtenerPrenda (sqlite3 *db, int id);
void agregarPrenda (sqlite3 *db, int id, char* nom, float precio, int stock, float talla);
void subirStockPrenda (sqlite3 *db, int id, int cant);
void eliminarPrenda (sqlite3 *db, int id);


// ------------------------ CALZADO --------------------------

Calzado obtenerCalzado (sqlite3 *db, int id);
void agregarCalzado(sqlite3 *db, int id, char* nom, float precio, int stock, float talla);
void subirStockCalzado (sqlite3 *db, int id, int cant);
void eliminarCalzado(sqlite3 *db, int id);


// ------------------------------------------------- ADMINISTRADOR -------------------------------------------------------

Administrador obtenerAdmin(sqlite3 *db, int id);
int existeAdmin(sqlite3 *db, int id);


#endif