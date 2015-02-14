#include <iostream>

struct MyClass
{
    MyClass(int i) : i(i) {}
    int i;
};

struct MyStruct
{
    MyClass myObject1;
    MyClass myObject2;
};

int main()
{
    MyStruct *myStructPtr = new MyStruct
    {
        MyClass(10),
        MyClass(20)
    };
    
    std::cout << myStructPtr->myObject1.i << " " << myStructPtr->myObject2.i << '\n';
}
