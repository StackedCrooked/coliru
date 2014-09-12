#include <functional>
#include <vector>
#include <iostream>

struct ControllerClass
{
    static std::vector<std::function<void()>> function_vector;
};

std::vector<std::function<void()>> ControllerClass::function_vector;

struct Foo
{
    void fooFn()
    {
        std::cout << "Foo" << std::endl;
    }
    
    void registerFnPointer()
    {
        ControllerClass::function_vector.push_back(std::bind(&Foo::fooFn, this));
    }
};

struct Bar
{
    void barFn()
    {
        std::cout << "Bar" << std::endl;
    }
    
    void registerFnPointer()
    {
        ControllerClass::function_vector.push_back(std::bind(&Bar::barFn, this));
    }
};

int main()
{
    Foo foo;
    Bar bar;
    foo.registerFnPointer();
    bar.registerFnPointer();
    
    ControllerClass::function_vector[0]();
    ControllerClass::function_vector[1]();
}
