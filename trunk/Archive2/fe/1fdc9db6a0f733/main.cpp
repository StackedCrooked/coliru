#include <iostream>
#include <string>
#include <regex>
 
int main()
{
    std::string s = "for a good time, call 867-5309";
    std::regex phone_regex("\\d{3}-\\d{4}");
    std::smatch phone_match;
 
    if (std::regex_search(s, phone_match, phone_regex)) {
        std::string fmt_s = phone_match.format(
            "$`"    // $` means characters before the match
            "[$&]"  // $& means the matched characters
            "$'");  // $' means characters following the match
        std::cout << fmt_s << '\n';
    }   
}