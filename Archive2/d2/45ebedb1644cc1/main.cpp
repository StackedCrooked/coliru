#include <boost/regex.hpp>
#include <string>
#include <iostream>
int main(){
std::string host = "http://aguilobo.com"; 
boost::regex expression(R"((?:\w*:\/\/)(?:w{0,3}\.)?(\w+\.\w+\.?\w*)(?::\d+)?\/?)");
boost::match_results<std::string::const_iterator> matches;
if (boost::regex_search(host, matches, expression))
{
     std::string result = matches[1];
     std::cout << result << std::endl;
}



}