#include <stdexcept>
#include <iostream>
 
int main()
{
    std::string s("message"); // for capacity
 
    std::cout << s << std::endl;
    std::cout << "string size = " << s.size() << '\n';
    std::cout << "string capacity = " << s.capacity() << '\n';
 
    s = "abc";
    s.at(2) = 'x'; // ok
    std::cout << s << '\n';
 
    std::cout << "string size = " << s.size() << '\n';
    std::cout << "string capacity = " << s.capacity() << '\n';
 
    try {
        // throw, even if capacity allowed to access element
        s.at(3) = 'x';
    }
    catch (std::out_of_range& exc) {
        std::cout << exc.what() << '\n';
    }
}