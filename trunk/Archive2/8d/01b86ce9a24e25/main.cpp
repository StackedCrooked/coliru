#include <string>
#include <sstream>
#include <iostream>

namespace detail
{
    template<typename T>
    auto stringify(std::stringstream& ss, T const& t, bool)
        -> decltype(ss << t, std::string{})
    {
        ss << t;
        return ss.str();
    }
    
    template<typename T>
    auto stringify(std::stringstream&, T const&, int)
        -> std::string
    {
        return "No overload of operator<<";
    }
}

template <typename T>
std::string stringify(const T& t)
{
    std::stringstream ss;
    return detail::stringify(ss, t, true);
}

struct Foo { };

int main()
{
    std::cout << stringify(11) << std::endl;
    std::cout << stringify(Foo{}) << std::endl;
}
