#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    
int a,b,c;
int AB,BC;

cout<<"katet AB :";    
cin>>a;
cout<<"katet BC:";
cin>>b;

AB=pow(a,2);
BC=pow(b,2);

c=(AB+BC);

cout<<"Hipotenuza = "<<sqrt(c);
   
   system("pause"); 
   return 0;
}
