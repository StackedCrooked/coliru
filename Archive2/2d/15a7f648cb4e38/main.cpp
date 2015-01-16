#include <type_traits>
#include <iostream>
#include <sstream>

    template <class T, class = decltype(std::declval<std::ostream>() << std::declval<T>() )>
    std::true_type  supports_insertion_operator_test(const T&);
    std::false_type supports_insertion_operator_test(...);

    template <typename T>
    using supports_insertion_operator = decltype(
        supports_insertion_operator_test(std::declval<T>()));

    template <typename T>
    std::string to_string_any(const T& value,
                              typename std::enable_if<
                                  supports_insertion_operator<T>::value>::type* = 0) {
      std::stringstream stream;
      stream << value;
      return stream.str();
    }

    template <typename T>
    std::string to_string_any(const T&
                              ,
                              typename std::enable_if<
                                  !supports_insertion_operator<T>::value>::type* = 0) {
      return std::string("(unknown type [no operator<< implemented] for )");
    }

struct UnknownType {};

int main() {
    std::cout << to_string_any(5) << "\n";
    
    std::cout << to_string_any(UnknownType()) << "\n";
    
    return 0;
}