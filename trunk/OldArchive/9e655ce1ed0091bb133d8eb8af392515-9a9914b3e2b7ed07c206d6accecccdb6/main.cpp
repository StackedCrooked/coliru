#include <utility>

template <typename U>
auto foo() -> decltype(std::declval<U>() + std::declval<U>());

template <typename T>
decltype(foo<T>()) bar(T)
{
    return T{};
}

int main()
{
    bar(1);
    return 0;
}