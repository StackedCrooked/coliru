#include <functional>
#include <iostream>
#include <tuple>
#include <typeinfo>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;

template<typename Signature>
struct Command;

template<typename Result, typename ...Args>
struct Command<Result(Args...)>
{    
    typedef Result result_type;
    typedef std::tuple<Args...> argument_type;
};


struct Sum : Command<int(int, int)>
{    
};


int main()
{
    Sum s;
    std::cout << typeid(Sum::argument_type).name() << std::endl;
    std::cout << typeid(Sum::result_type).name() << std::endl;
}