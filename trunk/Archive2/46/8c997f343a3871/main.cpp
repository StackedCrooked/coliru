#include <type_traits>

void f(){}

using type = typename std::result_of<decltype(f)>::type;

int main()
{
    type t;
}
