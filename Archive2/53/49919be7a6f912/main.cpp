#include <cstddef>
#include <iostream>
 
void foo(char*)
{
    std::cout << "foo(int*);\n";
}
 
void foo(long)
{
    std::cout << "foo(long);\n";
}
 
int main()
{
    foo(nullptr);
    foo(NULL);
}