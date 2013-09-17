#include<iostream.h>
using namespace std;
int main()
{
      int a,b,c,d,e,sum=0;
      for(a=1;a<=500;a++)
      {
                         c=a;
      while(a>0)
      {
                c=a%10;
                sum=sum+(c*c*c);
      }
      }
                if(sum==c)
               {
                          cout<<"Armstrong Number\n";
               }
                          else
                          cout<<"Not an Armstrong number\n";
                          system("pause");
}