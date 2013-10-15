#include <stdio.h>
#include <stdlib.h>

class Ratio //Classe Ratio
{ public://a questi elementi si può accedere dall'esterno della classe
 void assign(int, int); //funzione membro
 double convert();//funzione membro
 void invert();//funzione membro
 void print();//funzione membro
private: //a questi elementi si può accedere solo all'interno della classe
 int num, den; //dati membro
};

int main()
{
  Ratio x;
  x.assign(22,7);
  printf("x= ");
  x.print();
  printf(" = ");
  printf("%f",x.convert());
  printf("\n");
  x.invert();
  printf("1/x = ");
  x.print();
  printf("\n");
  system ("pause");
}

void Ratio::assign(int numeratore, int denominatore)//def. di assign: associa alle variabili num e den i valori di numeratore e denominatore, non restituisce niente: è void!!
{
    num=numeratore;
    den=denominatore;
}

double Ratio::convert() //def. di convert, restituisce il quoziente num/den
{
    return double (num)/den;
}

void Ratio::invert() //inverte num con den
{
    int temp=num;
    num=den;
    den=temp;
}

void Ratio::print()//stampa num/den
{
    printf("%d", num);
    printf("/");
    printf("%d",den);
}
