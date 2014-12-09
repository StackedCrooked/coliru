#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

template<typename First>
void ToSStream(std::stringstream& ss, First&& v)
{
    ss << std::forward<First>(v);
}

template<typename First, typename ...Rest>
void ToSStream(std::stringstream& ss, First&& v, Rest&& ...rest)
{
    ss << std::forward<First>(v);
    ToSStream(ss, std::forward<Rest>(rest)...);
}

template<typename ...Args>
std::string ToString(Args&& ...args)
{
    std::stringstream ss;
    ToSStream(ss, std::forward<Args>(args)...);
    return ss.str();
}

int main()
{
    std::cout << ToString("I can << things ", 123.45, " and use iomanip ", std::hex, 49152) << std::endl;
}
