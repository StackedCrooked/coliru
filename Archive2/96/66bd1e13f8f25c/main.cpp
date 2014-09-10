#include <iostream>
#include <exception>
#include <stdexcept>

class LevelLoadException : public std::runtime_error
{
public:
    using std::runtime_error::runtime_error;
};

int main()
{
    try {
        throw LevelLoadException("Oops");
    } catch( std::exception const& e ) {
        std::cout << e.what() << '\n';
    }
}
