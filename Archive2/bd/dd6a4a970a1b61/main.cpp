#include <iostream>

#define IS_DEFINED(x) IS_DEFINED2(x)
#define IS_DEFINED2(x) (#x[0] == 0 || #x[0] == '1')
#define TRACE(x, y) if (IS_DEFINED(x)) { std::cout << y << std::endl; }

int main()
{
    #define FOO
    TRACE(FOO, "test1");
    #undef FOO
    TRACE(FOO, "test2");
    #define FOO 1
    TRACE(FOO, "test3");
}