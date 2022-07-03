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
                    printf("Bienvenido, %s \n", admin.nombreAdmin);
                }

            } else {
                // Si coincide, se devuelve el administrador
                printf("Bienvenido, %s \n", admin.nombreAdmin);
            }
        }
    }

    printf("\n");

    free(contrasena);
    contrasena = NULL;

    sqlite3_close(db);

    return admin;
}


// Esta funcion sera para que el administrador meta nuevos productos en la base de datos
void crearProductoAdmin (sqlite3 *db, Administrador administrador) {

    int idProd = maxIdProducto (db) + 1;

    char *nombre;
    nombre = malloc(sizeof(char)*50);
    float precio;
    int stock, talla;
    char* tipoProd;
    tipoProd = malloc(sizeof(char)*10);

    printf("PRODUCTO NUEVO \n");
    printf("--------------------------------- \n");

    printf("¿Qué tipo de producto desea meter en la base de datos? \n");
    printf("1. Prenda \n");
    printf("2. Calzado \n");

    // Tendra que elegir el tipo de producto que insertar
    int tipo = 0;

    // El programa seguira pidiendo el tipo hasta que meta entre 1 y 2
    while (tipo < 1 || tipo > 2) {
        printf("TIPO: \n");
        scanf("%i", &tipo);
    } 

    // Preguntara de uno en uno los datos del producto
    if (tipo == 1) {
        printf("CREACIÓN DE PRENDA \n");
        strcpy(tipoProd, "PRENDA");
    } else if (tipo == 2) {
        printf("CREACIÓN DE CALZADO \n");
        strcpy(tipoProd, "CALZADO");
    }

    printf("------------------------- \n");

    printf("NOMBRE: \n");
    scanf("%s", nombre);

    printf("TALLA: \n");
    scanf("%i", &talla);

    printf("PRECIO: \n");
    scanf("%f", &precio);

    printf("STOCK: \n");
    scanf("%i", &stock);

    int result = agregarProducto(db, idProd, tipoProd, nombre, precio, stock, talla);

    if (result == SQLITE_OK) {
        printf("Producto introducido \n");
    }
    printf("\n");

    // Se libera la memoria almacenada
    free(nombre);
    nombre = NULL;

} 


void recargarProductoAdmin (sqlite3 *db, Administrador administrador) {

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

    subirStock (db, idProd, cantidad);
    
    printf("Producto %i recargado \n", idProd);
    printf("\n");
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

    int eleccion;

    printf("¿Está seguro de que quiere eliminarlo?\n");
    printf("1. Sí \n");
    printf("2. No \n");
    scanf("%i", &eleccion);

    if (eleccion == 1) {

        eliminarProducto(db, idProd);
        printf("Producto eliminado correctamente. \n");
        printf("\n");
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
        printf("5. Visualizar todas las compras \n");
        printf("Pulsa 0 para volver \n");

        do {
            printf("¿Qué desea hacer, %s? ", administrador.nombreAdmin);
            scanf("%i", &eleccion);
        } while (!(eleccion>= 0 && eleccion<=6));

        if (eleccion == 1) {
            printf("\n");
            crearProductoAdmin (db, administrador);
        } else if (eleccion == 2) {
            printf("\n");
            recargarProductoAdmin (db, administrador);
        } else if (eleccion == 3) {
            printf("\n");
            eliminarProductoAdmin (db, administrador);
        } else if (eleccion == 4) {
            printf("\n");
            mostrarProductos (db);
        } else if (eleccion == 5) {
            printf("\n");
            mostrarCompras (db);
        } else if (eleccion == 0) {
            printf("\n");
            ventanaAdmin(db, administrador);
        }

    } while (eleccion != 0);
    
}

void recargarProdFichero (sqlite3 *db, Administrador administrador) {

    printf("RECARGAR PRODUCTOS \n");
    printf("--------------------------------- \n");

    FILE* file;
    file = fopen("RecargarProductos.txt", "rt");

    char c;
	int numProds = 0;


    while ((c = fgetc(file)) != EOF) {
		if (c == '\n'){
			numProds++;
        } 
	}
    numProds++;


    fclose(file);
    file = fopen("RecargarProductos.txt", "rt");
    
    char** productos;
    productos = (char**)malloc(sizeof(char*)*numProds);
    for(int i = 0; i < 10; i++){
        productos[i] = (char*)malloc(sizeof(char)*9);
    }

    int linea = 0;
    int caracter = 0;
       
	while ((c = fgetc(file)) != EOF) {
		if (c == '\n'){
			linea++;  
            caracter = 0;
        } else{
            productos[linea][caracter] = c;
            caracter++;
        }
	}

    //printf("\n");

    int id;
    int cant;
    
    for (int i = 0; i < numProds; i++) {
        //printf("%s\n", productos[i]);
        char* iden = malloc(sizeof(char)*4);
        iden[0] = productos[i][0];
        iden[1] = productos[i][1];
        iden[2] = productos[i][2];
        iden[3] = '\0';
        id = atoi(iden);

        char* cantidad = malloc(sizeof(char)*4);
        cantidad[0] = productos[i][5];
        cantidad[1] = productos[i][6];
        cantidad[2] = productos[i][7];
        cantidad[3] = '\0';
        cant = atoi(cantidad);

        printf("El producto %i hay que recargarlo por %i\n", id, cant);

        subirStock(db, id, cant);
    }
    

	//cerrar fichero
	fclose(file);

	printf("Se han recargado %i productos. \n", numProds);
    printf("\n");

}


