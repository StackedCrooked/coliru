#include <cstdlib>
#include <iostream>


struct A {
    A(int a, int b) : a(a), b(b) {
    }
    int a;
    int b;
};


void bar(A &a) {
      std::cout << a.a << a.b << std::endl;
}

void foo() {
    A a(1, 2);
    bar(a);
}

int main()
{
	foo();
}
