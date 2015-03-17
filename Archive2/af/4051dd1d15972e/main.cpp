
#include <iostream>
#include <algorithm>
#include <string>

/// Try to find in the Haystack the Needle - ignore case
bool findStringIC(const std::string & strHaystack, const std::string & strNeedle)
{
  auto it = std::search(
    strHaystack.begin(), strHaystack.end(),
    strNeedle.begin(),   strNeedle.end(),
    [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
  );
  return (it != strHaystack.end() );
}

int main(void)
{
  std::cout << "Fox Found?  " << findStringIC("Brown fox jump", "fox") << std::endl;
  std::cout << "None Found? " << findStringIC("Brown fox jump", "none") << std::endl;
  std::cout << "X Found?    " << findStringIC("Brown fox jump", std::string(1, 'x') ) << std::endl;
  std::cout << "Y Found?    " << findStringIC("Brown fox jump", std::string(1, 'y') ) << std::endl;
}
