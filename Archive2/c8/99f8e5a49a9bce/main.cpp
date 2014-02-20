#include <cstddef>

struct Other {};

struct MyClass {
    MyClass(int, int);
    MyClass(int, int, Other *);
    int int1, int2;
    Other *pOtherClass;
};

MyClass::MyClass(int a, int b)
:
MyClass(a, b, NULL),
int1(a),
int2(b),
pOtherClass(NULL)
{
}

MyClass::MyClass(int a, int b, Other *p)
:
int1(a),
int2(b),
pOtherClass(p)
{
     if (pOtherClass == NULL)
     {
         pOtherClass = &DefaultInstance;
     }
}