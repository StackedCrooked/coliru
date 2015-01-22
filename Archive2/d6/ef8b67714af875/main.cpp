#include <iostream>
#include <string>
#include <vector>
#include <regex>

int main()
{
   std::regex re("\\D+(\\d+)");
   const std::string test = "bla1 bla2 bla100 bla bla123 bla500 bla999 bla";
   auto begin = std::sregex_iterator(test.begin(), test.end(), re), end = std::sregex_iterator();
   std::vector<std::string> numbers;
   while (begin != end)
   {
      auto match = *begin;
      if (match.size() > 1)
      {
         numbers.push_back(match[1].str());
      }
      ++begin;
   }
   for (const auto& n : numbers)
   {
      std::cout << n << std::endl;
   }
}
