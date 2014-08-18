#include <iostream>

struct MyClass
{
    MyClass(int x)
    {
        std::cout << "x = " << x << std::endl;
    }
};

int main()
{
    MyClass a = 1;
    MyClass b (2);
    MyClass c {3};
    MyClass (4);
    MyClass (5);
    MyClass d = (MyClass)6;
    MyClass e = MyClass(7);
    MyClass f = MyClass{8};
    MyClass g = static_cast<MyClass>(9);
}
