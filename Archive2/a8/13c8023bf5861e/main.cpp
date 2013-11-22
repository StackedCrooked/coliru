#include <iostream>
int main()
{
    std::cout << "Test\n"; // There is no operator<< in global namespace, but ADL
                           // examines std namespace because the left argument is in
                           // std and finds std::operator<<(std::ostream&, const char*)
    operator<<(std::cout, "Test\n"); // same, using function call notation
 
    // however,
//    std::cout << endl; // Error: 'endl' is not declared in this namespace.
                       // This is not a function call to endl(), so ADL does not apply
 
    endl(std::cout); // OK: this is a function call: ADL examines std namespace
                     // because the argument of std::endl is in std, and finds std::endl
 
//    (endl)(std::cout); // Error: 'endl' is not declared in this namespace.
                       // The sub-expression (endl) is not a function call expression
}