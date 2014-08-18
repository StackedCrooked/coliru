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
    MyClass {5};
    (MyClass)6;
    static_cast<MyClass>(7);
}
