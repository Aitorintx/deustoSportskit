#ifndef PRODUCTOS_H_
#define PRODUCTOS_H_

typedef struct 
{
    int idProducto;
    char* tipoProducto;
    char* nombreProducto;
    float precioProducto;
    int stockProducto;
    int tallaProducto;
} Producto;


typedef struct {
    int idCompra;
    int idProducto;
    int idComprador;
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
    int idCompradorVIP;
    char* nombreCompradorVIP;
    int telefono;
    char* correo;
    char* direccion;
    char* contrasena;
    char* nivel;
} CompradorVip;





#endif