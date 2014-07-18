#include <iostream>
#include <cstddef>

using std::cout;

struct A
{
    int d;

    //A(){ a = 4; }
};

struct B : A
{
	bool c;
    B(){ c = 5; }
};

A *a = new A;
B *b = new B;

int main()
{ 
    cout << alignof(void*) << "\n" ; 
    cout << alignof(long double*) << "\n"; 
    cout << alignof(B*) << "\n";
    cout << alignof(int*) << "\n" ; 
    cout << alignof(double*) << "\n"; 
    cout << alignof(A**) << "\n";
}