#include <iostream>

using std::cout;
using std::endl;

void foo(int){ cout << "foo(int)" << endl; }
void foo(int, int){ cout << "foo(int, int)" << endl; }

void (*baz)(int, int);


int main(){ baz = foo; baz(1, 1); }