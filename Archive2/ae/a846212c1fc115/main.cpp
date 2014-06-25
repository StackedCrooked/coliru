#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

int main(int argc, const char* argv[])
{
    std::vector<string> vec;

	vec.push_back("XXXX_LLLL");
	vec.push_back("XXXX_HHHH");
	vec.push_back("XXXX_XXXX");

	for_each(vec.begin(), vec.end(), [&](string &str) {
		regex_replace(str.begin(), str.begin(), str.end(), regex("_"), "");
	});

	for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); ++it )
    {
        std::cout << *it << std::endl;
    }
	return 0;
}