#include <tuple>
#include <iostream>

template <class T>
T&
lvalue_cast(T&& t)
{
    return t;
}

int
main()
{
    int i = 1;
    int j = 2;
    auto i_tuple = std::tie(i);
    auto j_tuple = std::tie(j);
    auto const i_copy = i_tuple;
    auto const j_copy = j_tuple;
    std::cout << std::boolalpha
              << (i_tuple == i_copy) << ' '
              << (j_tuple == j_copy) << '\n';
    swap(i_tuple, j_tuple);
    std::cout << std::boolalpha
              << (i_tuple == j_copy) << ' '
              << (j_tuple == i_copy) << '\n';
}
