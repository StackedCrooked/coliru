#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <funzioni.h>
#define DESTRA 1
#define SINISTRA 2
#define SU 3
#define GIU 4

int mat[100][2];
int direzione=DESTRA;
int lunghezza=1;
int x_cibo,y_cibo;
bool esci=false;

void generacibo();
void cornice();
void coordinate(int );
void controllo();

int main()
{
    char tasto;
    int i,c;
    cornice();
    generacibo();
    for(i=0;i<100;i++)
    {
        for(c=0;c<2;c++)
        {
            mat[i][c]=0;
        }
    }
    mat[0][0]=30;
    mat[0][1]=10;
    gotoxy(mat[0][0],mat[0][1]); /* posiziona * a centro video */
    putch('*');
    while(esci==false)
    {
        delay(100);
        if(kbhit())
        {
            tasto=getch();
            if(tasto==0) tasto=getch();
            switch(tasto)
            {
                case(72): direzione=SU; break;
                case(80): direzione=GIU; break;
                case(75): direzione=SINISTRA; break;
                case(77): direzione=DESTRA; break;
            }
        }
        for(i=0;i<lunghezza;i++) /*ciclo for per fari si che venga incementata*/
        {                       /*tutta la l0unghezza dello snake e gli passo*/
           coordinate(i);       /* i in modo che muova tutto*/
        }
        gotoxy(mat[0][0],mat[0][1]); /* visualizza snake */
        putch('*');
        controllo();
        if(mat[0][0]>79 || mat[0][0]<1 || mat[0][1]>23 || mat[0][1]<1)
            esci=true;
    }
    return 0;
}

void generacibo() /* genera casulamente il cibo */
{
    randomize();
    x_cibo=1+random(79);
    y_cibo=1+random(23);
    gotoxy(x_cibo,y_cibo);
    putch('@');
}

void cornice() /* crea la cornice intorno all'area di gioco */
{
    int i;
    for(i=0;i<=79;i++)
    {
        gotoxy(i,1);
        printf("*");
        gotoxy(i,24);
        printf("*");
    }
    for(i=0;i<=24;i++)
    {
        gotoxy(0,i);
        printf("*");
        gotoxy(79,i);
        printf("*");
    }
}

void coordinate(int p) /* calcola le coordinate del nuovo punto */
{
    switch(direzione) /*la variabile p serve per passare la lunghezza dello snake*/
    {
        case(DESTRA):
            gotoxy(mat[p][0],mat[p][1]); /*cancella il vecchio asterisco*/
            putch(' ');
            mat[p][0]+=1; /*cambia la direzione*/
            break;
        case(SINISTRA):
            gotoxy(mat[p][0],mat[p][1]);
            putch(' ');
            mat[p][0]-=1;
            break;
        case(SU):
            gotoxy(mat[p][0],mat[p][1]);
            putch(' ');
            mat[p][1]-=1;
            break;
        case(GIU):
            gotoxy(mat[p][0],mat[p][1]);
            putch(' ');
            mat[p][1]+=1;
            break;
    }
}

void controllo() /*controlla se lo snake a mangiato*/
{
    if(mat[0][0]==x_cibo || mat[0][1]== y_cibo)
        lunghezza++;
}