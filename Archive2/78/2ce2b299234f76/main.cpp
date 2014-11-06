#include <iostream>

using namespace std;
int main()
{
    int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,a1,a2,a3,a4,a5,a6;
    cout << "Enter: " << endl;
    cin>>n;
    c=n%10;
    b=n%100;
    b=b/10;
    a=n%1000;
    a=a/100;
    a1=(100*c)+(10*b)+(a);
    a2=(100*b)+(10*c)+(a);
    a3=(100*a)+(10*c)+(b);
    a4=(100*c)+(10*a)+(b);
    a5=(100*a)+(10*b)+(c);
    a6=(100*b)+(10*a)+(c);
    if ((a1==a2)&(a2==a3)&(a3==a4)&(a4==a5)&(a5==a6))
    {
        cout<<"0";
    }
    else if ((a1<=a2)&(a2<=a3)&(a3<=a4)&(a4<=a5)&(a5<a6))
    {
        o=a6-a5;
        cout<<o;
    }
    else if ((a1<=a2)&(a2<=a3)&(a3<=a4)&(a4<=a6)&(a6<a5))
    {
        p=a5-a5;
        cout<<p;
    }
    else if ((a1<=a2)&(a2<=a3)&(a3<=a5)&(a5<=a6)&(a6<a4))
    {
        q=a4-a5;
        cout<<q;
    }
    else if ((a1<=a2)&(a2<=a4)&(a4<=a5)&(a5<=a6)&(a6<a3))
    {
        y=a3-a5;
        cout<<y;
    }
    else if ((a1<=a3)&(a3<=a4)&(a4<=a5)&(a5<=a6)&(a6<a2))
    {
        j=a2-a5;
        cout<<j;
    }
    else if ((a2<=a3)&(a3<=a4)&(a4<=a5)&(a5<=a6)&(a6<a1))
    {
        r=a1-a5;
        cout<<r;
    }

}
