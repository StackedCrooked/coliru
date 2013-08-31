#include <iostream>
#include <string>

std::string to_x(std::string &str) {
    for(decltype(str.size()) i = 0; i < str.size(); ++i) {
		str[i] = 'x';
	}
	return str;
}

int main()
{
    std::string str1 = "hello world!";
    std::cout << str1;
    std::cout << " " << to_x(str1) << std::endl;
    
    std::string str2 = "hello world!";
    std::cout << str2 << " " << to_x(str2) << std::endl;
}
