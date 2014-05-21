#include <type_traits>
#include <tuple>

template <typename V, typename T, size_t T_end = std::tuple_size<T>::value>
struct Is_in_tuple
  : std::conditional<std::is_same<V, typename std::tuple_element<T_end-1, T>::type>::value,
                     std::true_type, Is_in_tuple<V, T, T_end - 1>>::type {};

template <typename V, typename T>
struct Is_in_tuple <V, T, 0> : std::false_type {};

#include <iostream>
int main()
{
    typedef std::tuple<int, int, char, int, int> t0;
    typedef std::tuple<int, int, int, int, int> t1;
    
    std::cout << std::boolalpha << Is_in_tuple<char, t0>::value << "\n";
    std::cout << std::boolalpha << Is_in_tuple<char, t1>::value << "\n";
}