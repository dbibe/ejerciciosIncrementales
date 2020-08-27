/*
La librería ahora necesita guardar más datos para cada libro:
-Nombre
-ISBN (String de 13 caracteres)
-Precio
-Stock

Actualizar el modelo del ejercicio 1.1 y modificar el comando CargarLibro de tal forma que permita agregar un libro con todas las características antes detalladas.


Añadir el comando “QuitarLibro [Nombre]” que permita borrar de la lista el libro indicado en [Nombre].


Añadir la comando “AumentarStock [Nombre] [Unidades]” y “DisminuirStock [Nombre] [Unidades]”.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/collections/list.h>
#include "libros.h"
#include "commons/config.h"
#include <pthread.h>
#include "hilos.h"

#define CMD_SIZE 12
#define STR_LEN 1024

pthread_mutex_t mutex_libro = PTHREAD_MUTEX_INITIALIZER;
t_list* libros;
t_config *archivito;

void menu(char *action) {

    char cmd[CMD_SIZE];
    char *name;

    // Copio los primero caracteres del string para saber que accion ejecutar
    strncpy(cmd, action, CMD_SIZE);
    cmd[CMD_SIZE] = '\0';

    printf("Probando el comando: %s", cmd);

    switch (getCommand(cmd)) {

        // ListarLibros   
        case 1:
            list_iterate(libros, print);
            break;
        // cargar
        case 2:
            // Copiando el nombre CargarLibro ASDASDASD
            // name = malloc(strlen(action) - CMD_SIZE);
            printf("Nombre: %s", action + CMD_SIZE + 1);
            memcpy(name, action + CMD_SIZE + 1, strlen(action) - CMD_SIZE);
            agregar(libros, name, "AAAA-AAA-AAAA", 5, 7);
        break;

        default:
            printf("\nNo existe el comando: %s\n", action);
        break;
    }
}


int main(int argc, char* argv[]) {

    if (argc > 1) {
        switch (getCommand(argv[1])) {

        // ListarLibros   
        case 1:
            list_iterate(libros, print);
            break;

        // cargar
        case 2:
            agregar(libros, argv[2],argv[3],atof(argv[4]), atoi(argv[5]));
            list_iterate(libros, print);
        break;

        default:
            printf("apaga martin, no pongas espacios salame");
        break;
        }
    }

    libros = list_create();
    archivito = config_create("biblio.config");

    pthread_t hilo1;
    int tiempo;

    char action[STR_LEN];

    tiempo = config_get_int_value(archivito,"imprenta_tiempo_generacion");

    pthread_create(&hilo1,NULL,generarLibros, &tiempo);
    
    printf("\nIngresate un comando perrito..\n");

    fgets (action, STR_LEN, stdin);
    while (strcmp(action, "exit") != 0) {

        menu(action);

        fgets (action, 100, stdin);
    }

    printf("\n---- End Main ----\n");
  
    list_destroy_and_destroy_elements(libros,the_destroyer);
  
    return 0;
  
}