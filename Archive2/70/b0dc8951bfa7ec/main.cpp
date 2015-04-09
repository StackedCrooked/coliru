#include <type_traits>

template<typename T, typename std::enable_if<std::is_pointer<T>{}>::type* = nullptr>
struct X;

using Z = X<int>;

int main()
{
}