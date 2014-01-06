#include <iostream>
#include <string>
#include <regex>

#include <cstdlib>

int main() {
  std::string line;
  std::getline(std::cin, line);

  const std::string liveVarRegexStr = R"(X\(\s*([+-]?[A-Fa-f0-9.]+)\s*\))";
  const std::regex liveVarRegex(liveVarRegexStr);
  std::smatch match;
    
  auto lineStart = line.begin();
  const auto lineEnd = line.end();
  const bool matched = std::regex_search(lineStart, lineEnd, match, liveVarRegex);
  
  return EXIT_SUCCESS;
}
