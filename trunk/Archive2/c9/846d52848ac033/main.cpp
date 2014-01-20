#include <iostream>
#include <algorithm>
#include <vector>

#include <string>

    void remove_vowels_accept(std::string the_string)                                                                                                      
    {                                                                                                                                                   
      std::replace(the_string.begin(),the_string.end(),'a','x');                                                                                      
      std::replace(the_string.begin(),the_string.end(),'A','x');                                                                                      
      std::replace(the_string.begin(),the_string.end(),'e','x');                                                                                          
      std::replace(the_string.begin(),the_string.end(),'E','x');                                                                                      
      std::replace(the_string.begin(),the_string.end(),'i','x');                                                                                        
      std::replace(the_string.begin(),the_string.end(),'I','x');                                                                                      
      std::replace(the_string.begin(),the_string.end(),'o','x');                                                                                      
      std::replace(the_string.begin(),the_string.end(),'O','x');                                                                                         
      std::replace(the_string.begin(),the_string.end(),'u','x');                                                                                      
      std::replace(the_string.begin(),the_string.end(),'U','x');                                                                                      
      std::replace(the_string.begin(),the_string.end(),'~',' ');                                                                                      
      std::cout<<"the replaced string is :"<<the_string<<std::endl;                                                                                             

  }          

int main() {
    remove_vowels_accept("aeiou AEIOU");
}