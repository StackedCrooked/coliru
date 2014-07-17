#include <iostream>
using namespace std;

class MyClass
{
    public:
        MyClass();
};

MyClass::MyClass()
{
    cout << "Hello world" << endl;
}

int main()
{
    MyClass myClass;
    return 0;
}