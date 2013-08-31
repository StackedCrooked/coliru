#include <iostream>
#include <sstream>

template <class exception, class charT, class traits>
std::basic_ostream<charT,traits>& throw_cpp(std::basic_ostream<charT,traits>& os)
{
    std::stringstream& self = dynamic_cast<std::stringstream&>(os); //maybe throws std::bad_cast
    throw exception(self.str());
    return os; //redundant, but the compiler might not know that.
}

#include <stdexcept>
#include <fstream>
int main() {
    try {
        int world = 42;
        std::stringstream() << "HELLO " << world << throw_cpp<std::logic_error>;
    } catch(const std::logic_error& e) {
        std::cerr << e.what() << '\n'; 
    }
    try {
        std::fstream() << "HELLO " << throw_cpp<std::logic_error>;
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n'; 
    }
}