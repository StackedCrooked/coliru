#include <algorithm>
#include <iostream>

template <typename InputIterator,
          typename BidirIterator,
          typename ForwardIterator>
InputIterator substitute( InputIterator first, InputIterator last,
                          BidirIterator key_first, BidirIterator key_last,
                          ForwardIterator val_first )
{
    for (; first != last; ++first)
	{
		auto&& ref = *first;
		auto i = std::lower_bound( key_first, key_last, ref );

		if (i == key_last || *i != ref)
			return first;

		ref = *std::next(val_first, std::distance(key_first, i));
	}

	return last;
}

int main()
{
	std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	std::string keyboard = "AZERTYUIOPQSDFGHJKLMWXCVBNazertyuiopqsdfghjklmwxcvbn";

	char str[] = "abccdef";
	substitute( std::begin(str), std::end(str)-1,
	            alphabet.begin(), alphabet.end(),
	            keyboard.begin() );

	std::cout << str;
}
