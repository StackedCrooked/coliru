#include <iostream>
using namespace std;

int main(){
{   
int pnum1;
int pnum2;
int op;
cout<<("TDCC v2")<<endl;
start: // menu
cout<<("Settings:")<<endl;
cout<<("1=Addition 2=Subtraction 3=Multiplication 4=Division 0=Close Program")<<endl;
cout<<("Problem: ");
cin >>pnum1;  if(pnum1==0) return 0;
cin >>op;
cin >>pnum2;

if(op==1)
cout << "Is: " << pnum1+pnum2 << endl;
goto start;
if(op==2);
cout << "Is: " << pnum1-pnum2 << endl;
goto start;
if(op==3);
cout << "Is: " << pnum1*pnum2 << endl;
goto start;
if(op==4);
cout << "Is: " << pnum1/pnum2 << endl;
goto start;
}
}