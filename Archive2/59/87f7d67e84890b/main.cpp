#include <iostream>
#include <iterator>
#include <regex>
#include <string>
 
int main()
{
   std::string text = "Quick brown fox";
   std::regex vowel_re("a|e|i|o|u");
 
   // write the results to an output iterator
   std::regex_replace(std::ostreambuf_iterator<char>(std::cout),
                      text.begin(), text.end(), vowel_re, "*");
 
   // construct a string holding the results
   std::cout << '\n' << std::regex_replace(text, vowel_re, "[$&]") << '\n';
}