#include<iostream>
#include<regex>
#include<string>

int main()
{
    const std::string myString = "(123)";
    
    // open paranthesis, three decimal digits, close paranthesis
    const std::regex myRegex( "\\([0-9][0-9][0-9]\\)" ); // parantheses need to be escaped
    if( std::regex_match(myString,myRegex) ) std::cout << "Match found!\n";

    const std::regex myRegex2( "\\([0-9]{3}\\)" ); // [0-9] three times
    if( std::regex_match(myString,myRegex2) ) std::cout << "Match found!\n";

    const std::regex myRegex3( "\\(\\d{3}\\)" ); // decimal digit three times
    if( std::regex_match(myString,myRegex3) ) std::cout << "Match found!\n";

    // http://www.stroustrup.com/C++11FAQ.html#raw-strings
    const std::regex myRegex4( R"x(\(\d{3}\))x" ); // same as myRegex3 with a raw string literal
    if( std::regex_match(myString,myRegex3) ) std::cout << "Match found!\n";
}
