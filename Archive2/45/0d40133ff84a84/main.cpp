#include <iostream>
#include <string>
#include <boost/regex.hpp>

int main () {    
  std::string url = "IAB10-3";
  boost::regex exp("[0-9]+");
  boost::smatch match;
  std::cout << "Result" << std::endl;
  if (boost::regex_search(url, match, exp))
  {
    std::cout << std::string(match[0].first, match[0].second);
  }    
}