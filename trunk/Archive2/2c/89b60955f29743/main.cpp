#include <iostream>
#include <iterator>
#include <algorithm>
#include <stdexcept>

template <typename InputIterator, typename T>
InputIterator findClosing( InputIterator first, InputIterator last, T close )
{
    if (first == last)
		return last;

	auto open = *first;
	unsigned counter = 1;
	while (++first != last)
	{
		if (*first == close && --counter == 0)
			return first;
		if (*first == open)
			++counter;
	}

	return last;
}

template <std::size_t N,
          std::size_t N2>
std::string f(char const(&str)[N], char const(&name)[N2])
{
	using namespace std;

	// Argument to isalnum must be unsigned:
	auto cond = [] (unsigned char c) {return !isalnum(c) && c != '_';};

	auto iter = str;
	for (;;++iter)
	{
		iter = search( iter, end(str),
		               begin(name), end(name)-1 );

		if (iter == end(str))
			throw invalid_argument("");

		if ((iter == begin(str)      || cond(iter[-1]))
		 && (iter ==   end(str) - N2 || cond(iter[N2-1])))
			break;
	}

	auto origin_iter = iter;
	while(iter != begin(str))
	{
		--iter;
		for (auto p : {"()", "{}"})
		if (*iter == p[1])
			iter = findClosing(reverse_iterator<char const*>(iter+1),
			                   reverse_iterator<char const*>(begin(str)),
			                   p[0]).base()-2;

		if (cond(*iter) && *iter != ':')
			return string(iter+1, origin_iter+N2-1);
	}

	return string(iter, origin_iter+N2-1);
}


namespace foo {
namespace {

template<int i>
int (*bar(int (*arg)(int *)))(int *)
{
	std::cout << f(__PRETTY_FUNCTION__, __func__) << '\n';
	return arg;
}

void foobar()
{
	std::cout << f(__PRETTY_FUNCTION__, __func__) << '\n';
}

} // anonymous namespace
} // namespace foo

int main()
{
	foo::bar<1337>(nullptr);
	foo::foobar();
}
