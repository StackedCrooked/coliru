#include <iostream>
#include <string>
#include <regex>

int main()
{
    std::string str="Hello  world";
//	std::getline(std::cin, str,'.');
	std::regex regex("[ ]{2,}");//two or more space
	std::string replace_str = " ";//replace with one space
	str = std::regex_replace(str, regex, replace_str);//find regex in str and replace with  replace_str
	std::cout << str.size();
}