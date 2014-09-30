#include <iostream>
#include <regex>
using namespace std;


int main() {
  std::string s_rgx(R"([[:punct:] ]([a-z]+)[[:punct:] ]season(?:[[:punct:] ]|$))");
  try
  {
    const std::regex rgx(s_rgx, std::regex_constants::icase);
    std::string input("My killing season (first season)");
    std::smatch results;
    if (std::regex_search(input, results, rgx))
    {
      std::cout << "search positive:" << std::endl;
      for (auto res : results)
        std::cout << "\t\"" << std::string(res.first, res.second) << "\"" << std::endl;
    }
    else
      std::cout << "search negative" << std::endl;
  }
  catch (std::regex_error&  e)
  {
    std::cout << "invalid input" << std::endl;
  }
  return 0;
}