void importarProdFichero (sqlite3 *db, Administrador administrador) {

    printf("IMPORTAR NUEVOS PRODUCTOS \n");
    printf("--------------------------------- \n");

    FILE* file;
    file = fopen("NuevosProductos.txt", "rt");

    char c;
	int numProds = 0;


    while ((c = fgetc(file)) != EOF) {
		if (c == '\n'){
			numProds++;
        } 
	}
    numProds++;


    fclose(file);
    file = fopen("NuevosProductos.txt", "rt");
    
    char** productos;
    productos = (char**)malloc(sizeof(char*)*numProds);
    for(int i = 0; i < 10; i++){
        productos[i] = (char*)malloc(sizeof(char)*100);
    }

    int linea = 0;
    int caracter = 0;
       
	while ((c = fgetc(file)) != EOF) {
		if (c == '\n'){
			linea++;  
            caracter = 0;
        } else{
            productos[linea][caracter] = c;
            caracter++;
        }
	}


    
    for (int i = 0; i < numProds; i++) {

        //printf("%s\n", productos[i]);
        int id;
        char* tipo;
        tipo = malloc(sizeof(char)*10);
        char * nombre;
        nombre = malloc(sizeof(char)*50);
        float precio;
        int stock;
        int talla;


        // IDENTIFICATIVO
        id = maxIdProducto(db) + 1;

        
        // TIPO
        int carTipo = 0;
       
	    while (productos[i][carTipo] != ';') {
            tipo[carTipo] = productos[i][carTipo];
            carTipo++;
        }
        tipo[carTipo] = '\0';


        // NOMBRE
        int carNombre = carTipo + 2;        // 2 -> ', '
        int count = 0;

        while (productos[i][carNombre] != ';') {
            nombre[count] = productos[i][carNombre];
            carNombre++;
            count++;
        }
        nombre[count] = '\0';


        // PRECIO
        int carPrecio = carNombre + 2;
        count = 0;

        char* precioStr;
        precioStr = malloc(sizeof(char)*7);

        while (productos[i][carPrecio] != ';') {
            precioStr[count] = productos[i][carPrecio];
            carPrecio++;
            count++;
        }
        precioStr[count] = '\0';
        precio = atoi(precioStr);

        free(precioStr);
        precioStr = NULL;


        // STOCK
        int carStock = carPrecio + 2;
        count = 0;

        char* stockStr;
        stockStr = malloc(sizeof(char)*4);

        while (productos[i][carStock] != ';') {
            stockStr[count] = productos[i][carStock];
            carStock++;
            count++;
        }
        stockStr[count] = '\0';
        stock = atoi(stockStr);

        free(stockStr);
        stockStr = NULL;


        // TALLA
        int carTalla = carStock + 2;
        count = 0;

        char* tallaStr;
        tallaStr = malloc(sizeof(char)*4);

        while (productos[i][carTalla] != ';') {
            tallaStr[count] = productos[i][carTalla];
            carTalla++;
            count++;
        }
        tallaStr[count] = '\0';
        talla = atoi(tallaStr);

        free(tallaStr);
        tallaStr = NULL;


        printf("El producto %i de tipo %s con nombre %s\n", id, tipo, nombre);

        int result = agregarProducto(db, id, tipo, nombre, precio, stock, talla);

        if (result == SQLITE_OK) {
            printf("Producto introducido correctamente \n");
        } else {
            printf("Producto no se ha podido introducir \n");
        }


        free(tipo);
        tipo = NULL;
        free(nombre);
        nombre = NULL;

    }



    //cerrar fichero
	fclose(file);

	printf("Se han importado %i nuevos productos. \n", numProds);
    printf("\n");

}


void ventanaFichero (sqlite3 *db, Administrador administrador) {
    
    int eleccion;

    printf("IMPORTAR DATOS DESDE FICHEROS \n");
    printf("--------------------------------- \n");

    do {

        printf("1. Importar nuevos productos \n");
        printf("2. Recargar productos existentes \n");
        printf("Pulsa 0 para volver \n");

        do {
            printf("¿Qué desea hacer, %s? ", administrador.nombreAdmin);
            scanf("%i", &eleccion);
        } while (eleccion < 0 || eleccion > 2);

        if (eleccion == 0) {
            printf("\n");
            ventanaAdmin(db, administrador);
        } else if (eleccion == 1) {
            printf("\n");
            importarProdFichero (db, administrador);
        } else if (eleccion == 2) {
            printf("\n");
            recargarProdFichero (db, administrador);
        } 

    } while (eleccion != 0);

    
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
            printf("¿Qué desea hacer, %s? ", administrador.nombreAdmin);
            scanf("%i", &eleccion);
        } while (!(eleccion >= 0 && eleccion <= 3));

        if (eleccion == 0) {
            printf("¡Que pase un buen día! \n");
            break;
        } else if (eleccion == 1) {
            printf("\n");
            gestionarProductosAdmin (db, administrador);
        } else if (eleccion == 2) {
            printf("\n");
            eliminarProductos (db);
        } else if (eleccion == 3) {
            printf("\n");
            ventanaFichero (db, administrador);
        } 

    } while (eleccion != 0);
    
}





