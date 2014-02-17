// test.cpp: определяет точку входа для консольного приложения.
//

//#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/support_line_pos_iterator.hpp>

#include <iomanip>

#include <boost/fusion/view/iterator_range.hpp>
#include <boost/fusion/include/iterator_range.hpp>
#include <boost/range/iterator_range.hpp>

#include <boost/chrono.hpp>

#include <string>
#include <map>
#include <vector>
#include <iostream>

typedef std::string::const_iterator iter;

namespace qi = boost::spirit::qi;

typedef boost::iterator_range<iter> type;

int main()
{
    std::string str = "abc123, def8hju9sdf, ajgisdughs,lock_ed,shark,another_word";

	std::vector<type>		 pi;
	std::vector<std::string> vec;

	size_t num_of = 20000;
	boost::chrono::high_resolution_clock::time_point start = boost::chrono::high_resolution_clock::now();
	for (size_t ix = 0; ix < num_of; ix++){
		pi.clear();
		bool result = qi::phrase_parse(str.begin(), str.end(),
			qi::raw[+(qi::char_ - ',')] % ',', qi::space, pi);
	}
	boost::chrono::milliseconds ms = boost::chrono::duration_cast<boost::chrono::milliseconds> (boost::chrono::high_resolution_clock::now() - start);
	std::cout << "Iterator time: " << ms.count() << std::endl;
	
	start = boost::chrono::high_resolution_clock::now();
	for (size_t ix = 0; ix < num_of; ix++){
		vec.clear();
		bool result = qi::phrase_parse(str.begin(), str.end(),
			qi::raw[+(qi::char_ - ',')] % ',', qi::space, vec);
	}
	ms = boost::chrono::duration_cast<boost::chrono::milliseconds> (boost::chrono::high_resolution_clock::now() - start);
	std::cout << "String time: " << ms.count() << std::endl;


	for (auto& m : vec){
//		std::cout << std::string(m.begin(), m.end()) << std::endl;
	}
	int k; std::cin >> k;
	return 0;
}