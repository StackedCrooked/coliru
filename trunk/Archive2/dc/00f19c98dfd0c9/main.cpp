#include <iostream>
int main()
{
    auto mystery= true ? ((float)1.0f) : ((int)1);
    std::cout << std::is_floating_point<decltype(mystery)>::value;
}