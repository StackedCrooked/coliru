#include <iostream>
#include <string>
#include <map>
#include <boost/any.hpp>

using namespace std;

struct RightFold
{
    RightFold()
	{
		cout << "constructor\n";
	}
	RightFold(RightFold const&)
	{
		cout << "copy\n";
	}
};

template <typename T>
void Set(map<string, boost::any> &OptionsMap, std::string optionName, T&& optionValue)
{
	OptionsMap[optionName] = std::move(optionValue);
}

int main() 
{
	map<string, boost::any> mp;

    RightFold a;
	Set(mp, "lala", std::move(a));

	return 0;
}