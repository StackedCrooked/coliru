#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
   int n;
   int suma, produs, media;
   cout<<"Introduceti n = ";
   cin>>n;
   for(int i = 1;i<=n;i++)
   {
       suma  = suma+n;
       produs = produs*n;
       media = suma/n;
   }
   cout<<"Suma numarului introdus "<<n<<" ";
      for(int i = 1;i<=n;i++)
      {
        cout<<i<<",";
      }
        cout<<" = "<<suma;
   
   return 0;
  
}
