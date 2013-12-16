#include <iostream>
#include <locale> // for toupper()
#include <string>
 
std::string get_some_string()
{
	return "some very long string";
}
 
std::string make_loud(std::string str)
{
	for(char& c: str){
		// toupper converts every character to it's equivalent
		// uppercase-character
		c = std::toupper(c, std::locale{});
	}
	return str;
}
 
int main()
{
	std::cout << make_loud(get_some_string()) << std::endl;
}