#include "sqlite3.h"
#include "Productos.h"

typedef struct {
    int idAdmin;
    char* nombreAdmin;
    char* contrasena;
} Administrador;


Administrador iniciarAdmin (sqlite3 *db);

void crearProductoAdmin (sqlite3 *db, Administrador administrador);

void recargarProoductoAdmin (sqlite3 *db, Administrador administrador);

void eliminarProductoAdmin (sqlite3 *db, Administrador administrador);

void ventanaAdmin (sqlite3 *db, Administrador administrador);

void importarProdFichero (sqlite3 *db, Administrador administrador);

