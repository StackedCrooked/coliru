#include <iostream>
#include <string>
using namespace std;

int main()
{
   int a=12,b=1,c=0,before=0,next=0;
   while(a!=0)
   {
       before=next;
       next=a%2;
       c=c+a%2*b;
       b=b*10;
       a=a/2;
       if((next==1)&& (before==1))
       {
           cout<<"may magkatabi"<<endl;
           break;
       }
   }
    cout<<c;


    return 0;
}
