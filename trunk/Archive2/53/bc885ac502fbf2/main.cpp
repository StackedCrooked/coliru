#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>

std::vector<double> tokenize(const std::string& input)
{
  std::vector<double> result;
  std::istringstream stream(input);
  std::string thingie; // please choose a better name, my inspiration is absent today
  while(std::getline(stream, thingie, '('))
  {
    if(std::getline(stream, thingie, ')'))
    {
      try
      {
        result.push_back(boost::lexical_cast<double>(thingie));
      }
      catch(...)
      {
        throw std::runtime_error("This wasn't just a number, was it?");
      }
    }
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
  test = "(2h567)=(58765)+(67888)+(65678)";
  tokens = tokenize(test);
}
