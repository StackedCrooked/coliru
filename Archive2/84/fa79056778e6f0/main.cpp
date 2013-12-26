// regex_match example
#include <iostream>
#include <string>
#include <regex>

int main () {
  try {
    if(std::regex_match ("3", std::regex("[0-9]") ))
        std::cout << "string literal matched\n";
  } catch (std::regex_error& e) {
     using namespace std::regex_constants;
     switch(e.code()) {
        case error_badrepeat:
          std::cerr << "Repeat was not preceded by a valid regular expression.\n";
          break;
          
        case error_brack:
          std::cerr << "The expression contained mismatched brackets ([ and ]).\n";
          break;
        
        case error_paren:
          std::cerr << "The expression contained mismatched parentheses (( and )).\n";
          break;
          
        default:
          std::cerr << "Some other regex exception happened.\n";
          break;
     }
  }
  return 0;
}