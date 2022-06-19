#ifndef BASEDATOS_H_
#define BASEDATOS_H_


#include <stdbool.h>

// ------------------------------------------------- PRODUCTOS -------------------------------------------------------

int maxIdProducto (sqlite3 *db);
int eliminarProducto(sqlite3 *db, int id);
int agregarProducto(sqlite3 *db, int id, char* tipo, char* nombre);
char obtenerTipoProducto (sqlite3 *db, int id);
int obtenerIdProducto (sqlite3 *db, char* nombre);
bool existeProducto (sqlite3 *db, int id);
bool existeProducto2 (sqlite3 *db, char* nombre);
int sizeProductos(sqlite3 *db);
int mostrarProductos (sqlite3 *db);
int eliminarProductos (sqlite3 *db);

// ------------------------ PRENDA ---------------------------

Prenda obtenerPrenda (sqlite3 *db, int id);
int agregarPrenda (sqlite3 *db, int id, char* nom, float precio, int stock, float talla);
int subirStockPrenda (sqlite3 *db, int id, int cant);
int eliminarPrenda (sqlite3 *db, int id);
int eliminarTodasLasPrenda(sqlite3 *db);
bool existePrenda (sqlite3 *db, int idPrenda);


// ------------------------ CALZADO --------------------------

Calzado obtenerCalzado (sqlite3 *db, int id);
int agregarCalzado(sqlite3 *db, int id, char* nom, float precio, int stock, float talla);
int subirStockCalzado (sqlite3 *db, int id, int cant);
int eliminarCalzado(sqlite3 *db, int id);
int eliminarTodasLosCalzados(sqlite3 *db);
bool existeCalzados(sqlite3 *db, int idCalzado);


// ------------------------------------------------- USUARIOS -------------------------------------------------------

// ------------------------ COMPRADOR --------------------------

int maxIdComprador (sqlite3 *db);
bool obtenerTipoComprador (sqlite3 *db, int id);
Comprador obtenerComprador (sqlite3 *db, int id);
CompradorVip obtenerCompradorVIP (sqlite3 *db, int id);
int sizeComprador (sqlite3 *db);
int mostrarCompradores (sqlite3 *db);
int eliminarComprador (sqlite3 *db, int id);
int agregarComprador (sqlite3 *db, int id, char* nombre, int telefono, char* correo, char* direccion, char* contrasena);
int agregarCompradorVIP (sqlite3 *db, int id, char* nombre, int telefono, char* correo, char* direccion, char* contrasena, char* nivel);
bool existeComprador (sqlite3 *db, int id);

// ------------------------ ADMINISTRADOR --------------------------

Administrador obtenerAdmin(sqlite3 *db, int id);
bool existeAdmin(sqlite3 *db, int id);

// ------------------------------------------------- COMPRAS -------------------------------------------------------

int maxIdCompra (sqlite3 *db);
int agregarCompra (sqlite3 *db, int idCompra, int idProducto, int idComprador, float precioCompra);
int sizeCompras(sqlite3 *db);
int mostrarCompras (sqlite3 *db);


// ------------------------------------------------- SERVER -------------------------------------------------------

int sizePrendas(sqlite3 *db);
int sizeCalzados(sqlite3 *db);
int cargarProductos (sqlite3 *db, Prenda** prendas, Calzado** calzados, int* numPrendas, int* numCalzado, int* numProductos);


#endif