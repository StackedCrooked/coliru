#include<iostream>
using namespace std;
template<class T>
T min(T a,T b)
{
return (a>b)?a:b;
}
int main()
{
int x,y;
cin>>x>>y;
cout<<"min. of integer value is="<<min(x,y); //error is call of overloaded function    is ambiguous.
float p,q;
cin>>p>>q;
cout<<"min. of floating value is="<<min(p,q);//same error as above
char c1,c2;
cin>>c1>>c2;
cout<<"min. of c1 and c2(basis of ASCII values)="<<min(c1,c2);// same error as    above
getch();
return 0; }