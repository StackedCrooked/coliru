#include <boost/regex.hpp>
#include <string>
#include <iostream>
int main(){
std::string s = "this is a test string";
s = boost::regex_replace(s, boost::regex("\\s"), "\\\\s*");

std::cout << s << std::endl;
}