#include <iostream>
#include <tuple>
#include <typeinfo>
#include <string>
#include <map>






template<typename Signature>
struct Command;

template<typename R, typename ...Args>
struct Command<R(Args...)>
{
    typedef std::tuple<Args...> argument_type;
    typedef R result_type;
};


template<typename C>
const std::string& get_command_name()
{
    // forward declaration
    std::string demangle(char const * name);
    
    static const std::string cached_result = demangle(typeid(C).name());
    return cached_result;
}


template<typename C>
void register_command()
{    
    // registration code...
    std::cout << "Register: " << get_command_name<C>() << std::endl;
}
    

// list of commands
// the x parameter is a user-defined macro to be applied on each element of the list
// the _ argument can be used to group comma separated list of parameter types
#define COMMAND_LIST_IMPL(x, _) \
    x( Increment, int,                      int         ) \
    x( Sum,       int,                      _(int, int) )  \
    x( Split,     std::tuple<_(int, int)>,  int         )


#define EXPAND(...) __VA_ARGS__

// apply x macro on each command
#define COMMAND_LIST(x) COMMAND_LIST_IMPL(x, EXPAND)


// generate Command classes
#define x(Name, Result, Args) struct Name : Command<Result(Args)> {};
inline namespace Commands { COMMAND_LIST(x) }
#undef x


void register_all()
{ 
    // generate registeration code
    #define x(Name, Result, Args)  register_command<Name>();   
    COMMAND_LIST(x)
    #undef x
}


template<typename C, typename ...Args>
typename C::result_type execute_command(Args&& ...args)
{
    std::cout << "Execute: " << get_command_name<C>() << std::endl;
    
    typedef typename C::argument_type Arg;
    typedef typename C::result_type Result;
    
    // Possible serialization code:
    // Arg arg(std::forward<Args>(args)...);
    // std::string result_string = send(get_command_name<C>(), serialize(arg));
    // return deserialize<Result>(result_string);
    
    return Result();
}


int main()
{
    register_all();
    static_assert(std::is_same<Increment::result_type, int>::value, "");
    
    std::cout << "\n";
    
    int result = execute_command<Increment>(1);
    int sum = execute_command<Sum>(1, 2);
}














































#include <memory>
#include <cxxabi.h>

std::string demangle(char const * name)
{
    int st;
    char * const p = abi::__cxa_demangle(name, 0, 0, &st);
    switch (st)
    {
        case 0: { return std::unique_ptr<char, decltype(&std::free)>(p, &std::free).get(); }
        case -1: throw std::runtime_error("A memory allocation failure occurred.");
        case -2: throw std::runtime_error("Not a valid name under the GCC C++ ABI mangling rules.");
        case -3: throw std::runtime_error("One of the arguments is invalid.");
        default: throw std::runtime_error("unexpected demangle status");
    }
}