#include <boost/variant.hpp>
#include <functional>
#include <string>
#include <iostream>

typedef uint32_t IntType;
typedef IntType IntValue;
typedef boost::variant<IntValue, std::string>  MsgValue;

class d_string_int_visitor : public boost::static_visitor<IntType>
{
public:
    inline IntType operator()(IntType i, const std::string& s) const
    {
        std::cout << __PRETTY_FUNCTION__ << ' ' << s << '\n';
        return i;
    }

    //I want this, but compiler error.
    inline IntValue operator()(const std::string& str, const std::string& s) const noexcept
    {
        // code in here
        std::cout << __PRETTY_FUNCTION__ << ' ' << s << '\n';
        return 0;
    }
};

int main()
{
    MsgValue v;
    auto bound_visitor = std::bind(d_string_int_visitor(), std::placeholders::_1, "Hello World!");
    boost::apply_visitor(bound_visitor, v);
    
    v = "str";
    boost::apply_visitor(bound_visitor, v);
}
