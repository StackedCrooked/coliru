
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <tuple>



int main()
{
  std::string json_string = R"abc({"ololo" : "olo\lo"})abc";
  std::cerr << json_string << std::endl;
}