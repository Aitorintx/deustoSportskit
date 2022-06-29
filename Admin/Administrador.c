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

    // Tendra que elegir el tipo de producto que insertar
    int tipo;

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

    // El programa seguira pidiendo el tipo hasta que meta entre 1 y 2
    do {
        printf("TIPO: \n");
        scanf("%i", &tipo);
    } while (!(tipo >= 1 && tipo <= 2));

    printf("Numero elegido: %i\n", tipo);

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

    printf("IMPORTAR PRODUCTOS \n");
    printf("--------------------------------- \n");

    FILE* file;
    file = fopen("RecargarProductos.txt", "rt");

    char c;
	int numProds = 0;

    //bool primeraLinea = true;           // La primera linea será siempre la misma y no incluirá ningún producto nuevo
                                        // Por eso cuando este en la linea 1, no se tendran en cuenta los caracteres leidos a no ser que sea \n

    
    while ((c = fgetc(file)) != EOF) {
		if (c == '\n'){
			numProds++;
        } 
	}
    numProds++;
    
    char** productos;
    productos = (char**)malloc(sizeof(char*)*numProds);
    for(int i = 0; i < 10; i++){
        productos[i] = (char*)malloc(sizeof(char)*9);
    }

    fclose(file);
    file = fopen("NuevosProductos.txt", "rt");


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
    




    /**
    while ((c = fgetc(file)) != EOF) {
        if (c != '.') {

            printf("Prueba normal");
            
            linea[caracteres] = c;
            caracteres++;

        } else {

            printf("Prueba aparte");
            printf("%s", linea);
            
            
            char* iden = malloc(sizeof(char)*4);
            iden[0] = linea[0];
            iden[1] = linea[1];
            iden[2] = linea[2];
            iden[3] = '\0';
            id = atoi(iden);

            int nCant = caracteres - 5;         // 5 -> 'xxx, '
            char* cantidad = malloc(sizeof(char)*5);
            for (int i = 0; i < nCant; i++) {
                cantidad[i] = linea[i+nCant+1];
            }
            cantidad[nCant] = '\0';
            cant = atoi(cantidad);

            subirStock(db, id, cant);
            

            numProds++;

            char* lineaNueva;
            lineaNueva = malloc(sizeof(char)*10);
            linea = lineaNueva;
            caracteres = 0;
        }
    } 
    **/


    /**
    //leer mientras no se llegue al final del fichero EOF
	while ((c = fgetc(file)) != EOF) {
		if (c != '\n' && primeraLinea == true) {
            // Está leyendo un caracter de la primera linea. Por lo tanto, no nos interesa.
        } else if (c == '\n' && primeraLinea == true) {
            // Ha llegado al final de la primera linea. Empezará a leer productos
        } else if (c != '\n' && primeraLinea == false) {
            // Seguimos en la misma linea del producto
            linea[caracteres] = c;              // Meteremos en la posicion caracteres el caracter que estamos leyendo
            caracteres++;
        } else if (c == '\n' && primeraLinea == false) {
            // Hemos llegado al final de la linea. Es decir, al final del producto. Es momento de coger la información obtenida, almacenarla y volver a empezar con la linea.
            if (linea[0] == 'n' && linea[1] == 'e' && linea[2] == 'w') {
                // PRODUCTO NUEVO

                char tipo = linea[5];       // Para obtener el tipo

                // Nombre
                char cadenaNom[strlen(linea)-7];                // 'xxx, _, ' ocupan un total de 8 caracteres
                int i1;
                for (i1 = 0; i1 < strlen(linea); i1++) {
                    if (i1 > 7) {
                        cadenaNom[i1-7] = linea[i1];
                    }
                }
                cadenaNom[i1] = '\0';              // Hemos creado una nueva cadena sin el 'new, _, '. Ahora tenemos el nombre, precio, stock, talla

                int sizeNombre = 0;
                bool coma = false;
                while (coma == false) {
                    if (cadenaNom[sizeNombre] != ',') {
                        sizeNombre++;
                    } else {
                        coma = true;
                    }
                }
                char* nombreProd;
                nombreProd = malloc (sizeof(char) * (sizeNombre+1));
                for (int i = 0; i < sizeNombre; i++) {
                    nombreProd[i] = cadenaNom[i];
                }
                nombreProd[sizeNombre] = '\0';

                //Precio
                char cadenaNueva[strlen(cadenaNom)-sizeNombre-2];          // Le restamos 2 por ', '
                int i2;
                for (i2 = 0; i2 < strlen(cadenaNom); i2++) {
                    if (i2 > sizeNombre-1) {
                        cadenaNueva[i2-(sizeNombre-1)] = cadenaNom[i2];
                    }
                }
                cadenaNueva[i2] = '\0';              // Hemos creado una nueva cadena sin el 'new, _, yyyyyyyy'. Ahora tenemos el precio, stock, talla

                int sizePrecio = 0;
                coma = false;
                while (coma == false) {
                    if (cadenaNueva[sizePrecio] != ',') {
                        sizePrecio++;
                    } else {
                        coma = true;
                    }
                }
                char* precioProd;
                precioProd = malloc (sizeof(char) * (sizePrecio+1));
                for (int i = 0; i < sizePrecio; i++) {
                    precioProd[i] = cadenaNueva[i];
                }
                precioProd[sizePrecio] = '\0';
                float precio = atoi(precioProd);        // Convertimos el array a float
                
                // Stock
                int sizeStock = 0;
                coma = false;
                while (coma == false) {
                    if (cadenaNueva[sizePrecio+2+sizeStock] != ',') {
                        sizeStock++;
                    } else {
                        coma = true;
                    }
                }
                char* stockProd;
                stockProd = malloc (sizeof(char) * sizeStock);
                for (int i = 0; i < sizeStock; i++) {
                    stockProd[i] = cadenaNueva[i+sizePrecio+2];
                }
                stockProd[sizeStock] = '\0';
                float stock = atoi(stockProd);        // Convertimos el array a int

                // Talla
                int sizeTalla = 0;
                coma = false;
                while (coma == false) {
                    if (cadenaNueva[sizePrecio+2+sizeStock+2+sizeTalla] != ',') {
                        sizeTalla++;
                    } else {
                        coma = true;
                    }
                }
                char* tallaProd;
                tallaProd = malloc (sizeof(char) * sizeTalla);
                for (int i = 0; i < sizeTalla; i++) {
                    tallaProd[i] = cadenaNueva[i+sizePrecio+2+sizeTalla];
                }
                tallaProd[sizeTalla] = '\0';
                float talla = atoi(tallaProd);        // Convertimos el array a int


                // CREAMOS PRODUCTOS
                int idProd = maxIdProducto (db);

                agregarProducto(db, idProd, &tipo, nombreProd, precio, stock, talla);

                // Liberamos memoria
                free(nombreProd);
                nombreProd=NULL;
                free(precioProd);
                precioProd=NULL;
                free(stockProd);
                stockProd=NULL;
                free(tallaProd);
                tallaProd=NULL;

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

                subirStock (db, idProd, cantProd);
            }

            // Al acabar de leer un producto, tendremos que volver a hacer que la cadena de caracteres esté en 0
            free (linea);
            linea = NULL;

            char linea[100];
            int caracteres = 0;
            
            numProds++;
        }
	}
    **/

	//cerrar fichero
	fclose(file);

	printf("Se han recargado %i productos. \n", numProds);
    printf("\n");

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
            recargarProdFichero (db, administrador);
        } 

    } while (eleccion != 0);

    
}





