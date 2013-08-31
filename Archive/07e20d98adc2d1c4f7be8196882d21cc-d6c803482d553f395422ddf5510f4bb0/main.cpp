#include <sstream>
#include <utility>
#include <iostream>
 
int main()
{
//  std::ostream myout(std::cout);              // ERROR: copy ctor is deleted
    std::ostream myout(std::cout.rdbuf());      // OK: shares buffer with cout
//  std::ostream s2(std::move(std::ostringstream() << 7.1));       // ERROR: move constructor
                                                                   // is protected
    std::ostringstream s2(std::move(std::ostringstream() << 7.1)); // OK: move ctor called
                                                                   // through the derived class
    myout << s2.str() << '\n';
}