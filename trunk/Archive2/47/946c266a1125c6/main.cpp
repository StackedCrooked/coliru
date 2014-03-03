#include <iostream>

struct Example
{
    Example(int) {}
    Example(Example const &) { std::cout << "copy\n"; }
};

Example FunctionUsingIf(int i)
{
    if (i == 1)
        return Example(1);
    else
        return Example(2);
}

Example FunctionUsingTernaryOperator(int i)
{
    return (i == 1) ? Example(1) : Example(2);
}

int main()
{
    std::cout << "using if:\n";
    Example obj1 = FunctionUsingIf(0);
    std::cout << "using ternary operator:\n";
    Example obj2 = FunctionUsingTernaryOperator(0);
}