#include <iostream>
#include <vector>
#include <type_traits>

template <class> 
struct is_template : std::false_type {};

template <template <class...> class T, typename ...Args>
struct is_template<T<Args...>> : std::true_type {};

template<class T>
typename std::enable_if<is_template<T>::value, int>::type getId()  // #1
{
    std::cout << "#1";
    return 42;
}

template<class T>
typename std::enable_if<!is_template<T>::value, int>::type getId()  // #2
{
    std::cout << "#2";
    return 42;
}

int main()
{
    getId<int>();
    getId<std::vector<int>>();
}