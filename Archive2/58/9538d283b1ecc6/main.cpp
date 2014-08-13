#include <type_traits>
#include <iterator>

template <class, class Enable = void> struct is_iterator : std::false_type {};
template <typename T> struct is_iterator<T, typename std::enable_if<std::is_pointer<typename std::iterator_traits<T>::pointer>::value>::type> : std::true_type {};

#include <iostream>
#include <vector>

int main()
{
    std::cout << is_iterator<std::ostream_iterator<char>>::value << std::endl;
}
