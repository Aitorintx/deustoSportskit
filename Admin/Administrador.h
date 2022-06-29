#include "sqlite3.h"
#include "Productos.h"

#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_

typedef struct {
    int idAdmin;
    char* nombreAdmin;
    char* contrasena;
} Administrador;


Administrador iniciarAdmin (sqlite3 *db);

void crearProductoAdmin (sqlite3 *db, Administrador administrador);

void recargarProductoAdmin (sqlite3 *db, Administrador administrador);

void eliminarProductoAdmin (sqlite3 *db, Administrador administrador);

void gestionarProductosAdmin (sqlite3 *db, Administrador administrador);

void recargarProdFichero (sqlite3 *db, Administrador administrador);

void importarProdFichero (sqlite3 *db, Administrador administrador);

void ventanaFichero (sqlite3 *db, Administrador administrador);

void ventanaAdmin (sqlite3 *db, Administrador administrador);

#endif
