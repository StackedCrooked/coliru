#include <iostream>

void f() 
{
    throw "error";
}

void g()
{
    std::cout << "reachable\n";
    f();
    std::cout << "unreachable\n"; 
}

int main()
{
    try {
        g();
    } catch(...) {
        std::cout << "and we're back\n";    
    }
}
