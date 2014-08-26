#include <iostream>
#include <string>
#include <regex>

// Typed in by the user
const std::vector<std::string> ins_names = { "Blue Cross Blue Shield of Illinois", "BCBS of IL", "BCBS IL", "BCBS TX", "Blue Cross and Blue Shield Texas", "Does not match any" };

// From ins_comp
const std::vector<std::string> matcher = { R"r(\b(Delta)\b.*\b(Dental)\b.*\b(Illinois|IL|Illanoise)\b)r", R"r(\b(Blue|BC|BCBS)\b.*\b(Illinois|IL)\b)r", R"r(\b(Delta)\b.*\b(Dental)\b.*\b(Texas|TX)\b)r", R"r(\b(Blue|BC|BCBS)\b.*\b(Texas|TX)\b)r" };

int main()
{

  for (auto & co_name : ins_names) {
    for (auto &regex_expr : matcher) {
      std::cout << "Checking if [" << co_name << "] matches [" << regex_expr << "]  = ";
      std::regex self_regex(regex_expr, std::regex_constants::ECMAScript | std::regex_constants::icase);
      if (std::regex_search(co_name, self_regex)) {
          std::cout << "Yes" << std::endl << std::endl;
      } else {
          std::cout << "No" << std::endl;
      }
    }
  }
  std::cout << "Done" << std::endl;
}

