#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#define BOOST_REGEX_MATCH_EXTRA
#include <boost/regex.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/join.hpp>

int main(int argc, const char* argv[])
{
    std::string s1 = "abcd<ht";
    std::string s2 = "ml>giuya";
    
    boost::iterator_range<std::string::iterator> ir1 = boost::make_iterator_range(s1);
    boost::iterator_range<std::string::iterator> ir2 = boost::make_iterator_range(s2);
    auto ir3 = boost::join(ir1,ir2);
    
    boost::regex e("<[^>]*>");
    boost::match_results<decltype(ir3)::iterator> what;
    
    boost::regex_search(ir3.begin(), ir3.end(), what, e, 
                        boost::match_default | boost::match_partial);
    std::cout << std::string(what[0].first, what[0].second) << std::endl;
    //std::cout << what[0].second << std::endl;
}