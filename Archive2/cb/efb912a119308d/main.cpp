#include <iostream>

#define MAGICLY_EXPANDING_IFDEFINED_MACRO_I(X) (#X[0] == 0 || #X[0] == '1')
#define MAGICLY_EXPANDING_IFDEFINED_MACRO(X) MAGICLY_EXPANDING_IFDEFINED_MACRO_I(X)

#define FOO

bool foo()
{
    return MAGICLY_EXPANDING_IFDEFINED_MACRO(FOO);
}

bool bar()
{
    return MAGICLY_EXPANDING_IFDEFINED_MACRO(BAR);
}

int main()
{
    std::cout << foo() << std::endl;
    std::cout << bar() << std::endl;
}
