#include <sstream>
#include <utility>
#include <iostream>
 
int main()
{
    // ERROR: copy ctor is deleted
//  std::ostream myout(std::cout);
 
    // OK: shares buffer with cout
    std::ostream myout(std::cout.rdbuf());
 
    // ERROR: move constructor is protected
//  std::ostream s2(std::move(std::ostringstream() << 7.1));    
 
    // OK: move ctor called through the derived class
    std::ostringstream s2(std::move(std::ostringstream() << 7.1)); 
    myout << s2.str() << '\n';
}
