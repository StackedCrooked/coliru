#include <iostream>
#include <string>
using namespace std;

int main()
{
   int a=12,b=1,c=0,before=0,next=0;
   while(a!=0)
   {
       before=next;
       cout<<"before="<<before<<endl;
       next=a%2;
       cout<<"next="<<next<<endl;
       c=c+a%2*b;
       cout<<"c="<<c<<endl;
       b=b*10;
       cout<<"b="<<b<<endl;
       a=a/2;
       cout<<"a="<<a<<endl;
       if((next==1)&& (before==1))
       {
           cout<<"may magkatabi"<<endl;
           break;
       }
   }
    cout<<c;


    return 0;
}
