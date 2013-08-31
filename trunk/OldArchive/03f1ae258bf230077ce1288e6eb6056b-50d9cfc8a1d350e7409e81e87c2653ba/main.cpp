#include <iostream>

namespace x { int a() { return 0; } }
namespace y { int a() { return 1; } }

int main()
{
    using namespace x;
    using namespace y;
    using y::a;
    
    std::cout << a() << std::endl;
}