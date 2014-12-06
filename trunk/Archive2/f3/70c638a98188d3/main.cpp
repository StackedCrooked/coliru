#include <iostream>
#include <type_traits>
#include <initializer_list>
#include <functional>
#include <string>

enum LogLevel
{
    one, two, three,
};

namespace 
{
    constexpr int log_level = LogLevel::three;
}

///// Should invoke function
template<enum LogLevel L, typename F>
    typename std::enable_if<
        (log_level >= L), 
        typename std::conditional<false, std::result_of<F()>, void>::type
    >::type
    write_log(F const& fn)
    { 
        fn();
    }


template<enum LogLevel L, typename F>
    typename std::enable_if<
        (log_level < L), 
        typename std::conditional<false, std::result_of<F()>, void>::type
    >::type
    write_log(F const& fn)
    { /* intentionally empty for SFINAE */ }


//// Write other stuff
template<enum LogLevel L, typename... Args>
    typename std::enable_if<(log_level >= L), void>::type 
    write_log(Args const & ... args)
    {   
        (void)std::initializer_list<int> { (std::cout << args << ' ', 0)... };
        std::cout << std::endl;
    }


template<enum LogLevel L, typename... Args>
    typename std::enable_if<(log_level < L), void>::type
    write_log(Args const & ... args)
    { /* intentionally empty for SFINAE */ }


int main()
{
    int x = 0xDEAD;
    write_log<one>(123,51235); 
    write_log<one>( [&x] { std::cout << x << std::endl; } ); // BROKEN
}
