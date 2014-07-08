#include <iostream>

#include <string>
#include <regex>
#include <map>
#include <numeric>

struct Test
{
    Test() 
	{
		std::cout << "Test()" << std::endl;
	}

	Test(const Test& other) 
	{
		std::cout << "Test(const Test&)" << std::endl;
	}

	Test(Test&& other) 
	{
		std::cout << "Test(Test&&)" << std::endl;
	}

	Test& operator=(const Test& other)
	{
		std::cout << "operator=(const Test&)" << std::endl;
		return *this;
	}

	Test& operator=(Test&& other)
	{
		std::cout << "operator=(Test&&)" << std::endl;
		return *this;
	}

	Test& operator+=(const Test& other)
	{
		std::cout << "operator+=(const Test&)" << std::endl;
		return *this;
	}
    
    Test& operator+=(Test&& other)
	{
		std::cout << "operator+=(Test&&)" << std::endl;
		return *this;
	}

	operator std::string() { return "aaa"; }
};

std::string format(const std::string& format,
				   const std::map<std::string, std::string>& map)
{
	using std::sregex_token_iterator;

	bool matched = true;
	auto opacc = [&](Test& acc, const sregex_token_iterator::value_type& sm)
	{
		std::cout << "LINE:" << __LINE__ << std::endl;
		matched = !matched; // toggle
		if (!matched)
		{ 
			std::cout << "LINE:" << __LINE__ << std::endl;
			return std::ref(acc += Test{});
		}

		const auto replace = map.find(std::string{sm.first + 1, sm.second - 1});
		std::cout << "LINE:" << __LINE__ << std::endl;
    	return std::ref(acc += Test{});
	};
    
    Test t;

	static const std::regex  kDirective{R"((\{[_[:alpha:]][_[:alnum:]]*\}))"};
	const sregex_token_iterator first{begin(format), end(format), kDirective, {-1, 1}};
	const sregex_token_iterator last{};
	std::accumulate(first, last, std::ref(t), opacc);
    return "aaa";
}

int main()
{
	std::cout << format("aaa {a1}", {{"a1", "111"}}) << std::endl;
	return 0;
}