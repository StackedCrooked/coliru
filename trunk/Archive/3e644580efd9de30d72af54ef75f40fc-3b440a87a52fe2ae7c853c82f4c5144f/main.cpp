#include <memory>
#include <string> 

namespace X {
    class S;   
}

std::string r(X::S &s);

namespace X
{
    class S
    {
        friend std::string (::r)(S &s);
        std::unique_ptr<std::istream> s_;
    };
}

std::string r(X::S &s)
{
    auto& x = s.s_;
    return "";
}