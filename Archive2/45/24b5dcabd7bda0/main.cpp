#include <iostream>

using std::cout;
using std::endl;

int func(int a, int b) { return a * b; }

void byRef(int& i) { cout << "int& " << i << endl; }
void byRef(const int& i) { cout << "const int& " << i << endl; }
void byRef(int&& i) { cout << "int&& " << i << endl; }
void byRef(const int&& i) { cout << "const int&& " << i << endl; }

int main()
{
    int&& rval = func(10, 20);
    byRef(rval);
    byRef(func(10, 10));
    byRef(17);
}