#include <iostream>
#include <new>

void foo()
{
    std::cout << "something" << "\n";
}

int main()
{
    std::set_new_handler(foo);
    auto array = new double[2*2*2*2*2*2*2*2*2*2*2];
    std::get_new_handler()(); //Ok, but I want that the function invoke as memory allocation fail handler
}