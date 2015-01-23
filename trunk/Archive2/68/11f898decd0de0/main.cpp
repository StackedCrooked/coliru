#include <vector>
#include <typeinfo>
#include <iostream>

template<typename T, std::size_t N>
struct md_vector
{
    using type = std::vector<typename md_vector<T, N - 1>::type>;
};

template<typename T>
struct md_vector<T, 1>
{
    using type = std::vector<T>;
};

template<typename T, std::size_t N>
using md_vector_t = typename md_vector<T, N>::type;

int main()
{
    md_vector_t<int, 2> foo;
    //check if type is what we want:
    std::cout << (typeid(foo) == typeid(std::vector<std::vector<int>>));
}