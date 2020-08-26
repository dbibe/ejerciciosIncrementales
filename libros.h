#ifndef LIBROS
#define LIBROS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/collections/list.h>

struct node {
  char* nombre;
  char* isbn;
  double precio;
  int stock;
};


typedef struct node book;

int getCommand(char* cmd);

void agregar(t_list* libros, char *str, char* _isbn, double _precio, int _stock);

void print(void* element);

void the_destroyer(void* element);


#endif