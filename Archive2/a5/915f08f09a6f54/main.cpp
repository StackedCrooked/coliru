#include <map>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <exception>
#include <stdexcept>

class error : public std::exception
{
    std::string msg;
    public:
    error(const std::string& msg) : msg(msg) {}
    const char* what() const throw() { return msg.c_str(); }
    auto message() const { return msg; }
};

namespace Foo
{
// header
enum class FooEc { one, two, three };
std::string get_error_format(FooEc ec);

// cpp
std::map<FooEc, std::string> foo_ecodes
{
    {FooEc::one, "One"},
    {FooEc::two, "Two %%"},
    {FooEc::three, "Three %% %%"}
};

std::string get_error_format(FooEc ec) { return "FooEc-" + std::to_string(int(ec)) + ": " + foo_ecodes[ec]; }
}

template<class ErrorCode_T>
void throw_error(ErrorCode_T ec)
{
    auto str = get_error_format(ec);
    throw error(str);
}


std::string format_exceptions(int level = 0)
{
    std::ostringstream oss;
    try
    {
        if(level)
            oss << "\nReason (" << level << "): ";
        throw;
    }
    catch(error& e)
    {
        oss << e.message();
        try
        {
            std::rethrow_if_nested(e);
        }
        catch(...)
        {
            oss << format_exceptions(level + 1);
        }
    }
    catch(std::exception& e)
    {
        oss << e.what();

        try
        {
            std::rethrow_if_nested(e);
        }
        catch(...)
        {
            oss << format_exceptions(level + 1);
        }
    }
    catch(...)
    {
        oss << "\nunknown exception";
    }

    return oss.str();
}



int main()
{
    try
    {
        throw_error(Foo::FooEc::one);
    }
    catch(error& e)
    {
        std::cout << format_exceptions() << "\n";
    }
    try
    {
        throw_error(Foo::FooEc::two);
    }
    catch(error& e)
    {
        std::cout << format_exceptions();
    }

return 0;
}
