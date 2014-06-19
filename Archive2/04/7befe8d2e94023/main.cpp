#include <stdio.h>
#include <stdlib.h> /* pour exit et malloc */
#include <string.h> /* pour strlen */
#include <math.h>
#define eox 39*1.e-1
#define eo 8.85*1.e-12



int main(void)
{

float w,w1, l,l1, r, umax, vds, lgi, gm, gm1, tox, tox1,u;
char f;

w=1;
w1=1;
lgi=1;
l=1;
l1=1;
r=1;
vds=1;
umax=1;
gm=1;
gm1=1;
tox=1;
tox1=1;
u=1;



puts("Ce programme calcul la mobilité en fonction de la transconductance Gm ");
puts("Veuillez taper la largeur du transistor en um W : ");
scanf("%f",&w1);
w=w1*1.e-6;
puts("Veuillez taper la longueur du transistor en um L: ");
scanf("%f",&l1);
l=l1*1.e-6;
r=w/l;
puts("Veuillez entrer la tension Vds en Volt : ");
scanf("%f",&vds);
printf("le rapport W/L =  %f\n",r);
lgi = (100*1.e-9*(w/l));
printf("lgi =  %14.10lg\n",lgi);
puts("Veuillez entrer l'épaisseur d'oxyde en nm e: ");
scanf("%f",&tox1);
tox=tox1*1.e-9;
puts("Veuillez entrer la transconductance Gm en nA/V : ");
scanf("%f",&gm1);
gm=gm1*1.e-9;

{
u = (gm*1e+4*l*tox)/(eox*eo*w*vds);
}

  printf("Mobilité =  %14.10lg\n",u);
   puts("Veuillez taper f pour fin : ");
scanf("%f",&f);

  return 1 ;


  }

