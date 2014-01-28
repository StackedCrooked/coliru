#include <boost/fusion/adapted.hpp>
#include <boost/spirit/home/qi.hpp>

namespace qi = boost::spirit::qi;

template < typename _Type, typename _Iterator, typename _Enable = void >
struct parser;

template < typename _Type, typename _Iterator >
struct parser < _Type, _Iterator, typename std::enable_if < std::is_arithmetic<_Type> ::value > ::type > :
    qi::grammar<_Iterator, _Type() >
{
    parser()
        : parser::base_type(impl)
    {
        impl = qi::create_parser<_Type>() ;
    }

    qi::rule<_Iterator, _Type()> impl;
};

template < typename _Iterator >
struct parser < double, _Iterator> :
    qi::grammar<_Iterator, double() >
{
    parser()
        : parser::base_type(impl)
    {
        impl = qi::double_;
    }

    qi::rule<_Iterator, double()> impl;
};

template < typename _First, typename _Second, typename _Iterator >
struct parser < std::pair<_First, _Second>, _Iterator> :
    qi::grammar<_Iterator, std::pair<_First, _Second>() >
{
    parser()
        : parser::base_type(impl)
    {
        impl =  qi::lit('(') >> first >> ',' >> second >> ')';
    }

    qi::rule<_Iterator, std::pair<_First, _Second>()> impl;

    parser<_First, _Iterator> first;
    parser<_Second, _Iterator> second;
};

template < typename _Type, typename _Alloc, typename _Iterator >
struct parser < std::vector<_Type, _Alloc>, _Iterator> :
    qi::grammar<_Iterator, std::vector<_Type, _Alloc>() >
{
    parser()
        : parser::base_type(impl)
    {
        impl = qi::lit('[') >> qi::omit[qi::uint_] >> ",(" >> item % ',' >> ")]";
    }

    qi::rule<_Iterator, std::vector<_Type, _Alloc>()> impl;

    parser<_Type, _Iterator> item;
};

int main(int agrc, char *argv[])
{
    typedef std::pair<double, int> pair;

    using string = std::string;

    string input_ = { "[1,((0.97,5),(1.75,10))]" };

    string::const_iterator iterator_ = input_.begin();
    string::const_iterator end_ = input_.end();

    std::vector<pair> pairs_;

    bool result_ = qi::parse(iterator_, end_, parser <std::vector<pair>, string::const_iterator> (), pairs_);

    return result_? 0 : 255;
}
