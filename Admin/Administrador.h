#include "sqlite3.h"
#include "Productos.h"

typedef struct {
    char* nombre;
    int idAdmin;
    char* contrasena;
} Administrador;


Administrador iniciarAdmin (sqlite3 *db);

void crearProductoAdmin (sqlite3 *db, Administrador administrador);





