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
	auto optrans = [&](const tokeniter::value_type& sm)
	{
		matched = !matched; // toggle
		if (!matched)
			return sm.str();

		const auto replace = map.find(std::string{sm.first + 1, sm.second - 1});
		return std::string{replace == end(map) ? sm.str() : replace->second};
	};

	static const std::regex  kDirective{R"(\{[_[:alpha:]][_[:alnum:]]*\})"};
	const tokeniter first{begin(format), end(format), kDirective, {-1, 0}};
	const tokeniter last{};

	std::stringstream ss;
    std::ostream_iterator<std::string> out(ss);
	std::transform(first, last, out, optrans);
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
	return 0;
}