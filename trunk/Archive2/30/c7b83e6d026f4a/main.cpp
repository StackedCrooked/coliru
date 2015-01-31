#include <iostream>
#include<cstdlib>
#include<c.math>
using namespace std;

int main()
{
   int x1,x2,x3,x4,somma p=o,somma d=o;
   cout<<"inserisci i valori x1>>x2>>x3>>x4;"
   if((x1<0)||(x2<0)||(x3<0)||(x4<0))
   { cout<<"uno dei quattro numeri non è positivo:"<<endl;
   }
   else
   {
       if(x1%2==0)
       { somma p=somma p+x1;
       }
       else
       {
           somma d=somma d+x1;
       }
       if(x2%2==0)
       {
           somma p=somma p+x2;
       }
       else
       {
           somma d= somma d+x2
       }
       if(x3%==0)
       {
           somma p=somma p+x3;
       }
       else
       {
           somma d=somma d+x3;
       }
       if(x4%2==0)
       {
           somma p=somma p+x4;
       }
       else
       {
           somma d=somma d+x4;
       }
       cout<<"la somma dei numeri pari è:"<<somma p<<"."<<endl;
       cout<<"la somma dei numeri dispari è"<<somma d<<"."<<endl;
       system("pause");
       return 0;
       
   }
