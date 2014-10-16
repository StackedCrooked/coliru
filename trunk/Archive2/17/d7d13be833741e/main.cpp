#include <regex>
#include <iostream>

int main(int argc, char* argv[])
{
    std::regex r("<img[^>]*src=['|\"](.*?)['|\"].*?>");
	std::smatch results;
	std::string test_str = "<div><br /><img width=\"980\" height=\"1515\" id=\"mainImg\" src=\"//test/123.jpg\" alt=\"test\"></div><br />";

	std::sregex_iterator it(test_str.begin(), test_str.end(), r);
	std::sregex_iterator end;

	while (it != end)
	{
		std::cout << (*it)[1].str()<<std::endl;
		++it;
	}

	std::cin.get();
}