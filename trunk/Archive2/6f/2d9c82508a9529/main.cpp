#include <iostream>
#include <cstdlib>
 
class Static {
public:
 
    ~Static() 
    {
        std::cout << "Static dtor\n";
    }
};
 
class Local {
public:
    ~Local() 
    {
        std::cout << "Local dtor\n";
    }
};
 
Static static_variable; // dtor of this object *will* be called
 
void atexit_handler()
{
    std::cout << "atexit handler\n";
}
 
int main()
{
    Local local_variable; // dtor of this object will *not* be called
    const int result = std::atexit(atexit_handler); // handler will be called
 
 std::cout<<"reult:"<<result;
    if (result != 0) {
        std::cerr << "atexit registration failed\n";
        return EXIT_FAILURE;
    }
 
    std::cout << "test\n";
    std::exit(EXIT_FAILURE);
}