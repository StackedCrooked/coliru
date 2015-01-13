#include <string>
#include <iostream>
#include <algorithm>

int main()
{
    enum { ID_A, ID_B, ID_C }
    auto t1 = std::make_tuple(10, "Test", 42);
    
    std::cout << std::get<ID_B>(t1) << "(" << std::get<ID_A>(c) << ", " << std::get<ID_C>(c) << ")" << std::endl;
    return 0;
}