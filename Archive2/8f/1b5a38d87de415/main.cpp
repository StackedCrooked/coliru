#include <type_traits>

template<typename T, typename = void>
struct has_id : std::false_type { };

template<typename T>
struct has_id<T, decltype(std::declval<T>().id, void())> : std::true_type { };

#include <iostream>

struct X { int id; };
struct Y { int foo; };

int main()
{
    std::cout << std::boolalpha;
    std::cout << has_id<X>::value << std::endl;
    std::cout << has_id<Y>::value << std::endl;
}