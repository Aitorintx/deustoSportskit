#ifndef PRODUCTOS_H_
#define PRODUCTOS_H_

typedef struct 
{
    int id,;
    char* nombre;
    float precio;
    int stock;
    int talla;
}Calzado;

typedef struct 
{
    int id,;
    char* nombre;
    float precio;
    int stock;
    int talla;
}Prenda;

typedef struct {
    int identificativo;
    int idProducto;
    int idComprador;
    int cantidad;
    float precio;
} Compra;

typedef struct {
    char* nombre;
    int identificativo;
    int telefono;
    char* correo;
    char* direccion;
    char* contrasena;
} Comprador;

typedef struct {
    char* nombre;
    int identificativo;
    int telefono;
    char* correo;
    char* direccion;
    char* contrasena;
    char* nivel;
} CompradorVip;





#endif