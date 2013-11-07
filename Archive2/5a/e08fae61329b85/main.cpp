#include<iostream>
//#include<conio.h>
using namespace std;

class A
{
    public:
        int a,b;
    public:
        A():a(0),b(0){   }
        A(int a, int b) : a(a), b(b) {    }

};

int main()
{
	A *x;
	x = new A[3]{ {10, 5}, {1, 2}, {4, 5} };
	for (int i = 0; i < 3; ++i)
	{
		std::cout << x[i].a << x[i].b << '\n';
	}
	delete []x;
	//getch();
	return 0;
}