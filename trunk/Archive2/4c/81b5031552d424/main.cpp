// BOOST HEADER
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <iostream>

struct what_is_the_attr
{
    template <typename> struct result { typedef bool type; };

    template <typename T>
    static void print_the_type()
    {
        std::cout << "    ";
        std::cout << typeid(T).name();
        if(std::is_const<typename std::remove_reference<T>::type>::value)
            std::cout << " const";
        if(std::is_rvalue_reference<T>::value)
            std::cout << " &&";
        else if(std::is_lvalue_reference<T>::value)
            std::cout << " &";
    }

    template <typename Th, typename Th2, typename... Tt>
    static void print_the_type()
    {
        print_the_type<Th>();
        std::cout << ",\n";
        print_the_type<Th2, Tt...>();
    }

    template <typename... Ts>
    void operator()(Ts&&...) const
    {
        std::cout << "what_is_the_attr(\n";
        print_the_type<Ts...>();
        std::cout << ")" << std::endl;
    }
};

namespace qi    = boost::spirit::qi;

struct mybase             { int a,b; };
struct myderived : mybase { int c,d; };

BOOST_FUSION_ADAPT_STRUCT(mybase,    (int,a)(int,b))
BOOST_FUSION_ADAPT_STRUCT(myderived, (int,a)(int,b)(int,c)(int,d))

int main()
{
    std::string const s = "1 2 3 4";
    auto f = s.begin(), l = s.end();

    qi::rule<decltype(f), mybase()   , qi::space_type> base_    = qi::int_ >>  qi::int_;
    qi::rule<decltype(f), myderived(), qi::space_type> derived_ = (base_ >> qi::int_ >> qi::int_) [what_is_the_attr()];

    myderived data;
    bool ok = qi::phrase_parse(f,l,derived_,qi::space,data);
}
