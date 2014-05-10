
#include <iostream>

namespace foo {
    namespace bar {
        const static char* test = "foo";
    }
}

namespace bar = foo::bar;

int main()
{
    std::cout << bar::test << "\n";
}
