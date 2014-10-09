#include <iostream>

int a = 1, b = 2, c = 3, d = 4, e = 5, g = 6, h = 7;

void Plus()
{
    a = b + c;
}

void Divide()
{
    c = d / e;
}

void Minus()
{
    e = g - h;
}

template <void (*...functions)()>
void PerformOperations()
{
    int v[]{(functions(), 0)...};
    
    (void)v;
}

#define PRINT_VARIABLE(variable) std::cout << #variable " = " << variable << std::endl

void PrintVariables()
{
    PRINT_VARIABLE(a);
    PRINT_VARIABLE(c);
    PRINT_VARIABLE(e);
}

int main()
{
    PrintVariables();
    PerformOperations<Plus, Minus>();
    PrintVariables();
    PerformOperations<Plus, Divide, Minus>();
    PrintVariables();
}