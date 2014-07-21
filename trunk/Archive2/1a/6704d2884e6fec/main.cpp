#include <iostream>
#include <limits>
#include <new>

void foo()
{
    std::cout << "something" << "\n";
}

int main()
{
    std::set_new_handler(foo);
    auto array = new double[std::numeric_limits<int>::max()];
    array[123456789] = 2;
    std::cout << "\nEnd";
}