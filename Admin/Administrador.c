#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "Administrador.h"
#include "Productos.h"
#include "BaseDatos.h"
#include "sqlite3.h"

#define PROGRAMADORES 5


Administrador iniciarAdmin (sqlite3 *db) {

    sqlite3_open("bbdd.db", &db);

    int idAdmin;
    char* contrasena;
    contrasena = malloc(sizeof(char)*20);
    int respuestaPregunta;
    // si realmente son administradores, sabrán la respuesta a una pregunta. siempre la misma.

    printf("INCIAR SESIÓN \n");
    printf("--------------------------------- \n");

    // Recoge la informacion del administrador para asegurarse de que es un administrador del sistema
    printf("IDENTIFICATIVO PROPIO: \n");
    scanf("%i", &idAdmin);
	printf("CONTRASEÑA: \n");
    scanf("%s", &contrasena);
    printf("¿CUÁNTOS PROGRAMADORES HAY EN 'DeustoSportKit'?: \n");
    scanf("%i", &respuestaPregunta);

    
    if (respuestaPregunta != PROGRAMADORES) {
        // Si no se sabe la respuesta a la pregunta, no será un administrador
        printf("¡ERROR! Tú no eres un administrador. \n");
        Administrador admin;
        strcpy(admin.nombre, "nada");
        admin.idAdmin = -1;
        strcpy(admin.contrasena, "nada");
        return admin;            // administrador falso

    } else if (respuestaPregunta == PROGRAMADORES) {
        // Hay que asegurarse de que el aministrador con el identificativo metida existe.
        int existe;
        existe = existeAdmin(db, idAdmin);
        if (existe == 0) {
            // Si el identificativo no está en la base de datos, el administrador no existe.
            printf("¡USTED NO ES UN ADMINISTRADOR! \n");
            Administrador admin;
            strcpy(admin.nombre, "nada");
            admin.idAdmin = -1;
            strcpy(admin.contrasena, "nada");
            return admin;            // administrador falso
        } else {
            // Si lo es, habrá que coger el administrador con dicho identificativo y comparar la informacion de este con la introducida
            Administrador admin2 = obtenerAdmin(db, idAdmin);

            if (strcmp(admin2.contrasena, contrasena) != 0) {
                // Si no coincide la contrasena, podra volver a introducirla una vez mas.
                printf("Algo ha ido mal. Vuelva a introducir los datos. \n");
                printf("Recuerde que solo tiene una oportunidad más \n");
                printf("CONTRASEÑA: \n");
                scanf("%s", contrasena);

                if (strcmp(admin2.contrasena, contrasena) != 0) {
                    // En caso de fallar la segunda vez, se devolvera null para que no siga adelante
                    printf("¡ERROR!\n");
                    Administrador admin;
                    strcpy(admin.nombre, "nada");
                    admin.idAdmin = -1;
                    strcpy(admin.contrasena, "nada");
                    return admin;            // administrador falso
                } else {
                    // Si coincide,  se devulve el administrador
                    printf("Bienvenido, %s", admin2.nombre);
                    return admin2;
                }

            } else {
                // Si coincide, se devuelve el administrador
                printf("Bienvenido, %s", admin2.nombre);
                return admin2;
            }
        }
    }

    free(contrasena);
    contrasena = NULL;

    result = sqlite3_close(db);
}


void preguntarPrenda (sqlite3 *db) {

    strcpy(typeProd, "Prenda");

    int idPrenda = maxIdProducto (db);
    agregarProducto(db, idPrenda, tipo);

    char *nombre;
    float precio;
    int stock, talla;

    // Preguntara de uno en uno los datos del producto
    printf("CREACIÓN DE PRENDA \n");
    printf("------------------------- \n");

    printf("NOMBRE: \n");
    nombre = malloc(sizeof(char)*20);
    scanf("%s", nombre);

    printf("TALLA: \n");
    scanf("%i", &talla);

    printf("PRECIO: \n");
    scanf("%f", &precio);

    printf("STOCK: \n");
    scanf("%i", &stock);

    // Se agrega el producto a la base de datos
    agregarPrenda(db, idPrenda, nombre, talla, precio, stock);
    
    // LOGGERS ---------------------
    //Prenda p = obtenerPrenda(db, idPrenda);
    //entradasNuevasPrenda (p, administrador);

    // Se libera la memoria almacenada
    free(nombre);
    nombre = NULL;
}


void preguntarCalzado (sqlite3 *db) {

    strcpy(typeProd, "Calzado");

    int idCalzado = maxIdProducto (db);
    agregarProducto(db, idCalzado, tipo);

    char *nombre;
    float precio;
    int stock, talla;

    // Preguntara de uno en uno los datos del producto
    char *nombre;
    float precio;
    int stock, talla;

    printf("CREACIÓN DE CALZADO \n");
    printf("------------------------- \n");

    printf("NOMBRE: \n");
    nombre = malloc(sizeof(char)*20);
    scanf("%s", nombre);

    printf("TALLA: \n");
    scanf("%i", &talla);

    printf("PRECIO: \n");
    scanf("%f", &precio);

    printf("STOCK: \n");
    scanf("%i", &stock);

    // Se agrega el producto a la base de datos
    agregarCalzado(db, idCalzado, nombre, talla, precio, stock);
    
    // LOGGERS ---------------------
    //Calzado c = obtenerCalzado(db, idCalzado);
    //entradasNuevasCalzado (p, administrador);

    // Se libera la memoria almacenada
    free(nombre);
    nombre = NULL;
}


// Esta funcion sera para que el administrador meta nuevos productos en la base de datos
void crearProductoAdmin (sqlite3 *db, Administrador administrador) {

    // Tendra que elegir el tipo de producto que insertar
    int tipo;
    printf("¿Qué tipo de producto desea meter en la base de datos? \n");
    printf("1. Prenda \n");
    printf("2. Calzado \n");

    // El programa seguira pidiendo el tipo hasta que meta entre 1 y 4
    do {
        printf("TIPO: \n");
        scanf("%i", &tipo);
    } while (!(tipo >= 1 && tipo <= 4));

    char* typeProd;
    typeProd = malloc(sizeof(char)*11);

    if (tipo == 1) {
        
        preguntarPrenda (db);
    
    } else if (tipo == 2) {
        
        void preguntarCalzado (db);
    
    } 

} 


