#include <iostream>
namespace B
{
    int c = 42;
}

namespace A
{
    using namespace B;
    int a = 442;
}

namespace B
{
    int b = 24;
}

int main()
{ 
    std::cout << A::a << std::endl;
    std::cout << A::b << std::endl;
    std::cout << A::c << std::endl;
}