#ifndef TYPES
#define TYPES

// Estructura clase
typedef struct clase {
    int nombre;
    int alumnos;
    int presencia;
    struct clase *anterior;
    struct clase *siguiente;
} Clase;

// Estructura lista
typedef struct lista{
    Clase *inicio;
    Clase *fin;
} Lista;

#endif

#ifndef FUNC
#define FUNC


#include <stdio.h>
#include <stdlib.h>

Lista * crea_Lista();

void add_element_Lista(Lista *list,Clase *room);

Clase * find_element_Lista(Lista *list,int numero);

void remove_element_Lista(Lista *list,Clase *room);

void remove_Lista(Lista *list);

#endif

#include <stdio.h>

int main (void){
}