#include <iostream>


class MyClass
{
public:
    static void myFunc();
    static void myFuncII();
    static void myFuncIII();
};

void MyClass::myFunc()
{
    printf("test");
    MyClass::myFuncII();
    myFuncIII();
}

void MyClass::myFuncII()
{
    printf("2");
}

void MyClass::myFuncIII()
{
    printf("3");
}

int main() {
    MyClass::myFunc();
}