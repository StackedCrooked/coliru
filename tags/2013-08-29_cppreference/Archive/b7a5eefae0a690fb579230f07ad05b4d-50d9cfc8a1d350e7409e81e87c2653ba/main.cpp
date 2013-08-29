#include <stdio.h>
#include <sys/wait.h>
#include "rshmem.h"

/* constantes logicas */

#define F 0

#define T 1

/* Numero de procesos en total */

#define N 4

/* Numero de iteraciones para la tarea de cada proceso */

#define NITER 500

/*******************************

* definicion de funciones */

/**********************************************************************

*void incrementa()

*incrementa el valor del contenido del recurso compartido en tantas

*unidades como se indique en la variable k.

**********************************************************************/

void incrementa(int *mem, int k){

int i;

i=*mem;

TP i=i+k;

TP *mem=i;

}

/***********************************************************************

* pHijoQuiere()

* comprueba si algun proceso quiere acceder a su seccion critica:

* recorre "intencion[]" (menos "proc") si alguna componente es "T", en cuyo

* caso devuelve "T", de otro modo "F".

***********************************************************************/

int pHijoQuiere (int intencion[], int proc, int NProc){

int i;

for (i=1; i<NProc; i++)

if (intencion[(proc+i)%NProc]==T ) return T;

return F; /* ninguno tiene intencion de entrar */

}

/***********************************************************************

* elSiguiente()

* busca el proceso que tiene intencion de entrar en su SC, en la lista

* "intencion[]", a partir del proceso "proc". Si no encuentra ninguno

* se toma (proc+NProc-1)%NProc (el anterior mod NProc).

***********************************************************************/

int elSiguiente (int intencion[], int proc, int NProc){

int j;

for (j=1; j<NProc-1; j++)

if (intencion[(proc+j)%NProc] == T) return (proc+j)%NProc ;

return (proc+NProc-1)%NProc ;

}

int main(){

int i; /* variable auxiliar contador*/

int *recurso; /* recurso compartido*/

int idProc ; /* identificador de proceso para uno mismo */

int *entrarSC; /* entrarSC[idProc]=T : idProc quiere entrar en s.c.

entrarSC[idProc]=F : idProc no quiere */

int *turno; /* turno de cada proceso (idProc) */

/*crea zona de memoria compartida*/

if (!crearMemoria()) {

fprintf(stderr, "error de crearMemoria\n");

exit(-1) ;

}

/* asignacion de memoria a los punteros*/

recurso = (int *) memoria; memoria += sizeof(int);

turno = (int *) memoria; memoria += sizeof(int);

entrarSC = (int *) memoria; memoria += sizeof(int)*N;

/* inicializacion de variables en memoria compartida */

*recurso = 0;

/* ningun proceso quiere entrar en su seccion critica todavia */

for (i=0; i<N-1; i++)

entrarSC[i]=F;

*turno=0; /* el turno es del padre */

/* creacion de procesos */

idProc = 0; /* para el proceso primigenio */

while (idProc<N-1) {

if (fork()) { /**** proceso padre */

/* tarea de cada proceso */

for (i=0; i<NITER; i++){

/********seccion entrada********/

if ( pHijoQuiere(entrarSC, idProc, N)== F )

*turno=idProc;

entrarSC[idProc]=T;

while(pHijoQuiere(entrarSC, idProc, N)){

if(*turno != idProc){ /* si no es su turno */

entrarSC[idProc]=F;

while(*turno != idProc); /* mientras no sea su turno */

entrarSC[idProc]=T;

}

}

/********fin seccion entrada*******

*/
incrementa(recurso,-10); /********seccion critica********/
/********seccion salida*******

*/

*turno = elSiguiente(entrarSC, idProc, N);

entrarSC[idProc]=F;

/*

*******fin seccion salida********/

} /* fin for (tarea) */

(void) wait(NULL) ;

printf("Elrecurso valia 0 y ahora vale %d\n", *recurso);

if (idProc == 0) /* el proceso primigenio debe borrar la memoria */

if (!eliminarMemoria())

fprintf(stderr, "error de eliminarMemoria\n");

exit(0);

} else { /**** proceso hijo */

idProc++;

}

}/*idProc=N-1*/

/*Tarea del proceso nieto de todos los procesos*/

for (i=0; i<NITER; i++){

/********seccion entrada*******

*/

entrarSC[idProc]=T;

while(pHijoQuiere(entrarSC, idProc, N)){

if(*turno != idProc){ /* si no es su turno */

entrarSC[idProc]=F;

while(*turno != idProc); /* mientras no sea su turno */

entrarSC[idProc]=T;

}

}

/*

*******fin seccion entrada********/

incrementa(recurso,-10); /********seccion critica********/

/********seccion salida*******

*/

*turno = elSiguiente(entrarSC, idProc, N);

entrarSC[idProc]=F;

/*

*******fin seccion salida********/

} /* fin for (tarea) */

exit(0);

}/*main*/
