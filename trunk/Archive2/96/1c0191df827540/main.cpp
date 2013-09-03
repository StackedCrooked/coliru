#include <iostream>

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/at.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace fusion = boost::fusion;

struct assign
{
    template <typename Attr, typename Context>
    void operator()(Attr& attr, Context& con, bool& pass) const
    {
        fusion::at_c<0>(con.attributes)=attr;
        pass=true;
    }
};

struct add_assign
{
    template <typename Attr, typename Context>
    void operator()(Attr& attr, Context& con, bool& pass) const
    {
        fusion::at_c<0>(con.attributes)+=attr;
        pass=true;
    }
};

struct sub_assign
{
    template <typename Attr, typename Context>
    void operator()(Attr& attr, Context& con, bool& pass) const
    {
        fusion::at_c<0>(con.attributes)-=attr;
        pass=true;
    }
};


int main()
{
    std::string INPUT_DATA = "12e-1 + 3.4 - .67";
    typedef std::string::iterator iterator_type;
    iterator_type begin = std::begin(INPUT_DATA);
    iterator_type end = std::end(INPUT_DATA);

    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::qi::ascii;

    auto parser = qi::double_[assign()]                      // (1)
        >> *(
                (qi::lit('+') >> qi::double_[add_assign()])     // (2)
                |
                (qi::lit('-') >> qi::double_[sub_assign()])     // (3)
            );

    double result;
    bool ok = qi::phrase_parse(begin, end, parser, ascii::space, result);

    if ( ok  && begin == end)
    {
        std::cout << "parsed, result = " << result << std::endl;
    }
    else
    {
        std::cout << "not parsed" << std::endl;
    }

    return 0;
}