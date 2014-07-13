#include <iostream>
#include <limits>

int main()
{
    constexpr int int_min = std::numeric_limits<int>::min() ;
    constexpr int int_max = std::numeric_limits<int>::max() ;

    std::cout << "int_min: " << int_min // -2147483648 on this implementation
              << "\nint_max: " << int_max << '\n' ; // 2147483647 on this implementation

    int test ;

    std::cin >> test ; // enter value greater than int_max (say, 2147483648 on this implementation)
    // the value entered is too large to be represented by an int
    // the largest representable positive value for an int is stored in test
    // and failbit is set on the input stream
    std::cout << "test: " << test << '\n' ; // int_max (2147483647 on this implementation)
    std::cout << std::boolalpha << "std::cin::fail()? " << std::cin.fail() << '\n' ; // true

    std::cin.clear() ; // clear the failed state of std::cin

    std::cin >> test ; // enter value smaller than int_min (say -2147483699)
    // the negative value entered is outside the range that can be represented by an int
    // the lowest representable negative value for an int is stored in test
    // and failbit is set on the input stream
    std::cout << "test: " << test << '\n' ; // int_min (-2147483648 on this implementation)

    test = int_max ;
    ++test ; // engenders undefined behaviour
}
