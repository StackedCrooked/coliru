#include <iostream>
#include <tuple>
#include <string>
#include <typeinfo>
#include <map>


    

// "x-macro" which allows user to apply a macro on this list of RPC Commands.
// The x parameter is the macro which is applied on each element.
// The _ parameter is a macro that evaluates to its arguments and avoid lexer-issues.
#define COMMAND_LIST_IMPL(_, R, A) \
    _( Increment, R(int),                  A(int)      ) \
    _( Sum,       R(int),                  A(int, int) ) \
    _( Split,     R(std::tuple<int, int>), A(int)      )


#define EXPAND(...) __VA_ARGS__
#define COMMAND_LIST(x) COMMAND_LIST_IMPL(x, EXPAND, EXPAND)


template<typename Signature>
struct Command;


template<typename R, typename ...Args>
struct Command<R(Args...)>
{
    typedef std::tuple<Args...> argument_type;
    typedef R result_type;
};


template<typename C>
const std::string& get_command_name();


template<typename C>
void register_command()
{    
    // registration code...
    std::cout << "Register: " << get_command_name<C>() << std::endl;
}


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


template<typename C>
const std::string& get_command_name()
{
    // forward declaration
    std::string demangle(char const * name);
    
    static const std::string cached_result = demangle(typeid(C).name());
    return cached_result;
}