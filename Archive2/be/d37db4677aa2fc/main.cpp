#include <iostream>
#include <string>

void init()
{
    std::cout << "hello" << std::endl;
}
void f()
{
    static const bool registered = ( init(), true );
}
int main()
{
    f();
    f();
    f();
    f();

}