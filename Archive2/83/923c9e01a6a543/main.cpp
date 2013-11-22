#include <iostream>
#include <boost/regex.hpp>
#include <string>
#include <vector>

int
main (int argc, char *argv[])
{
  std::vector<std::string> vec {
    "hello", "w0rld"
  };

  for (auto& haystack : vec) {
    if (boost::regex_match (haystack, boost::regex ("[a-z]+"))) {
      std::cout << haystack << " matches!" "\n";
    } else {
      std::cout << haystack << " doesn't match.." "\n";
    }
  }
}