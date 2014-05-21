#include <iostream>
#include <string>
#include <sstream>
#include <regex>

int main() {
  std::string name = "libsigc\\+\\+";
  std::string full_name = "libsigc++-1.2.3-x86_64-1";
  std::string string_pat = "-([^-]*)-([^-]*)-([^-]*)$";
  std::ostringstream oss;
  oss << '^' << name << string_pat;
  
  std::cout << oss.str() << "\n";
  std::regex expr(oss.str(), std::regex::egrep);

  if (std::regex_match(full_name, expr))
    std::cout << full_name << " matched!\n";
  else
    std::cout << full_name << " did not match!\n";
}
