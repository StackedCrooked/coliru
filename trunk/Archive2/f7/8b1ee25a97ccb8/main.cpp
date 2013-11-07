#include <functional>

template<int> struct bar {};
template<typename T> void foo(T, bar<sizeof(T() + T())>* = 0);

int main()
{
    foo(0);
}