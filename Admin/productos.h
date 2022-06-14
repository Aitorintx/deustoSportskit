#ifndef PRODUCTOS_H_
#define PRODUCTOS_H_

typedef struct 
{
    int idCalzado;
    char* nombreCalzado;
    float precioCalzado;
    int stockCalzado;
    int tallaCalzado;
} Calzado;

typedef struct 
{
    int idPrenda;
    char* nombrePrenda;
    float precioPrenda;
    int stockPrenda;
    int tallaPrenda;
} Prenda;

typedef struct {
    int idCompra;
    int idProducto;
    int idComprador;
    int cantidad;
    float precioCompra;
} Compra;

typedef struct {
    int idComprador;
    char* nombreComprador;
    int telefono;
    char* correo;
    char* direccion;
    char* contrasena;
    // int esVip
} Comprador;

typedef struct {
    int idCompradprVIP;
    char* nombreCompradorVIP;
    int telefono;
    char* correo;
    char* direccion;
    char* contrasena;
    char* nivel;
} CompradorVip;





#endif