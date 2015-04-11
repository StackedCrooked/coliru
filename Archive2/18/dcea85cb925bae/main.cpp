#include <boost/any.hpp>
#include <vector>
#include <string>
#include <iostream>

template <const char *str1, const char*... str2> struct restrictedValues                                                                                
{
/*...*/
};

template<class T, class charT>                                                                            
void validate(boost::any&, const std::vector< std::basic_string<charT> >&, T*, long)
{
    std::cout << "default version\n";
}

extern char const client[] = "hello";
extern char const server[] = "world";

template<class charT, const char *... str>
void validate(boost::any &,
        const std::vector<std::basic_string<charT> >&,
        restrictedValues<str...>* /*target_type*/,
        int /*unused*/) {
    std::cout << "custom version\n";
}

int main()
{
    boost::any a;
    std::vector<std::string> xs;
    restrictedValues<client, server>* p = 0;
    validate(a, xs, p, 0);
}