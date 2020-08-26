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
            printf("apaga martin, no pongas espacios salame");
        break;
        }
    }
  
    list_destroy_and_destroy_elements(libros,the_destroyer);
  
  return 0;
  
}