#include <map>
#include <iostream>
#include <functional>
#include <string>
#include <strings.h>
int main()
{
   typedef std::function<bool(const std::string&, const std::string&)> Comparator;
   
   Comparator comp = [](const std::string& s1, const std::string& s2){ return (strcasecmp(s1.c_str(), s2.c_str() ) < 0); };
   
   std::map<std::string, int, Comparator> map;
   
   std::string str1 = "bus";
   std::string str2 = "Bus";
   
   map[str2] = 1;
   map[str1] = 2;
   
   auto found = map.find("bus");
   
   if (found != map.end())
   {
      std::cout << found->first;
   }
}