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
    scanf("%s", contrasena);
    printf("¿CUÁNTOS PROGRAMADORES HAY EN 'DeustoSportKit'?: \n");
    scanf("%i", &respuestaPregunta);

    Administrador admin;

    
    if (respuestaPregunta != PROGRAMADORES) {
        // Si no se sabe la respuesta a la pregunta, no será un administrador
        printf("¡ERROR! Tú no eres un administrador. \n");
        strcpy(admin.nombreAdmin, "nada");
        admin.idAdmin = -1;
        strcpy(admin.contrasena, "nada");
        // administrador falso

    } else if (respuestaPregunta == PROGRAMADORES) {
        // Hay que asegurarse de que el aministrador con el identificativo metida existe.
        int existe;
        existe = existeAdmin(db, idAdmin);
        if (existe == 0) {
            // Si el identificativo no está en la base de datos, el administrador no existe.
            printf("¡USTED NO ES UN ADMINISTRADOR! \n");
            strcpy(admin.nombreAdmin, "nada");
            admin.idAdmin = -1;
            strcpy(admin.contrasena, "nada");
            // administrador falso
        } else {
            // Si lo es, habrá que coger el administrador con dicho identificativo y comparar la informacion de este con la introducida
            admin = obtenerAdmin(db, idAdmin);

            if (strcmp(admin.contrasena, contrasena) != 0) {
                // Si no coincide la contrasena, podra volver a introducirla una vez mas.
                printf("Algo ha ido mal. Vuelva a introducir los datos. \n");
                printf("Recuerde que solo tiene una oportunidad más \n");
                printf("CONTRASEÑA: \n");
                scanf("%s", contrasena);

                if (strcmp(admin.contrasena, contrasena) != 0) {
                    // En caso de fallar la segunda vez, se devolvera null para que no siga adelante
                    printf("¡ERROR!\n");
                    strcpy(admin.nombreAdmin, "nada");
                    admin.idAdmin = -1;
                    strcpy(admin.contrasena, "nada");
                    // administrador falso
                } else {
                    // Si coincide,  se devulve el administrador
                    printf("Bienvenido, %s", admin.nombreAdmin);
                }

            } else {
                // Si coincide, se devuelve el administrador
                printf("Bienvenido, %s", admin.nombreAdmin);
            }
        }
    }

    free(contrasena);
    contrasena = NULL;

    sqlite3_close(db);

    return admin;
}


// Esta funcion sera para que el administrador meta nuevos productos en la base de datos
void crearProductoAdmin (sqlite3 *db, Administrador administrador) {

    // Tendra que elegir el tipo de producto que insertar
    int tipo;
    printf("PRODUCTO NUEVO \n");
    printf("--------------------------------- \n");

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
        strcpy(typeProd, "Prenda");
    } else if (tipo == 2) {
        strcpy(typeProd, "Calzado");
    }

    int idProd = maxIdProducto (db);

    char *nombre;
    float precio;
    int stock, talla;

    char* tipoProd;

    // Preguntara de uno en uno los datos del producto
    if (tipo == 1) {
        printf("CREACIÓN DE PRENDA \n");
        strcpy(tipoProd, "Prenda");
    } else if (tipo == 2) {
        printf("CREACIÓN DE CALZADO \n");
        strcpy(tipoProd, "Calzado");
    }
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

    agregarProducto(db, idProd, tipoProd, nombre);

    // Se agrega el producto a la base de datos

    if (tipo == 1) {
        agregarCalzado(db, idProd, nombre, talla, precio, stock);
        // LOGGERS ---------------------
        //Prenda p = obtenerPrenda(db, idPrenda);
        //entradasNuevasPrenda (p, administrador);
    } else if (tipo == 2) {
        agregarCalzado(db, idProd, nombre, talla, precio, stock);
        // LOGGERS ---------------------
        //Calzado c = obtenerCalzado(db, idCalzado);
        //entradasNuevasCalzado (p, administrador);
    }

    // Se libera la memoria almacenada
    free(nombre);
    nombre = NULL;

} 


