#include <boost/spirit/include/karma.hpp>

namespace karma = boost::spirit::karma;

int main()
{
    karma::symbols<bool, const char*> const_;
    const_.add(true, "const")(false, "");

    for (bool const_qualifier : { true, false })
    {   
        std::cout << karma::format_delimited("void foo()" << const_, ' ', const_qualifier) << "\n";
    }   
}
