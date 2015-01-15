#include <iostream>
#include <iterator>
#include <string>
#include <regex>
 
int main()
{
//    std::string s = "Some people, when confronted with a problem, think "
//        "\"I know, I'll use regular expressions.\" "
//        "Now they have two problems.";

    std::string s = "This is a text for **bold* characters using regular expressions."
    "\nThis is another **bold2* character.";

    std::cout << s <<"\n***************\n";
    std::regex bold_regex("(\\*\\*)(\\w+)(\\*)"); 
    std::string new_s = std::regex_replace(s, bold_regex, "<b>$2</b>");
    std::cout << new_s << '\n';
}