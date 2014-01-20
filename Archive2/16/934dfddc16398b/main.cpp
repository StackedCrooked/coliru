#include <iostream>
#include <vector>
#include <type_traits>
#include <iterator>

template<bool B, typename V = void>
using enable_if = typename std::enable_if<B, V>::type;

template<typename ForwardIt>
auto f(ForwardIt first, ForwardIt)
    -> enable_if<std::is_integral<typename std::iterator_traits<ForwardIt>::value_type>{}>
{
    std::cout << "Integral container type" << std::endl;
}

template<typename ForwardIt>
auto f(ForwardIt, ForwardIt)
    -> enable_if<!std::is_integral<typename std::iterator_traits<ForwardIt>::value_type>{}>
{
    std::cout << "Non-integral container type" << std::endl;
}

int main()
{
    struct X { };

    std::vector<int> iv;
    std::vector<X>   xv;

    f(iv.begin(), iv.end()); // "Non-integral container type"
    f(xv.begin(), xv.end()); // "Non-integral container type"
}
