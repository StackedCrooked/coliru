#include <boost/regex.hpp>
#include <iterator>
#include <iostream>
#include <string>


int main()
{
    const std::string s = "AwBcDoFgAgHmLoCb";
 
    boost::regex words_regex("[A-Z][a-z]");
    auto words_begin = 
        boost::sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = boost::sregex_iterator();
 
    /* std::cout << "Found " 
              << std::distance(words_begin, words_end) 
              << " words:\n";
    */
    
    for (boost::sregex_iterator i = words_begin; i != words_end; ++i) {
        boost::smatch match = *i;                                                 
        std::string match_str = match.str(); 
        std::cout << match_str << '\n';
    }   
}