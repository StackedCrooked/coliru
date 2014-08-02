#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

class A
{ 
    friend class B;
};

class B : private A 
{ 
    friend int main();
};

int main()
{
    B *b = new B;
    A *a = b;
    cout << b << endl;
    cout << a;
}
