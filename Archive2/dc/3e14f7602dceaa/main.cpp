#include <stdio.h>

int main ()
{

int br,zbr=0, a[200], i,j=0,z=0,step;
FILE*f;
f=fopen("stranice.txt","w+");

printf("Raspon stranica (od 1 do): ");
scanf("%d", &br);

for(i=0;i<br;i++) a[i]=i+1;

printf("\nStranica po listu: ");
scanf("%d", &step);

for(i=0;z<br;i++)
{
for(j=0;j<step;j++)
{
printf("%d, ", a[z]);
fprintf(f,"%d,", a[z]);
z++;
}
z=z+step;
}
printf("\n\n");
fprintf(f,"\n");
z=0;
for(i=0;z<br;i++)
{
for(j=0;j<step;j++)
{
printf("%d,", a[z+step]);
fprintf(f,"%d,", a[z+step]);
z++;
}
z=z+step;
}
fprintf(f,"\n\n\n\n");

fclose(f);
}