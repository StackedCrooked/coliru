#include <iostream>
#include <fstream>
#include <initializer_list>

constexpr int log_level = 99; // all

enum LogLevel
{
    INFO   = 1,
    ERROR  = 2,
};

//////// Specialized ostream arg
template<enum LogLevel L, typename... Args>
    typename std::enable_if<(log_level >= L), void>::type 
    write_log(std::ostream & stream, Args const & ... args)
    {
        std::initializer_list<int> l { (stream << args << ' ', 0)... };
        stream << std::endl;
        (void)l;
    }

/* SFINAE */
template<enum LogLevel L, typename ...Args>
    typename std::enable_if<(log_level < L), void>::type
    write_log(std::ostream & stream, Args const & ... args)
    { }


////////// Non-specialized
template<enum LogLevel L, typename... Args>
    typename std::enable_if<(log_level >= L), void>::type 
    write_log(Args const & ... args)
    {   
        std::initializer_list<int> l { (std::cout << args << ' ', 0)... };
        std::cout << std::endl;
        (void)l;
    }

/* SFINAE */
template<enum LogLevel L, typename... Args>
    typename std::enable_if<(log_level < L), void>::type
    write_log(Args const & ... args)
    { }
        
        
int main(void) 
{ 
    std::cout << "Here ----\n";
    write_log<INFO>(1.254);
    write_log<ERROR>(3.14);
    
    std::ofstream f{"test1"};
    write_log<INFO>(f, 1256.7);
}



