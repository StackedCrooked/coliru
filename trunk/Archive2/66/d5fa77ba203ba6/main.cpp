#include <iostream>
#include <tuple>

int main()
{
    enum { ID_A, ID_B, ID_C };
    auto t1 = std::make_tuple(10, "Test", 3.14);
    
    std::cout << std::get<ID_B>(t1) << "(" << std::get<ID_A>(t1) << ", " << std::get<ID_C>(t1) << ")" << std::endl;
    return 0;
}