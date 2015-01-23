#include <iostream>
#include <type_traits>
#include <string.h>
#include <cmath>

    template <typename TLeft, typename TRight = TLeft>
    struct supports_equality_operator {
     private:
      template <typename TL, typename TR>
      static std::true_type equality_operator_test(const TL& left, const TR& right,
                                                   decltype(left == right)* = 0);

      template <typename TL, typename ... T>
      static std::false_type equality_operator_test(const TL& left, const T& ... args);

     public:
      static constexpr bool value =
          decltype(equality_operator_test(std::declval<TLeft>(), std::declval<TRight>()))::value;
    };
    
    struct SomeOption {
        int x;
        std::string foo;
    };

int main() {
    
    std::cout << "supports equality operator: " << supports_equality_operator<SomeOption>::value << std::endl;
    std::cout << "supports equality operator: " << supports_equality_operator<unsigned int>::value << std::endl;
    
    std::cout << "supports equality operator: " << supports_equality_operator<double>::value << std::endl;
    
    return 0;
}