void recargarProoductoAdmin (sqlite3 *db, Administrador administrador) {

    int idProd;

    printf("RECARGAR PRODUCTO \n");
    printf("--------------------------------- \n");

    printf("¿Qué producto quiere recargar? \n");
    printf("Por favor, esciba el identificativo del producto.\n");
    printf("IDENTIFICATIVO: \n");
    scanf("%i", &idProd);

    bool existe = existeProducto (db, idProd);

    while (existe == false) {
        printf("El producto indicado no existe. \n");
        printf("Por favor, esciba el identificativo del producto.\n");
        printf("IDENTIFICATIVO: \n");
        scanf("%i", &idProd);
    }

    char tipo = obtenerTipoProducto (db, idProd);
    // C -> calzado		P -> prenda

    int cantidad;

    printf("Cuántas unidades desea recargar?\n");
    printf("CANTIDAD:\n");
    scanf("%i", &cantidad);

    if (tipo == 'C') {
        subirStockCalzado (db, idProd, cantidad);
    } else if (tipo == 'P') {
        subirStockPrenda (db, idProd, cantidad);
    } 
    
}


void eliminarProductoAdmin (sqlite3 *db, Administrador administrador) {

    int idProd;

    printf("ELIMINAR PRODUCTO \n");
    printf("--------------------------------- \n");

    printf("¿Qué producto desea eliminar de DeustoSportKit? \n");
    printf("Por favor, esciba el identificativo del producto.\n");
    printf("IDENTIFICATIVO:\n");
    scanf("%i", &idProd);

    bool existe = existeProducto (db, idProd);

    while (existe == false) {
        printf("El producto indicado no existe.\n");
        printf("Por favor, esciba el identificativo del producto.\n");
        printf("IDENTIFICATIVO: \n");
        scanf("%i", &idProd);
    }

    char tipo = obtenerTipoProducto (db, idProd);
    // C -> calzado		P -> prenda

    int eleccion;

    if (tipo == 'C') {
        Calzado cal =  obtenerCalzado (db, idProd);
        printf("El calzado %s es: \n", cal.nombreCalzado);
    } else if (tipo == 'P') {
        Prenda pren =  obtenerPrenda (db, idProd);
        printf("El material deportivo %s es: ", pren.nombrePrenda); 
    } 


    printf("¿Está seguro de que quiere eliminarlo?\n");
    printf("1. Sí \n");
    printf("2. No \n");
    scanf("%i", &eleccion);

    if (eleccion == 1) {

        if (tipo == 'C') {
            eliminarCalzado(db, idProd);
        } else if (tipo == 'P') {
            eliminarPrenda(db, idProd);
        } 

        eliminarProducto(db, idProd);
        printf("Producto eliminado correctamente. \n");
    }

}


void gestionarProductosAdmin (sqlite3 *db, Administrador administrador) {
    
    int eleccion;

    printf("GESTIONAR PRODUCTOS \n");
    printf("--------------------------------- \n");

    do {

        printf("1. Introducir un producto nuevo \n");
        printf("2. Recargar un producto \n");
        printf("3. Eliminar un producto \n");
        printf("4. Visualizar todos los productos \n");
        printf("5. Volver \n");

        do {
            printf("¿Qué desea hacer, %s?", administrador.nombreAdmin);
            scanf("%i", &eleccion);
        } while (!(eleccion>= 1 && eleccion<=5));

        if (eleccion == 1) {
            crearProductoAdmin (db, administrador);
        } else if (eleccion == 2) {
            recargarProoductoAdmin (db, administrador);
        } else if (eleccion == 3) {
            eliminarProductoAdmin (db, administrador);
        } else if (eleccion == 4) {
            mostrarProductos (db);
        } else if (eleccion == 5) {
            ventanaAdmin(db, administrador);
        }

    } while (eleccion != 0);
    
}

