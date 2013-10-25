#include <boost/algorithm/string.hpp> 
#include <locale> 
#include <iostream> 
#include <algorithm> 

int main() 
{ 
  //std::locale::global(std::locale("German")); 
  std::string s = boost::algorithm::trim_copy(std::string("test.example.com:")); 
  std::string ip = s.substr(0,s.find(":"));
  std::string port("0");
  if (ip.size()+1 < s.size()) port = s.substr(ip.size()+1);
  
  std::cout << "¦" << ip << "¦" << std::endl; 
  std::cout << "¦" << port << "¦" << std::endl; 
} 
