#include "hilos.h"


void* generarLibros(void * tiempo){
    printf("Generando libros...");
    sleep(*((int*)tiempo));
}