void importarProdFichero (sqlite3 *db, Administrador administrador) {

    printf("IMPORTAR NUEVOS PRODUCTOS \n");
    printf("--------------------------------- \n");

    char* fichero;

    printf("Introduczca nombre del fichero: \n");
    scanf("%s", fichero);

    FILE* file;
    file = fopen(fichero, "r");

    char c;
	int numProds = 0;

    bool primeraLinea = true;          // La primera linea será siempre la misma y no incluirá ningún producto nuevo

    char linea[100];
    int caracteres = 0;

    //leer mientras no se llegue al final del fichero EOF
	while ((c = fgetc(file)) != EOF) {
		if (c != '\n' && primeraLinea == true) {
            // Está leyendo un caracter de la primera linea. Por lo tanto, no nos interesa.
        } else if (c == '\n' && primeraLinea == true) {
            // Ha llegado al final de la primera linea. Empezará a leer productos
            strcpy(linea, "");          // Inicializamos la linea (el producto)
        } else if (c != '\n' && primeraLinea == false) {
            // Seguimos en la misma linea del producto
            strcat(linea, c);
            caracteres++;
        } else if (c == '\n' && primeraLinea == false) {
            // Hemos llegado al final de la linea. Es decir, al final del producto. Es momento de coger la información obtenida, almacenarla y volver a empezar con la linea.
            if (strcmp(linea[0], 'n') == 0 && strcmp(linea[1], 'e') == 0 && strcmp(linea[2], 'w') == 0) {
                // PRODUCTO NUEVO
                
            } else {
                // PRODUCTO EXISTENTE  
                char idString [3];              // Los identificativos son de 3 cifras
                idString[0] = linea[0];
                idString[1] = linea[1];
                idString[2] = linea[2]; 
                int idProd = strtol(linea, NULL, 10);       // Obtenemos el identificativo en modo int

                int n = 0;
                char cant[4];       // Maximo 9999
                for (int i = 0; i < caracteres-4; i++) {              // Los caracteres 'xxx, ' ocupan 5 espacios
                    cant[i] = linea[i+5];
                }
                int cantProd = strtol(cant, NULL, 10);      // Obtenemos la cantidad en modo int

                char tipo = obtenerTipoProducto (db, idProd);           // Obtenemos el tipo para recargar
                if (tipo == 'P') {
                    subirStockPrenda (db, idProd, cantProd);
                } else if (tipo == 'C') {
                    subirStockCalzado (db, idProd, cantProd);
                }
            }
        }
	}

       
	//leer mientras no se llegue al final del fichero EOF
	while ((c = fgetc(file)) != EOF) {
		if (c == '\n' && primeraLinea==true) {
			numProds++;
        } else if (c == '\n' && primeraLinea==false) {
			primeraLinea = true;
        } else if (c != '\n') {

        }
		putchar(c);
	}

	//cerrar fichero
	fclose(file);

	printf("Se han importado %i nuevos productos. \n", numProds);

	return 0;

}


void ventanaAdmin (sqlite3 *db, Administrador administrador) {
    
    int eleccion;

    printf("MENU PRINCIPAL \n");
    printf("--------------------------------- \n");

    do {

        printf("1. Gestionar productos de SportKit \n");
        printf("2. Borrar todos los productos de SportKit \n");
        printf("3. Importar datos desde ficheros \n");
        printf("Pulsa 0 para salir \n");

        do {
            printf("¿Qué desea hacer, %s?", administrador.nombreAdmin);
            scanf("%i", &eleccion);
        } while (!(eleccion>= 0 && eleccion<=3));

        if (eleccion == 0) {
            printf("¡Que pase un buen día!\n");
        } else if (eleccion == 1) {
            gestionarProductosAdmin (db, administrador);
        } else if (eleccion == 2) {
            eliminarProductos (db);
        } else if (eleccion == 3) {
            importarProdFichero (db, administrador);
        }

    } while (eleccion != 0);

    
}





