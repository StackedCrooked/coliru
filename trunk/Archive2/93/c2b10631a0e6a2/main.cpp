#include <iostream>
#include <vector>

template <typename CharT,
          typename Traits = std::char_traits<CharT>>
class SplittingStreambuf : public std::basic_streambuf<CharT, Traits>
{
    std::vector<std::basic_streambuf<CharT, Traits>*> others;

public:

	template <typename InputIterator>
	SplittingStreambuf( InputIterator first, InputIterator last ) :
		others(first, last) {}

	SplittingStreambuf( std::initializer_list<std::basic_streambuf<CharT, Traits>*> init ) :
		others(init) {}

	SplittingStreambuf() = default;
	SplittingStreambuf(SplittingStreambuf&&) = default;
	SplittingStreambuf& operator=(SplittingStreambuf&&) = default;

	typename Traits::int_type overflow(typename Traits::int_type c)
	{
		if (Traits::eq_int_type(Traits::eof(), c))
			return Traits::not_eof(c);

		bool good = true;
		for (auto buf : others)
			good = good && not Traits::eq_int_type(buf->sputc(c), Traits::eof());

		return good;
	}
};

int main()
{
	std::cout.rdbuf( new SplittingStreambuf<char>{std::cout.rdbuf(), std::cout.rdbuf()} );
	std::cout << "Hello world!";
}