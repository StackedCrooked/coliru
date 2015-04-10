#include <functional>
#include <iostream>
using namespace std;

using Callback = void (*)();

void library_function(Callback x)
{
    x();
}

void func()
{
    cout << "func()" << endl;
}

struct Foo
{
    int data = 11;
    void method()
    {
        ++data;
        cout << "method() " << data << endl;
    }
};

int main()
{
    Foo x;
    function<void()> f = bind(&Foo::method, x);
    f(); // OK
    f(); // OK
    
    library_function(func); // OK
    library_function((Callback)&f); // Undefined Behaviour
}
