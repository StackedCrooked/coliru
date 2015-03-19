#include <string>
#include <locale>
#include <ios>

using namespace std;

template <class charT, class OutputIterator = ostreambuf_iterator<charT> >
class roman : public std::num_put < char > {
public:
    typedef charT char_type;
	typedef OutputIterator iter_type;

protected:

	virtual iter_type do_put(iter_type out, ios_base &, char_type, long v) const { 
		return fmt(v, out);
	}

	virtual iter_type do_put(iter_type out, ios_base &, char_type, long long v) const {
		return fmt(v, out);
	}

	virtual iter_type do_put(iter_type out, ios_base &, char_type, unsigned long v) const {
		return fmt(v, out);
	}

	virtual iter_type do_put(iter_type out, ios_base &, char_type, unsigned long long v) const {
		return fmt(v, out);
	}

	std::string fmt_internal(unsigned long long value) const {

		std::string roman;

		while (value >= 1000)
		{
			roman += "M";
			value -= 1000;
		}
		if (value >= 900)
		{
			roman += "CM";
			value -= 900;
		}
		while (value >= 500)
		{
			roman += "D";
			value -= 500;
		}
		if (value >= 400)
		{
			roman += "CD";
			value -= 400;
		}
		while (value >= 100)
		{
			roman += "C";
			value -= 100;
		}
		if (value >= 90)
		{
			roman += "XC";
			value -= 90;
		}
		while (value >= 50)
		{
			roman += "L";
			value -= 50;
		}
		if (value >= 40)
		{
			roman += "XL";
			value -= 40;
		}
		while (value >= 10)
		{
			roman += "X";
			value -= 10;
		}
		if (value >= 9)
		{
			roman += "IX";
			value -= 9;
		}
		while (value >= 5)
		{
			roman += "V";
			value -= 5;
		}
		if (value >= 4)
		{
			roman += "IV";
			value -= 4;
		}
		while (value > 0)
		{
			roman += "I";
			value--;
		}
		return roman;
	}

	template <class T, class Iter>
	Iter fmt(T t, Iter i) const {
		std::string s = fmt_internal(t);
		std::copy(s.begin(), s.end(), i);
		return i;
	}
};

#include <iostream>
#include <vector>

int main() {
	std::vector<int> values{ 17, 42, 199, 1997 };

	std::cout.imbue(locale(locale(), new roman<char>));

	for (auto i : values)
		std::cout << i << "\n";
}

