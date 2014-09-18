#include <cstddef>
#include <iostream>
#include <type_traits>

struct Type00 { };
struct Type01 { };
struct Type02 { };
struct Type03 { };
struct TypeXX { };
struct TypeYY { };

template <int N, typename T, typename L, typename... Args>
struct orderid
{
    static constexpr int value = std::is_same<T, L>::value ? N : orderid<N + 1, T, Args...>::value;
};

template <int N, typename T, typename L>
struct orderid<N, T, L>
{
    static constexpr int value = std::is_same<T, L>::value ? N : -1;
};

template <typename T>
struct TypeInfo
{
    using Id = std::integral_constant<int, orderid<0, T, Type00, Type01, Type02, Type03, TypeXX, TypeYY>::value>;
};

int main()
{
     std::cout << TypeInfo<Type00>::Id::value; // Should always print 0
     std::cout << TypeInfo<Type01>::Id::value; // Should always print 1
     std::cout << TypeInfo<Type02>::Id::value; // Should always print 2
     std::cout << TypeInfo<Type03>::Id::value; // Should always print 3
     std::cout << TypeInfo<TypeXX>::Id::value; // Should always print 4
     std::cout << TypeInfo<TypeYY>::Id::value; // Should always print 5
}
