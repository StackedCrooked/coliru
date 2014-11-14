#include <type_traits>

class A{};

template<typename T>
auto operator+(T& lhs,int rhs)
    -> typename std::enable_if<std::is_base_of<A, T>::value, A>::type
{
    A to_return;
    return to_return;
}

class B{};

template<typename T>
auto operator+(T& lhs,int rhs)
    -> typename std::enable_if<std::is_base_of<B, T>::value, B>::type
{
    B to_return;
    return to_return;
}

int main()
{
  A u;
  A v = u+1;
}