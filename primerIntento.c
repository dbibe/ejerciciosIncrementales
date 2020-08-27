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

#define CMD_SIZE 11
#define STR_LEN 1024

void menu(char *action, t_list* libros) {

    char cmd[CMD_SIZE];
    char *name;
    int len;

    // Copio los primeros caracteres del string para saber que accion ejecutar
    strncpy(cmd, action, CMD_SIZE);
    cmd[CMD_SIZE] = '\0';

    switch (getCommand(cmd)) {

        // ListarLibros   
        case 1:
            list_iterate(libros, print);
            break;
        // cargar
        case 2:
            // Guarda el tamaño de string leido por consola y le resto el tamaño del comando (CargarLibro)
            len = strlen(action) - CMD_SIZE - 2;
            // Asigno el espacio de memoria
            name = malloc(len);
            // Me muevo "CMD_SIZE + 1" caracteres desde action, para saltear la parte del comando y copio "len" caracteres en "name"
            memcpy(name, action + CMD_SIZE + 1, len);

            name[len] = '\0';

            agregar(libros, name, "AA-AAA-AA", atof("123"), atoi("123"));
        break;

        default:
            printf("\nNo existe el comando: %s\n", action);
        break;
    }
}

int main(int argc, char* argv[]) {

    t_list* libros = list_create();
    t_config *archivito = config_create("biblio.config");

    pthread_t hilo1;
    int tiempo;

    tiempo = config_get_int_value(archivito,"imprenta_tiempo_generacion");

    pthread_create(&hilo1,NULL,generarLibros, &tiempo);

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
            printf("No existe el comando: %s", argv[1]);
        break;
        }
    }

    // Leo un mensaje desde la consola
    char action[STR_LEN];
    fgets (action, STR_LEN, stdin);
    while (strcmp(action, "exit") != 0) {

        // Evaluo el comando
        menu(action, libros);

        // Vuelvo a leer otro comando
        fgets (action, STR_LEN, stdin);
    }
  
    list_destroy_and_destroy_elements(libros,the_destroyer);
  
    return 0;
  
}