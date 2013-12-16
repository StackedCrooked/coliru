#include <iostream>
#include <string>
#include <vector>

class MyClass
{
public:
    MyClass() {
        std::cout << "Running constructor" << std::endl;
    }
    
    MyClass(MyClass& other) {
        std::cout << "Running copy constructor" << std::endl;
    }
    
    void PrintSomething() {
        std::cout << "This worked!" << std::endl;
    }
};

class Inherited : private MyClass
{
public:
    MyClass* GetMyClass() {
        return static_cast<MyClass*>(this);
    }
};

int main() {
    Inherited a;
    MyClass* my_class = a.GetMyClass();
    my_class->PrintSomething();
    return 0;
}