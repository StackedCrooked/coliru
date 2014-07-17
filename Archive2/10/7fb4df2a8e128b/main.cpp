#include<iostream>
using namespace std;

class MyClass 
{
public:
    MyClass(){}

    MyClass (const MyClass &)
    {
        cout << "copy" <<endl;
    }
};

MyClass f()
{
    return MyClass();
}

void g(MyClass i)
{
    i;
}

int main() 
{

    f();
    g(MyClass());
    return 0;
}
