#include <iostream>
#include <vector>
#include <regex>

std::vector<std::string> get_numbers(std::string const& s)
{
    static std::regex regex(R"(^\((\d+)\)=\((\d+)\)(?:\+\((\d+)\))+$)",
                            std::regex_constants::ECMAScript
                            | std::regex_constants::optimize);

    std::vector<std::string> results;
    std::sregex_iterator const last;
    for (std::sregex_iterator first(s.cbegin(), s.cend(), regex);
         last != first;
         ++first)
    {
        results.push_back(first->str());
    }

    return results;
}

int main()
{
  std::string test = "(23567)=(58765)+(67888)+(65678)";
  auto tokens = get_numbers(test);
  for(auto&& item : tokens)
    std::cout << item << '\n';
}