#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <boost/lambda/lambda.hpp>


int main()
{
    std::vector<std::string> words;
    words.push_back("Helo");
    words.push_back("from");
    words.push_back("GCC");
    words.push_back("__VERSION__");

    
    
    std::transform(words.begin(), words.end(), words.begin(), boost::lambda::_1+"ZZ" );
    
    std::for_each(words.begin(),words.end(), std::cout<< boost::lambda::_1 );

     
}
