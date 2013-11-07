#include <iostream>

using namespace std;

void foo(int* ptr)
{
    cout << "foo(int*): Writing '666' to memory location " << ptr << "\n";
    *ptr = 666;
}

int main()
{
    int kek = 24;
    cout << "main(): kek is " << kek << ". Memory location of kek is " << &kek << '\n';
    foo(&kek);
    cout << "main(): kek is now " << kek << '\n';
}