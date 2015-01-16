#include <type_traits>
#include <iostream>
#include <sstream>

    template <class T, class = decltype(std::declval<std::ostream>() << std::declval<T>() )>
    std::true_type  supports_insertion_operator_test(const T&);
    std::false_type supports_insertion_operator_test(...);

    template <typename T>
    using supports_insertion_operator = decltype(
        supports_insertion_operator_test(std::declval<T>()));

struct UnknownType {};

int main() {
    
    std::cout << supports_insertion_operator_test<int> << "\n";
    
    return 0;
}