

//Main.cpp
#include <iostream>

//equivalent to #include "Header.h"
//Header.h
using namespace std;

class BaseClass;
class DerivedClass;

class BaseClass
{
    virtual void myFunction()
    {
        cout << "Base Class";
    }
};

class DerivedClass : public BaseClass
{
    void myFunction()
    {
        cout << "Derived Class";
    }
};

BaseClass *MyClass = new DerivedClass;

using namespace std;

int main()
{
    cout << "Hello";
}
