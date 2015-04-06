#include <streambuf>

template <typename CharT, typename Traits=std::char_traits<CharT>>
class FilterBuf : public std::basic_streambuf<CharT, Traits> {
    using base =  std::basic_streambuf<CharT, Traits>;
	using typename base::char_type;
	using typename base::int_type;
	using typename base::traits_type;

	base* sbf;
	char_type ch;
	char_type const* str;
	std::size_t len;

	int_type underflow() override {
		if (this->gptr() < this->egptr())
			return traits_type::to_int_type(ch);

		do {
			auto i = sbf->sbumpc();
			if (traits_type::eq_int_type(i, traits_type::eof())) {
				this->setg(0,0,0);
				return i;
			}
			traits_type::assign(ch, traits_type::to_char_type(i));
		} while (traits_type::find(str, len, ch));

		this->setg(&ch, &ch, &ch+1);
		return traits_type::to_int_type(ch);
	}

public:

	FilterBuf( base* sbf, char_type const* str, std::size_t len )
		: sbf(sbf), str(str), len(len) {
		this->setg(&ch, &ch+1, &ch+1);
	}
};


#include <iostream>
#include <sstream>

int main()
{
	std::istringstream stream("Hallo SeppJ, ein wunderschoener Tag, nicht wahr?");
	FilterBuf<char> newBuf(stream.rdbuf(), "aeiou", 5);
	std::cout << &newBuf;
}
