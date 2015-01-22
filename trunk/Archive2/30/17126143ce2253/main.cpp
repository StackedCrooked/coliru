#include <map>
#include <string>
#include <iostream>
#include <iterator>
 
int main() {
  std::map<std::string,std::string> a_map;
  a_map["Geely"]    = "Chinese";
  a_map["Peugeot"]  = "French";
  a_map["Mercedes"] = "German";
  a_map["Toyota"]   = "Japanese";
  a_map["Ford"]     = "American";
  a_map["Fiat"]     = "Italian";
 
  for (auto it = a_map.cbegin(); it != std::next(a_map.cbegin(), 3); ++it) {
    std::cout << it->first << " : " << it->second << '\n';
  }
}