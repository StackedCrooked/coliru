
#include <iostream>
#include <vector>
#include <type_traits>
#include <memory>
#include <iomanip>

template<typename T>
struct is_default_vector;

template<typename T, typename A>
struct is_default_vector<std::vector<T, A>> : std::false_type {};

template<typename T>
struct is_default_vector<std::vector<T, std::allocator<T>>> : std::true_type {};

template<typename T>
struct myalloc : std::allocator<T> {};

int main()
{
    std::cout << std::boolalpha << is_default_vector<std::vector<int>>::value << std::endl;
    std::cout << std::boolalpha << is_default_vector<std::vector<int, myalloc<int>>>::value << std::endl;
}