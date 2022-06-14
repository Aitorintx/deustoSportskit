#ifndef BASEDATOS_H_
#define BASEDATOS_H_

// ------------------------------------------------- PRODUCTOS -------------------------------------------------------

int maxIdProducto (sqlite3 *db);
void eliminarProducto(sqlite3 *db, int id);
void agregarProducto(sqlite3 *db, char* tipo);


#endif