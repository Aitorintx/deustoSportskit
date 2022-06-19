#ifndef BASEDATOS_H_
#define BASEDATOS_H_


#include <stdbool.h>

// ------------------------------------------------- PRODUCTOS -------------------------------------------------------

Producto obtenerProductos (sqlite3 *db, int id);
int maxIdProducto (sqlite3 *db);
int eliminarProducto(sqlite3 *db, int id);
int agregarProducto(sqlite3 *db, int id, char tipo, char* nombre, float precio, int stock, int talla);
char obtenerTipoProducto (sqlite3 *db, int id);
int obtenerIdProducto (sqlite3 *db, char* nombre);
bool existeProducto (sqlite3 *db, int id);
bool existeProducto2 (sqlite3 *db, char* nombre);
int sizeProductos(sqlite3 *db);
int mostrarProductos (sqlite3 *db);
int eliminarProductos (sqlite3 *db);
int subirStock (sqlite3 *db, int id, int cant);


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

int cargarProductos (sqlite3 *db, Producto** productos);
int sizeCompras(sqlite3 *db);
int cargarCompras (sqlite3 *db, Compra** compras);
int sizeCompradores(sqlite3 *db);
int sizeCompradoresVip(sqlite3 *db);
int cargarCompradores (sqlite3 *db, Comprador** compradores, CompradorVip** compradoresVip);
int sizeComprasId (sqlite3 *db, int idCompra);
int cargarComprasId (sqlite3 *db, Compra** compras, int* numCompras, int idCompra);

#endif