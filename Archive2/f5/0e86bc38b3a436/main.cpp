#include <iostream>
#include <sstream>
#include <chrono>

#include <string>
#include <regex>
#include <map>
#include <numeric>
#include <iterator>

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

std::string format4(const std::string& format,
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

	std::stringstream ss;
	std::transform(first, last, std::ostream_iterator<std::string>(ss), opacc);
	return ss.str();
}

int main()
{
	size_t count = 100000;
	{
		auto now = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < count; ++i)
			format("a{b1}aaa {a1} {a2} {{a3} bbb", {{"a1", "@11"}, {"a2", "222"}});
		// expected : a{b1}aaa @11 222 {{a3} bbb 
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - now).count() << std::endl;
	}

	{
		auto now = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < count; ++i)
			format2("a{b1}aaa {a1} {a2} {{a3} bbb", {{"a1", "@11"}, {"a2", "222"}});
		// expected : a{b1}aaa @11 222 {{a3} bbb 
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - now).count() << std::endl;
	}

	{
		auto now = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < count; ++i)
			format3("a{b1}aaa {a1} {a2} {{a3} bbb", {{"a1", "@11"}, {"a2", "222"}});
		// expected : a{b1}aaa @11 222 {{a3} bbb 
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - now).count() << std::endl;
	}

	{
		auto now = std::chrono::high_resolution_clock::now();
		for (size_t i = 0; i < count; ++i)
			format4("a{b1}aaa {a1} {a2} {{a3} bbb", {{"a1", "@11"}, {"a2", "222"}});
		// expected : a{b1}aaa @11 222 {{a3} bbb 
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - now).count() << std::endl;
	}
	return 0;
}