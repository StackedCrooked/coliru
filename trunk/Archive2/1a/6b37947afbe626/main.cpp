#include <iostream>
using namespace std;


void f(int x)
{
	int k,j;
	j=x;
	for(k=0;k<=3;k++)
	x-=k;
	cout<<x;
}
	void main(void)
{
		int a=10;
		f(a);
		cout<<a;
}
