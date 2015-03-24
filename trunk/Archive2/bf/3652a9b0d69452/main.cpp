#include <string>
#include <memory>
#include <iostream>

struct base {
    virtual ~base() = 0;
    
    virtual std::string message() const = 0;
};

base::~base() = default;

namespace lib {

// No definition provided, to be filled by a library
std::unique_ptr<base> plugin();
    
} // lib

int main()
{
    std::cout << "Calling the plugin once!\n" << lib::plugin()->message() << '\n';
    std::cout << "Calling the plugin twice!\n" << lib::plugin()->message() << '\n';
}