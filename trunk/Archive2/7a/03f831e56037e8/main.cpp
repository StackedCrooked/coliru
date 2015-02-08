#include <iostream>
#include <iomanip>
#include <string>

int main()
{
    std::string str ;

    std::cin >> str ; // enter 123456789
    std::cout << str << '\n' ; // 123456789

    std::cin >> std::setw(3) >> str ; // enter 123456789
    // reads "123", "456789\n" remains in the input buffer
    std::cout << str << '\n' ; // 123

    char cstr[32] ;
    std::cin >> std::setw(3) >> cstr ; // we don't need to enter anything; "456789\n" is in the input buffer
    // reads "45" from the input buffer, and appends a null character as the third character
    // "6789\n" remains in the input buffer
    std::cout << cstr << '\n' ; // 56

    std::cin >> std::setw(8) >> str ; // we don't need to enter anything; "6789\n" is in the input buffer
    // reads four characters "6789", formatted input stops when a white space is encountered
    // a new line character remains in the input buffer
    std::cout << str << '\n' ; // 6789

    int n ;
    std::cin >> std::setw(4) >> n ; // enter 123456789
    // setw (width) is ignored for numeric input
    std::cout << n << '\n' ; 
}
