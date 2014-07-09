#include <iostream>

#include <string>
#include <regex>
#include <map>
#include <numeric>
#include <iterator>

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

	Test& operator+(const Test& other)
	{
		std::cout << "operator+(const Test&)" << std::endl;
		return *this;
	}

	operator std::string() { return "aaa"; }
};

std::string format(const std::string& format,
				   const std::map<std::string, std::string>& map)
{
	using tokeniter = std::sregex_token_iterator;

	bool matched = true;
	auto opacc = [&](std::string& acc, const tokeniter::value_type& sm)
	{
		matched = !matched; // toggle
		if (!matched)
			return std::ref(acc += sm.str());

		const auto replace = map.find(std::string{sm.first + 1, sm.second - 1});
		return std::ref(acc += (replace == end(map)?sm.str():replace->second));
	};

	static const std::regex  kDirective{R"((\{[_[:alpha:]][_[:alnum:]]*\}))"};
	const tokeniter first{begin(format), end(format), kDirective, {-1, 1}};
	const tokeniter last{};

	std::string ret;
	return std::accumulate(first, last, std::ref(ret), opacc);
}

std::string format2(const std::string& format,
					const std::map<std::string, std::string>& map)
{
	using tokeniter = std::sregex_token_iterator;

	bool matched = true;
	std::string acc;
	auto opacc = [&](const tokeniter::value_type& sm)
	{
		matched = !matched; // toggle
		if (!matched)
			return (acc += sm.str());

		const auto replace = map.find(std::string{sm.first + 1, sm.second - 1});
		return (acc += (replace == end(map)?sm.str():replace->second));
	};

	static const std::regex  kDirective{R"((\{[_[:alpha:]][_[:alnum:]]*\}))"};
	const tokeniter first{begin(format), end(format), kDirective, {-1, 1}};
	const tokeniter last{};

	std::for_each(first, last, opacc);
	return acc;
}

template <class Container> 
class append_iterator : public std::iterator < std::output_iterator_tag, void, void, void, void >
{
public:
	append_iterator(Container& c)
		: c_(c)
	{}

	template <typename T>
	append_iterator& operator=(T&& value)
	{
		c_.append(std::forward<T>(value));
		return *this;
	}

	append_iterator& operator*() { return *this; }

	append_iterator& operator++() { return *this; }
	append_iterator& operator++(int) { return *this; }

private:
	Container& c_;
};

template <class Container>
append_iterator<Container> appender(Container& c)
{
	return append_iterator<Container>(c);
}

std::string format3(const std::string& format,
					const std::map<std::string, std::string>& map)
{
	using tokeniter = std::sregex_token_iterator;

	bool matched = true;
	auto opacc = [&](const tokeniter::value_type& sm)
	{
		matched = !matched; // toggle
		if (!matched)
			return sm.str();

		const auto replace = map.find(std::string{sm.first + 1, sm.second - 1});
		return std::string{replace == end(map) ? sm.str() : replace->second};
	};

	static const std::regex  kDirective{R"((\{[_[:alpha:]][_[:alnum:]]*\}))"};
	const tokeniter first{begin(format), end(format), kDirective, {-1, 1}};
	const tokeniter last{};

	std::string acc;
	std::transform(first, last, appender(acc), opacc);
	return acc;
}

int main()
{
	std::cout << format("a{b1}aaa {a1} {a2} {{a3} bbb", {{"a1", "@11"}, {"a2", "222"}}) << std::endl;
	std::cout << format2("a{b1}aaa {a1} {a2} {{a3} bbb", {{"a1", "@11"}, {"a2", "222"}}) << std::endl;
	std::cout << format3("a{b1}aaa {a1} {a2} {{a3} bbb", {{"a1", "@11"}, {"a2", "222"}}) << std::endl;
	// expected : a{b1}aaa @11 222 {{a3} bbb 

	std::cout << format("aaa {} {{}} {a1} bbb}", {{"a1", "111"}}) << std::endl;
	std::cout << format2("aaa {} {{}} {a1} bbb}", {{"a1", "111"}}) << std::endl;
	std::cout << format3("aaa {} {{}} {a1} bbb}", {{"a1", "111"}}) << std::endl;
	// expected : aaa {} {{}} 111 bbb}
	return 0;
}