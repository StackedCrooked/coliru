#include <iostream>

namespace SbcIf {
    int f() { return 1; }
}

namespace SbcController {
    using SbcIf::f;
}

int main(int, char *[])
{
    int x = SbcController::f();
    std::cout << "x=" << x << std::endl;
    return 0;
}