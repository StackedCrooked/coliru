#include <boost/regex.hpp>
#include <string>
#include <iostream>
int main(){
std::string s = "6+-3++5";
s = boost::regex_replace(s, boost::regex("(\\d+)[-+]"), "$1");

std::cout << s << std::endl;
}