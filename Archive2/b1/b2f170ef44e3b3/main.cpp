#include <algorithm>
#include <iostream>
#include <string>

// Helper
std::size_t getIndex( char c )
{
    if (c >= 'A' && c <= 'Z')
		return c - 'A';
	if (c >= 'a' && c <= 'z')
		return 26 + c - 'a';

	return -1;
}

template <typename InputIterator,
          typename ForwardIterator>
InputIterator substitute( InputIterator first, InputIterator last,
                          ForwardIterator val_first )
{
	for (; first != last; ++first)
	{
		auto&& ref = *first;
		auto i = getIndex(ref);

		if (i == std::size_t(-1)) // For simplicity of warning suppression
			return first;

		ref = *std::next(val_first, i);
	}

	return last;
}

int main()
{
	std::string keyboard = "AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn";

	char str[] = "AZabccdef";
	substitute( std::begin(str), std::end(str)-1,
	            keyboard.begin() );

	std::cout << str;
}
