#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

static std::string safe_getenv(std::string const& macro) {
    auto var = getenv(macro.c_str());
    return var? var : macro;
}

std::string expand_env(std::string const& input) 
{
    using namespace boost::spirit::qi;
    using boost::phoenix::bind;

    static rule<std::string::const_iterator, std::string()> compiled =
          *(~char_("%"))                         [ _val+=_1 ] 
        % as_string ["%" >> +~char_("%") >> "%"] [ _val += bind(safe_getenv, _1) ];

    std::string::const_iterator f(input.begin()), l(input.end());
    std::string result;

    parse(f, l, compiled, result);
    return result;
}

int main()
{
    std::cout << expand_env("Greeting is %HOME% world!\n");
}
