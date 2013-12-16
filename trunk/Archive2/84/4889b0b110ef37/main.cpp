#include <iostream>

using namespace std;

int suma_de_digitos(int numb, int digitos)
{
    int res=0;
   // int res1=0;
    int aux;
    for (int i = 0 ; i <= digitos; i++)
    {
        res= (numb % 10 ) + res;
        if (i==1)
        {
           aux=res;
        }
        numb=(int)numb/10;
    }
    return res;
}
int numero_digitos(int numb)
{
    int count=0;
    while (numb==0)
    {
        numb = (int)numb/10;
        count ++;
    }
}

int factorial(int digito)
{
    int fac=1;
    for (int i=1; i<=digito ; i++)
    {
        fac=fac* i;
    }
    return fac;
}


int main()
{
    int numb;
   cout <<"*************************************************" << endl;
   cout << "Programa para el calculo de diguitos y factorial" << endl; 
   cout <<"*************************************************" << endl;
   cout << "ingrese el numero para el calculo"<<endl;
   cin>>numb;
   cout <<"el nuemro de digitos es:"<<numero_digitos(numb);
   
   return 0;
}
