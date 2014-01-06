#include <iostream> 
#include <string> 
#include <regex> 


int main() 
{
  std::regex regex_to_use("(a?b*)*");
  std::string string_to_test("aaa"); 
  
  std::cout << std::boolalpha 
            << std::regex_match(string_to_test.cbegin(), string_to_test.cend(), regex_to_use) 
            << std::endl;

  #if defined _MSC_VER
    std::cin.get(); 
  #endif 
   
  return 0; 
}

