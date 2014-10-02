#include <iostream>
#include <type_traits>

void f1();
extern "C" void f2();

int main()
{
    // should be false according to the standard [C++11: 7.5/1]
    std::cout << "is_same: " << std::boolalpha << std::is_same<decltype(f1), decltype(f2)>::value << std::endl;
    return 0;
}