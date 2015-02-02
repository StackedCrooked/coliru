#include <string>
#include <iostream>
#include <functional>

void fun1(const std::string& name)
{
    std::cout << "fun1, param name = " << name << std::endl;
}

void fun2()
{
    std::cout << "fun2" << std::endl;
}

template <class Function>
void caller(Function function)
{
    function("test");
}

int main()
{
    caller(std::bind(&fun1, std::placeholders::_1));
    caller(std::bind(&fun2));
    
    return 0;
}
