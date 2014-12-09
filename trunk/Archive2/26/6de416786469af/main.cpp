#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdexcept>

template<typename First>
void ToSStream(std::stringstream& ss, First&& v)
{
    ss << std::forward<First>(v);
}

template<typename First, typename ...Rest>
void ToSStream(std::stringstream& ss, First&& v, Rest&& ...rest)
{
    ToSStream(ss, v);
    ToSStream(ss, std::forward<Rest>(rest)...);
}

template<typename ...Args>
std::string ToString(Args&& ...args)
{
    std::stringstream ss;
    ToSStream(ss, std::forward<Args>(args)...);
    return ss.str();
}

class variadic_error : public std::runtime_error
{
public:
    template<typename ...Args>
    explicit variadic_error(Args&& ...args)
        : std::runtime_error(ToString(std::forward<Args>(args)...))
    {
    }
};

int main(int argc, char **argv)
{
    // Bad example
    std::cout << ToString("I can output things easily ", 123.45, " and use iomanip ", std::hex, 49152) << std::endl;
    
    // Better example
    try
    {
        throw variadic_error("I can give a detailed error, argc=", argc, " argv=", argv);
    } catch (std::runtime_error e) {
        std::cout << "Caught: " << e.what() << std::endl;
    } catch (std::exception e) {
        std::cout << "Caught: " << e.what() << std::endl;
    }
    
    throw variadic_error("I can give a usable uncaught detailed error, argc=", argc, " argv=", argv);
    
    return 0;
}
