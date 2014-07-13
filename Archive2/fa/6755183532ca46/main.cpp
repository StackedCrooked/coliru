#include <iostream>
#include <exception>
#include <stdexcept>

namespace test {

struct my_error : public std::runtime_error {
  my_error(std::string s) : std::runtime_error(s) { }
};

void my_code()
{
    try {
        throw std::runtime_error("throw an exception forcibly");
    }
    catch (...)
    {
        my_error err{"something went wrong in my_code()"};
        std::throw_with_nested(err);
    }
}
    
}

int main()
{
    try {
        test::my_code();
    }
    catch (test::my_error& e) {
        std::cerr << e.what() << std::endl;
        try {
            std::rethrow_if_nested(e);
        } catch (std::exception& e2) {
            std::cerr << e2.what() << std::endl;
        }
    }
    return 0;
}