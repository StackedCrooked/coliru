#include <iostream>

auto list = [](auto... v)
{
    return [=](auto access) { return access(v...); };
};

auto map = [](auto func)
{
    return [=](auto ...z) { return list(func(z)...); };
};

auto print = [](auto v)
{
    std::cout << v; // side effect
    return v;
};

int main()
{
    std::cout << "gcc prints ";
    list(1,2,3,4)(map(print));        
            
    std::cout << "\nclang prints 1234\n";
    std::cout << "\nthe reason for discrepancy is the same old thing, coming from C:";
    std::cout << "\nthe order of evaluation of the arguments in function list(func(z)...) is unspecified";
}

