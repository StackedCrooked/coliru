#include<iostream>
#include<math.h>
using namespace std;
int main()
{

cout<<"************************************************************\n";   
cout<<"    This is a program to reverse the digits entered\n";
cout<<"************************************************************\n"; 
int a,b,c,d,i,e,f,h,j,k=h,sum=0,m[k-1],n[h-1],l,o(0); cout<<"\n";
        cout<<"Give the number of digits in the given number\n";
        cin>>h;
        cout<<"Give a "<<h<<" digit number \n";
        cin>>a; cout<<"\n"; b=pow(10,h-1); j=pow(10,h);
        if(a>=b && a<j)
    {
    i=h; e=h-1;
    while(i>=1)
        {   for(k=0;k<=(h-1);k++)
                {
                c=pow(10,i); d=pow(10,e); f=(a%c)/d; m[k]=f; 
                cout<<"The present value of f is \n"<<m[k]<<"\n";
                e=e--; i=i--; l=h-1; 
                n[l]=m[k]*pow(10,k); o=o+n[l]; l--;
            }
                cout<<o<<" is the new number\n";
                
        }
    }
    else
        {
                cout<<"Yeah ha ha ha ha...Now stop kidding";
    }
    /*Tricky is complete in all respects:
        1.it can run for any n-digit number & not just 5-digits.
        2.it can takes n from the user.
        3.it can check if the user has given a n-digit number or not.
        4.it can do all the above stuff with fixed no. of variables.*/
}