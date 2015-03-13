#include<iostream.h>
#include<conio.h>
#include<math.h>


void main(void)
{ int num,numd,i=2;
  cout<<"Enter a positive integer: ";endl;
  cin>>num;


 numd=num;

 while(i==2)
 {
    if(num%2==0)
    {cout<<2<<" ";
    num=num/i;}
    else i=3;
 }


 for (i=3 ; i<=(numd/2); )
      {
         if (num%i==0)
             {
                 cout<<i<<" ";
                 num=num/i;

             }
         else

             {
                i=i+2;
             }
         }
 if (numd=num)
 cout<<num;
 }
 