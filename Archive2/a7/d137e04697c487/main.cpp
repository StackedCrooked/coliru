#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <getopt.h>

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

struct columns
{
    std::string name;
    int words_;
    
    columns()
    : words_(1)
    {}
};

BOOST_FUSION_ADAPT_STRUCT(
    columns,
    (std::string, name)
    (int, words_)
)


namespace qi = boost::spirit::qi;
template<typename It, typename Skipper = qi::space_type>
struct cols_parser : qi::grammar<It,std::vector<columns>(), Skipper >
{
    cols_parser() : cols_parser::base_type(cols_)
    {
        str = +(qi::char_ - ':' - '|') ;
        cols_ =  (str >> -(':' >> qi::int_) ) % '|';
    }
    qi::rule<It,std::vector<columns>(), Skipper> cols_;
    qi::rule<It, std::string(), Skipper>  str;
    qi::symbols<char, int> types;
    
};


std::vector<columns> get_format(std::string format_string)
{
    std::vector<columns> form;
    typedef std::string::const_iterator iter;
    iter beg = format_string.begin();
    iter end = format_string.end();
    cols_parser<iter> rul;
    
    bool isp = qi::phrase_parse(beg,end, rul ,qi::space, form);
    
    if (!isp)
    {
        throw "Wrong format string" ;
    }
    
    return form;
}

const char* opts = 
"       -h,--help                       this text\r\n\
        -s N                            skip first N lines\r\n\
        --skip-first N      \r\n\
        -l N                            skip last N lines\r\n\
        --skip-last  N       \r\n\
        -f,--format \"format string\"   format string for columns\r\n\
";

#define STATBUFSIZE 1024

int main(int argc, char* argv[])
{
    std::string buffer;
    char  buf[STATBUFSIZE];
    size_t readed;
    
    while (readed = read(STDIN_FILENO, buf, STATBUFSIZE) )
    {
        buffer.insert(buffer.begin() + buffer.size(), buf, buf + readed);
    }
    
    std::string format = "mod|links|group|user|size|date:2|name";
    
    auto form = get_format(format);
    for (auto a : form)
    std::cerr << a.name << ":" << a.words_ << std::endl;
    
    std::vector<char>::const_iterator it;

}
