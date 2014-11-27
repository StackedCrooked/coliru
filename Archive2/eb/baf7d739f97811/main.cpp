#include <algorithm>
#include <iostream>
#include <string>
#include <climits>

template <typename InputIterator>
void substitute( InputIterator first, InputIterator last,
                 char const* values )
{
    char lookup[UCHAR_MAX+1];
	for (int c = 0; c++ != sizeof lookup;)
		if (std::isupper(c))
			lookup[c] = values[c - 'A'];
		else if (std::islower(c))
			lookup[c] = values[c - 'a' + 26];
		else
			lookup[c] = c;

	// Further adjustments to the table can be made here

	std::transform( first, last, first,
	                 [&] (unsigned char c) {return lookup[c];} );
}

int main()
{
	std::string keyboard = "AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn";

	char str[] = "123awefAEFZ";
	substitute( str, std::end(str)-1, keyboard.data() );

	std::cout << str;
}
