#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int inf;
    struct nodo *succ;
    struct nodo *prec;
};
typedef struct nodo nodo;

nodo *RicercaPosizione( nodo *a, int i );
nodo *Inserisci(nodo *a, int i, int x);
nodo* AlternateLists(nodo* list1, nodo* list2);
void *MostraLista(nodo *a);

int main(){

    nodo *lista1=NULL;
    nodo *lista2=NULL;
    nodo *lista3=NULL;
    int numeri[]={1,2,3,4};
    int numeri2[]={5,6,7,8};


    int i=0;
    while(i!=4){
        printf("%d",i);
        lista1=Inserisci(lista1,i, numeri[i]);
        i++;
    }


    printf("lista1 \n\n");
    MostraLista(lista1);
    lista2=lista1;
    printf("lista2 \n\n");
    MostraLista(lista2);
    printf("\n\nlista3 \n\n");
    lista3=AlternateLists(lista1,lista2);
    MostraLista(lista3);
}

nodo* AlternateLists(nodo* l1, nodo* l2){
printf("\n\n Inside the fuction");
 // Check if arrays are != NULL
  if(!l1 && !l2) return NULL;
  if(!l1) return l2;
  if(!l2) return l1;
  //----------------------
  nodo* c1 = l1;
  nodo* c2 = l2;
  nodo* next;
  nodo* next2;
  while(c1){
   next = c1->succ;
   if(c2){ // check to make sure there are still nodes in array2
     c1->succ = c2;
     next2 = c2->succ;
     c2->succ = next;
     c2 = next2;
   }else{
    c1->succ = next;
   }
   c1 = next;
 }
 while(c2){ //if there are more nodes in list 2 then there are in list 1
   c1->succ = c2;
   c2 = c2->succ;
   c1 = c2;
 }
 return l1;
 }

//Insert etc
nodo *Inserisci(nodo *a, int i, int x){
    nodo *q, *p;
    if ( i == 0 ){
        q = malloc(sizeof(nodo));
        q->succ = a; q->prec = NULL;
        q->inf = x;
        if (a != NULL)
            a->prec = q;
        a = q;
    } else {
        p = RicercaPosizione( a, i-1);
        if (p != NULL){
            q = malloc(sizeof(nodo));
            q->inf = x;
            q->succ = p->succ;
            q->prec = p;
            if ( p->succ != NULL)
                p->succ->prec = q;
            p->succ = q;
        }
    }
    return a;
}

nodo *RicercaPosizione( nodo *a, int i ){
    nodo *p = a;
    int j = 0;
    while ( j < i && p != NULL){
        p = p->succ;
        j = j+1;
    }
    return p;
}

void *MostraLista(nodo *a){
    nodo *p = a;

    while ( p != NULL ){
        printf("%d, ", p->inf);
        p = p->succ;
    }
    printf("\n");
}