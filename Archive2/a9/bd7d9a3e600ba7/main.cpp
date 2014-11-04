/* Noobleeeeeeeeeeeeeeeee */

#include <algorithm>
#include <string>
#include <iostream>
 
std::string alphabet("abcdefghijklmnopqrstuvwxyz");
 
bool isPangram(std::string s) 
{
  transform(s.begin(), s.end(), s.begin(), ::tolower);
  sort(s.begin(), s.end());
  return includes(s.begin(), s.end(), alphabet.begin(), alphabet.end());
}

int main()
{
    std::string Input;
    std::getline(std::cin, Input);
    if(isPangram(Input))
    {
        std::cout << "pangram" << std::endl;
    }
    else
    {
        
        std::cout << "not pangram" << std::endl;
        
    }
    
    return 0;
}