#include <type_traits>

int f(const int);
int g(int);

const int a();
int b();

int main()
{
    static_assert( std::is_same<decltype(f), decltype(g)>{}, "");
    static_assert( std::is_same<decltype(a), decltype(b)>{}, "");
}