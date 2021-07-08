#include "libros.h"


int getCommand(char* cmd) {
  if(strcmp(cmd, "ListarLibro") == 0) {
      return 1;
  }
  if(strcmp(cmd, "CargarLibro") == 0) {
      return 2;
  }
  return 0;
}

void agregar(t_list* libros, char *str, char* _isbn, double _precio, int _stock) {
  printf("DATA: %s %s %f %d", str, _isbn, _precio, _stock);
	book *libro;
	libro = malloc(sizeof(struct node));
  
    libro -> nombre = malloc(sizeof(str));
    libro -> isbn = malloc(sizeof(_isbn));
    strcpy(libro -> nombre, str);
    strcpy(libro -> isbn, _isbn);
    libro -> precio = _precio;
    libro -> stock = _stock;
    list_add(libros, libro);  
}

void print(void* element) {
  book *temp = (book *) element;
  printf("\nNombre del libro: %s\n", temp -> nombre);
  printf("\nISBN: %s\n", temp-> isbn);
  printf("\nPrecio: %f\n", temp->precio);
  printf("\nPrecio: %d\n", temp->stock);
}


void the_destroyer(void* element) {
  book *temp = (book *) element;
  free(temp->nombre);
  free(temp->isbn);
  free(temp);
}


