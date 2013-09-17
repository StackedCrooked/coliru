#include <iostream>
using namespace std;
int main()
{
      int a,c,sum=0;
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
                          return 0;
}
                          