#include <iostream>
#include <string>

template <typename Signature>
struct foo_func;

template <typename RET, typename... ARGS>
struct foo_func<RET(ARGS...)>
{
    RET bar(ARGS... args)
    {        
        std::cout << "bar" << std::endl;
    }
};

int main()
{
    foo_func<void(const std::string&, double)> example;
    //foo_func<void,const std::string&, double> compiler_error;
    //foo_func<void> compiler_error2;
    example.bar("hello", 42.0);
    //example.bar("compiler_error", 42.0, 3);
}