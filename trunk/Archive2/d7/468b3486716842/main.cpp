#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
//#define BOOST_SPIRIT_DEBUG

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

std::vector<char> o;

#define SETWF(W,F) std::setw(W) << std::setfill(F) 

struct long_iso_time 
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    
    friend
    std::ostream & operator << (std::ostream & os, long_iso_time const & t){
        os << t.year << '-' << SETWF(2,'0')  << t.month << '-' << SETWF(2,'0') << t.day
           << ' '    << SETWF(2,'0') << t.hour << ':' << SETWF(2,'0') << t.minute;
           
        return os;
    }
};

BOOST_FUSION_ADAPT_STRUCT(
    long_iso_time,
    (int,year)
    (int,month)
    (int, day)
    (int,hour)
    (int,minute)
)
    
namespace qi = boost::spirit::qi;
template<typename It, typename Skipper = qi::space_type>
struct long_iso_time_parser : qi::grammar<It,long_iso_time(), Skipper >
{
    long_iso_time_parser() : long_iso_time_parser::base_type(time_)
    {
        
        hour=minute=day=year=month = qi::int_;
        time_ = year >> '-' >> month >> '-' >> day >> hour >> ':' >> minute;
        
        BOOST_SPIRIT_DEBUG_NODES((year)(month)(hour)(day)(minute));
    }
    qi::rule<It, int(), Skipper> hour,minute,day,year,month;
    qi::rule<It,long_iso_time(), Skipper> time_;
};

    enum coltypes
    {
        string = 0,
        integer,
        date
    };

struct columns
{
    std::string name;
    int type_;
};

BOOST_FUSION_ADAPT_STRUCT(
    columns,
    (std::string, name)
    (int, type_)
)


template<typename It, typename Skipper = qi::space_type>
struct cols_parser : qi::grammar<It,std::vector<columns>(), Skipper >
{
    cols_parser() : cols_parser::base_type(cols_)
    {
        str = +(qi::char_ - ':') ;
        cols_ =  (str >> ':' >> qi::int_) % '|';
   
 /*   types.add
        ("s",coltypes::string)
        ("i",coltypes::integer)
        ("dt", coltypes::date);
   */     
    }
    qi::rule<It,std::vector<columns>(), Skipper> cols_;
    qi::rule<It, std::string(), Skipper>  str;
    qi::symbols<char, int> types;
    
};

typedef boost::variant<std::string, int , long_iso_time> result_type;

#define STATBUFSIZE 1024

int main(int argc, char* argv[])
{
    std::vector<char> buffer;
    char  buf[STATBUFSIZE];
    size_t readed;
    
    while (readed = read(STDIN_FILENO, buf, STATBUFSIZE) )
    {
        buffer.insert(buffer.begin() + buffer.size(), buf, buf + readed);
    }
    
    
    long_iso_time lit;
    char const* abc = "2014-06-08 22:00";
    long_iso_time_parser<const char*> par;
    
    bool isp = qi::phrase_parse(abc,abc + strlen(abc), par, qi::space, lit);
    
    /*Just parsing error - normal exit*/
    if (!isp)
                return 0;
    std::string format = "mod:s|links:i|group:s|user:s|size:i|date:dt|name:s";
    //std::string format = "mod|links|group|user|size|date|name";
    
    std::vector<columns> form;
    typedef std::string::const_iterator iter;
    iter beg = format.begin();
    iter end = format.end();
    cols_parser<iter> rul;
    
    isp = qi::phrase_parse(beg,end, rul ,qi::space, form);
    std::cerr << lit << std::endl;
    
    for (auto a : form)
    std::cerr << a.name << ":" << a.type_ << std::endl;
    
    std::vector<char>::const_iterator it;
    
    /*Skip 1st line*/
    while (it++ != '\n');
    
    std::vector<std::vector<result_type> > vec_res;
    while (it < buffer.end())
    {
        std::vector<result_type> tp;
        for (size_t ix = 0; ix < form.size(); ix++)
        {
        }
    }

    

}
