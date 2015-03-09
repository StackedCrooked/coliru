#include <iostream>
#include <string>
using namespace std;

int main()
{
    int a=21,b=7;
	while(a!=b)//implementing euclidean algorith
	
	{
		if(a>b)
        {
		a=a-b;//subtracting the lesser number
        cout<<a<<endl;
        }
		else
        {
		b=b-a;
        cout<<b<<endl;
        }
	}
	cout<<"GCD Of two numbers is "<<a<<endl;//to print can use a or b
    return 0;
}
