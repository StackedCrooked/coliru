#include <iostream>

void foo(const char*)
{   
    std::cout << "Oi!\n";
}

int main()
{
    char* p = nullptr;
    foo(p);
    foo("Goo");
}