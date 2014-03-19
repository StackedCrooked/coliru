#include <cassert>
#include <iostream>
#include <string>

namespace {

const std::string key_layout[10] =
{
    " ",
    "",
	"ABC",
	"DEF",
	"GHI",
	"JKL",
	"MNO",
	"PQRS",
	"TUV",
	"WXYZ",
};

template <typename It>
void print_permutations(It begin, It end, std::string& s)
{
	if (begin == end)
	{
		std::cout << s << std::endl;
		return;
	}

	char c = begin[0];
	assert('0' <= c && c <= '9');

	auto& letters = key_layout[c - '0'];
	if (letters.empty())
		return print_permutations(begin + 1, end, s);

	const auto old_size = s.size();
	for (auto l : letters)
	{
		s += l;
		print_permutations(begin + 1, end, s);
		s.resize(old_size);
	}
}

void print_permutations(const std::string& number)
{
	std::string s;
	print_permutations(begin(number), end(number), s);
}

}

int main()
{
	std::string number;
	std::cin >> number;
	print_permutations(number);
}
