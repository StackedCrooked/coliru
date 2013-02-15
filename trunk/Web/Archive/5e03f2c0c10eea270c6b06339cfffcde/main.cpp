#include <type_traits>

int foo()
{
    return 0;
}

int main()
{
    using result_tupe = typename std::result_of<foo>::type;
}