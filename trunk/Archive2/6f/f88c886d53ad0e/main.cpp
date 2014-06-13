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
        -s,--skip-first N               skip first N lines\r\n\
        -l,--skip-last  N               skip last N lines\r\n\
        -f,--format \"format string\"   format string for columns\r\n\
";

struct option longopts[] = {
    {"help"      , 0, 0, 'h'},
    {"skip-first", 1, 0, 's'},
    {"skip-last" , 1, 0, 'l'},
    {"format"    , 1, 0, 'f'},
    {0           , 0, 0,  0 }
};


#define STATBUFSIZE 1024

template<typename Iterator>
struct printit
{
    Iterator b,e;
    
    printit(Iterator begin, Iterator end)
    : b(begin),e(end)
    {}
    
    printit(std::pair<Iterator,Iterator> p)
    : b(p.first),e(p.second)
    {}
    
    template<typename It>
    friend std::ostream& operator << (std::ostream& os, printit<It> const& val)
    {
        std::ostream_iterator<char> oiter(os);
        std::copy(val.b,val.e,oiter);
        return os;
    }
};

template<typename Iterator>
std::pair<Iterator,Iterator> next_line(Iterator& begin, Iterator end, char div = 0)
{
    while (std::isspace(*begin) && (begin != end)) begin++;
    Iterator last = begin;
    
    if (div == 0)
        while ((!std::isspace(*last)) && last != end) last++;
    else 
        while ((*last != div) && last != end) last++;
        
    if (begin == end)
        return std::make_pair(end,end);
        
    auto first = begin; begin = last;
    return std::make_pair(first,last);
}

template<typename Iterator>
bool lasted(Iterator begin, Iterator end)
{
    while (std::isblank(*begin) && (begin != end)) begin++;
    
    if (begin == end)
        return true;
    
    return false;
}



template<typename Iterator>
bool is_pair_empty(std::pair<Iterator,Iterator> p)
{
    return (p.first != p.last);
}


int main(int argc, char* argv[])
{
    std::string buffer;
    char  buf[STATBUFSIZE];
    size_t readed;
    
    while (readed = read(STDIN_FILENO, buf, STATBUFSIZE) )
    {
        buffer.insert(buffer.begin() + buffer.size(), buf, buf + readed);
    }
    
    size_t skip_last = 0, skip_first = 0;
    std::string format = "";
    
    int optix, opt;
    
    while( (opt = getopt_long(argc,argv,"hs:l:f:",longopts,&optix)) != -1 )
    {
        switch (opt) {
            case 'h' : 
                std::cerr << opts ;
                return 0;
            case 'l' :
                if (optarg)
                    skip_last = atoi(optarg); 
                else 
                {
                    std::cerr << "No have count of last skip lines" << std::endl;
                    return 0;
                }
                break;
            case 's' :
                if (optarg)
                    skip_first = atoi(optarg);
                else 
                {
                    std::cerr << "No have count of first skip lines" << std::endl;
                    return 0;
                }
                break;
            case 'f' :
                if (optarg)
                    format = optarg;
                else 
                {
                    std::cerr << "No have an format option" << std::endl;
                    return 0;
                }
                break;
        }
    }
    

    
    if (format == "")
    {
        std::cerr << "No have an format option" << std::endl;
        return 0;
    }
    
    auto first = buffer.begin();
    auto last = buffer.end();
    
    while (skip_first)
    {
        first = std::find(first,last,'\n');
        skip_first--;
        
        if (last == first)
            return 0;
    }

    while (skip_last)
    {
        while ( (*(last--) != '\n') && ( last > first) ) ;
        if (last <= first) return 0;
        skip_last--;
    }
    
    std::vector<columns> cols;
    auto begin = format.begin();
    auto end   = format.end();
    cols_parser<decltype(first)> cparser;
    
    bool res = qi::phrase_parse(begin,end,cparser,qi::space,cols);
    if (!res)
    {
        std::cerr << "Wrong format of format string" << std::endl;
        return 0;
    }
    
    //std::istringstream is(result);
    
    
    first++;
    last++;
    std::ostringstream os;
    while (first < last) 
    {
        os << "{ ";
        for (size_t ix = 0 ; ix < cols.size(); ix++)
        {

            os << "\"" << cols[ix].name  << "\":\"";
            if (ix != cols.size() - 1){
                for (int ixwords = 0; ixwords < cols[ix].words_; ixwords++)
                {
                    auto nl = next_line(first,last);
                    if (ixwords) os << " ";
                    os << printit<decltype(first)>(nl);
                }
                os << "\",";
            }
            else 
            {
                auto nl = next_line(first,last,'\n');
                os << printit<decltype(first)>(nl);
                os << "\"}\n";
            }
        }
        
        if (lasted(first,last))
            break;
    }
    
    std::cerr << os.str() << std::endl;
    
}
