#include <iostream>

#include <string>
#include <regex>
#include <map>
#include <numeric>

std::string format(const std::string& format, 
                   const std::map<std::string, std::string>& map)
{
  using tokeniter = std::sregex_token_iterator;

  static const std::regex  kDirective{ R"((\{[_[:alpha:]][_[:alnum:]]*\}))"};

  bool matched = true;
  auto opacc = [&] (std::string acc, const tokeniter::value_type& sm) 
  {
    matched = !matched;

    if (!matched)
      return acc + sm.str();

    const auto replace = map.find(std::string{sm.first+1, sm.second-1});
    return  acc + (replace == end(map) ? sm.str() : replace->second);
  };

  const tokeniter first{ begin(format), end(format), kDirective, {-1,1} };
  const tokeniter last {};
  return std::accumulate(first, last, std::string{}, opacc);
}

int main()
{
  std::cout << format("a{b1}aaa {a1} {a2} {{a3} bbb", { { "a1", "@11" }, { "a2", "222" } }) << std::endl;
  // expected : a{b1}aaa @11 222 {{a3} bbb 

  std::cout << format("aaa {} {{}} {a1} bbb}", { { "a1", "111" } }) << std::endl;
  // expected : aaa {} {{}} 111 bbb}
  return 0;
}