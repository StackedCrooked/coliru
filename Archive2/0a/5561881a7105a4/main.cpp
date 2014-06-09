
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
//#define BOOST_SPIRIT_DEBUG

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/phoenix/operator.hpp>
#include <boost/spirit/include/qi_no_skip.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

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
			os << t.year << '-' << SETWF(2, '0') << t.month << '-' << SETWF(2, '0') << t.day
				<< ' ' << SETWF(2, '0') << t.hour << ':' << SETWF(2, '0') << t.minute;

			return os;
		}
};

BOOST_FUSION_ADAPT_STRUCT(
	long_iso_time,
	(int, year)
	(int, month)
	(int, day)
	(int, hour)
	(int, minute)
	)



	typedef boost::variant<std::string, int, long_iso_time> result_type;


#define STATBUFSIZE 1024

struct ls_la
{
	std::string mod;
	int         links;
	std::string group;
	std::string user;
	int         size;
	long_iso_time time;
	std::string name;

	friend std::ostream & operator << (std::ostream & os, ls_la const& val)
	{
		os << val.mod << " " << val.links << " " << val.group << " " << val.user << " " << val.size << " " << val.time << " " << val.name;
		return os;
	}
};


BOOST_FUSION_ADAPT_STRUCT(
	ls_la,
	(std::string, mod)
	(int, links)
	(std::string, group)
	(std::string, user)
	(int, size)
	(long_iso_time, time)
	(std::string, name)
	)

namespace qi = boost::spirit::qi;
template<typename It, typename Skipper = qi::space_type>
struct ls_la_parser : qi::grammar<It, std::vector<ls_la>(), Skipper >
{
	ls_la_parser() : ls_la_parser::base_type(res_)
	{
		hour = minute = day = year = month =links =size = qi::int_;
        mod = group = user =  -qi::no_skip[' '] >> +(qi::char_ - qi::no_skip[' ']);
        name = -qi::no_skip[' '] >> +(qi::char_ - qi::no_skip['\n']);
		time_ = year >> '-' >> month >> '-' >> day >> hour >> ':' >> minute;
		elem_ = mod >> links >> group >> user >> size >> time_ >> name;
		res_ = elem_ % qi::no_skip['\n'];
        BOOST_SPIRIT_DEBUG_NODES( (group)(user)(links)(size)(name)(mod)(time_) (elem_)(res_));
	}
	qi::rule<It, int(), Skipper> hour, minute, day, year, month;
	qi::rule<It, long_iso_time(), Skipper> time_;
	qi::rule<It, std::vector<ls_la>(), Skipper> res_;
	qi::rule<It, ls_la(), Skipper> elem_;
    qi::rule<It, std::string(), Skipper> mod,group,user,name;
    qi::rule<It, int(), Skipper> size, links;
};

int main(int argc, char* argv[])
{
	std::vector<char> buffer;
	char  buf[STATBUFSIZE];
	size_t readed;

	std::vector<ls_la> ls_vec;

	while (readed = read(STDIN_FILENO, buf, STATBUFSIZE))
	{
		buffer.insert(buffer.begin() + buffer.size(), buf, buf + readed);
	}

    
	typedef std::vector<char>::iterator iter;
	iter beg = buffer.begin();
	iter end = buffer.end();
    while(*(beg++) != '\n') ;
	ls_la_parser<iter> ls_par;
	bool isp = qi::phrase_parse(beg, end, ls_par, qi::space, ls_vec);
    
    for (size_t ix = 0; ix < ls_vec.size() ; ix++)
        for (size_t ix2 = 0; ix2 < ls_vec.size() - 1; ix2++){
            if (ls_vec[ix2].size > ls_vec[ix2 + 1].size ){
                ls_la l = ls_vec[ix2];
                ls_vec[ix2] = ls_vec[ix2+1];
                ls_vec[ix2 + 1] = l;
            }
            
        }

	for (auto& a : ls_vec)
		std::cerr << a << std::endl;
	

}
