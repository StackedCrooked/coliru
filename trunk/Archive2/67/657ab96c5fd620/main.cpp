#include <iostream>
#include <stdlib.h>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

int main()
{

    static const boost::regex
        date_regex("v\\d+\\.\\d+\\.\\d+-\\d+");

    {

        const char *input_cstr = "v0.52.0-9876";
        boost::cmatch char_matches;
        if (boost::regex_match(input_cstr, char_matches, date_regex))
        {
            
            std::cout << "1 "<< char_matches[0] << '\n';
            std::cout << "2 " << char_matches[1] << '\n';
            std::cout << "3 " << char_matches[2]  << '\n';
            std::cout << "4 " << char_matches[3]  << '\n';
        } 
        else
        {
            std::cout << "First example should have matched the regex.\n";
        }
    }

}