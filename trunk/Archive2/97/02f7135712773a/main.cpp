#include <iostream>
#include <string>
#include <regex>

int main ()
{
  std::string My_String = "delta = -002.050";
  std::smatch Match;
  std::regex Base(R"([0-9]+(\.[0-9]+)?)"); 

  if(std::regex_search(My_String,Match,Base)) {
      std::ssub_match Sub_Match = Match[1];
      std::string Sub_String = Sub_Match.str();
      std::cout << Sub_String << std::endl;
  }
}
