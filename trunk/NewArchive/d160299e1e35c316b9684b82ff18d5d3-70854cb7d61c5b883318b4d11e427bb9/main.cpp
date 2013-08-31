#include <functional>
#include <iostream>

class ClassA
{
public:
    void mainFunction()
    {
        std::cout << "ClassA::mainFunction()" << std::endl;
    }

    std::function<void()> getFunction()
    {
        return [&] { return mainFunction(); };
    }
};

class ClassB
{
public:
    int mainFunction(int a, int b)
    {
        return (a + b);
    }

    std::function<int()> getFunction(int a, int b)
    {
        return [&] { return mainFunction(a, b); };
    }
};

int main()
{
    ClassA a;
    auto a_function = a.getFunction();
    a_function();

    ClassB b;
    auto b_function = b.getFunction(5, 6);
    std::cout << b_function();
}
