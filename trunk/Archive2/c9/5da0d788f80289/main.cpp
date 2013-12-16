#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> tokenize(const std::string& input)
{
  std::vector<std::string> result;
  std::istringstream stream(input);
  std::string thingie; // please choose a better name, my inspiration is absent today
  while(std::getline(stream, thingie, '('))
  {
    if(std::getline(stream, thingie, ')'))
      result.push_back(thingie);
    else
      throw std::runtime_error("expected \')\' to match \'(\'.");
  }
  return result;
}

int main()
{
  std::string test = "(23567)=(58765)+(67888)+(65678)";
  auto tokens = tokenize(test);
  for(auto&& item : tokens)
    std::cout << item << '\n';
}
        