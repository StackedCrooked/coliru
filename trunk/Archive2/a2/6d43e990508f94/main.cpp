#include <boost/regex.hpp>
#include <string>
#include <iostream>
#include <boost/version.hpp>

int main(){
std::string s = "this is a test string";
s = boost::regex_replace(s, boost::regex("\\s"), "\\\\s*");

std::cout << s << std::endl;
std::cout << "Using Boost "     
          << BOOST_VERSION / 100000     << "."  // major version
          << BOOST_VERSION / 100 % 1000 << "."  // minior version
          << BOOST_VERSION % 100                // patch level
          << std::endl;
}